// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/exception.h>
#include <gdk/locking_queue.h>
#include <gdk/logger.h>
#include <gdk/resources.h>
#include <gdkresources/buildinfo.h>

#if defined JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows || defined JFC_TARGET_PLATFORM_Linux
#include <curl/curl.h>
#include <curl/easy.h>
#endif

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

static constexpr char TAG[] = "Resources";

namespace gdk::resources::hidden
{
    locking_queue<std::function<void()>> queued_fetches;

    std::queue<std::function<void()>> queued_responses;

    void updateFetchQueue()
    {
        std::function<void()> fetchTask;
        
        if (queued_fetches.pop(fetchTask)) fetchTask();
    }

    void updateResponseQueue()
    {
        if (queued_responses.size() > 0)
        {
            queued_responses.front()();

            queued_responses.pop();
        }
    }
}

namespace gdk::resources::local
{
    void fetchFile(const std::string aPath, response_handler_type aResponse)
    {
        hidden::queued_fetches.push([=]()
        {
            gdk::log(TAG, "worker fetching ", aPath);
            
            std::ifstream input(aPath, std::ios::binary);

            std::vector<char> buffer(
                (std::istreambuf_iterator<char>(input)), 
                (std::istreambuf_iterator<char>()));
            
            hidden::queued_responses.push([=]()
            {
                gdk::log(TAG, "main is responding to ", aPath);
                
                auto output = (std::vector<unsigned char>) // This will have to change when i go async
                {buffer.begin(), buffer.end()};
                
                aResponse(true, output);
            });
        });
    }
}

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows || defined JFC_TARGET_PLATFORM_Linux

// Buffer in system memory, used to store binary data fetched from remote server
struct MemoryStruct 
{
    char *memory;
    size_t size;
};

static_assert(std::is_trivial<MemoryStruct>::value,         "MemoryStruct must be C compatible");
static_assert(std::is_standard_layout<MemoryStruct>::value, "MemoryStruct must be C compatible");
 
static size_t WriteMemoryCallback(void *const contentPointer, const size_t contentItemSize, const size_t contentItemCount, void *const userPointer)
{
    const size_t contentByteCount = contentItemSize * contentItemCount;
    
    auto pResponseBuffer = static_cast<struct MemoryStruct *const>(userPointer);

    return [&contentPointer, &contentByteCount, &pResponseBuffer]()
    {
        if ((pResponseBuffer->memory = static_cast<char *>(realloc(pResponseBuffer->memory, pResponseBuffer->size + contentByteCount + 1))) == nullptr)
            throw gdk::Exception(TAG, "gdk::resources::remote fetch failed: could not allocate system memory to store fetched content!");
 
        memcpy(&(pResponseBuffer->memory[pResponseBuffer->size]), contentPointer, contentByteCount);

        pResponseBuffer->size += contentByteCount;

        pResponseBuffer->memory[pResponseBuffer->size] = {0};
 
        return contentByteCount;
    }();
}

#endif

namespace gdk::resources::remote
{    
    void fetchFile(const std::string aURL, response_handler_type aResponseHandler)
    {
#if defined JFC_TARGET_PLATFORM_Emscripten

        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "GET");

        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

        using callback_type = std::function<void(const bool, std::vector<unsigned char> *const)>;

        gdk::log(TAG, "fetch has begun");
                
        attr.onsuccess = [](emscripten_fetch_t *const fetch)
            {
                gdk::log(TAG, "fetch has succeeded");

                std::vector<unsigned char> binaryData = std::vector<unsigned char>(&(fetch->data[0]), &(fetch->data[fetch->numBytes]));

                auto pCallback = static_cast<callback_type *>(fetch->userData);

                (*pCallback)(true, &binaryData);

                delete pCallback;        
                emscripten_fetch_close(fetch);
            };
        
        attr.onerror = [](emscripten_fetch_t *const fetch)
            {
                gdk::log(TAG, "fetch has failed");

                printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

                auto pCallback = static_cast<callback_type *>(fetch->userData);

                (*pCallback)(false, nullptr);

                delete pCallback;        
                
                emscripten_fetch_close(fetch);
            };

        attr.userData = static_cast<void *>(new callback_type([aResponseHandler](const bool aSucceeded, std::vector<unsigned char> *const aBytes)
        {
            aResponseHandler(aSucceeded, *aBytes);
        }));
        
        emscripten_fetch(&attr, aURL.c_str());

#elif defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows || defined JFC_TARGET_PLATFORM_Linux

        hidden::queued_fetches.push([=]()
        {
            gdk::log(TAG, "worker fetching ", aURL);
            
            curl_global_init(CURL_GLOBAL_ALL); // MOVE TO A CURL WRAPPER

            if (CURL * curl_handle = curl_easy_init())
            {
                struct MemoryStruct chunk = (MemoryStruct)
                {
                    .memory = static_cast<char *>(malloc(1)),
                    .size =   0
                };

                curl_easy_setopt(curl_handle, CURLOPT_URL, aURL.c_str());                  /* specify URL to get */
                curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); /* send all data to this function  */
                curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);          /* we pass our 'chunk' struct to the callback function */
                curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");     /* some servers don't like requests that are made without a user-agent field, so we provide one */
            
                const CURLcode curlResult = curl_easy_perform(curl_handle);
            
                if (curlResult != CURLE_OK) // on macos/xcode saw an issue where this passsed although it was not CURLE_OK
                {
                    gdk::Exception(TAG, "curl_easy_perform failed: ", curl_easy_strerror(curlResult));
                }
                else
                {
                    //printf("%lu bytes retrieved\n", static_cast<unsigned long>(chunk.size));

                    // This writes to a file then loads it from file
                    //FILE *fp = fopen(std::string("resource/mia.png").c_str(), "wb");
                    //fwrite(chunk.memory, 1, chunk.size, fp); //This works! the file looks good.
                    //fclose(fp);
                    //auto output = gdk::resources::local::fetchFile("resource/mia.png");
                
                    auto output = (std::vector<unsigned char>) // This will have to change when i go async
                    {
                        chunk.memory, chunk.memory + (chunk.size)
                    };

                    hidden::queued_responses.push([=]()
                    {
                        gdk::log(TAG, "main is responding to ", aURL);
                        
                        aResponseHandler(true, output);
                    });
                }
                
                curl_easy_cleanup(curl_handle);

                free(chunk.memory);
            }
            else throw gdk::Exception(TAG, "Failed to initialize a curl session.");
            
            curl_global_cleanup();  // MOVE TO A CURL WRAPPER
        });
 
#else
#error fetchFile is unimplemented on the current platform
#endif

    }
}
