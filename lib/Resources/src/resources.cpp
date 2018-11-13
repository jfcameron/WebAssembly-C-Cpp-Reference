// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/locking_queue.h>
#include <gdk/resources.h>
#include <gdk/resources_protected.h>
#include <gdk/resources_private.h>
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

namespace gdk::resources::local
{
    void fetchFile(const std::string aPath, response_handler_type aResponse)
    {
        PRIVATE::queued_fetches.push([=]()
        {
            PROTECTED::logging_interface::log(TAG, std::string("worker fetching ") + aPath);
            
            std::ifstream input(aPath, std::ios::binary);

            std::vector<char> buffer(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
            
            PRIVATE::queued_responses.push([=]()
            {
                PROTECTED::logging_interface::log(TAG, std::string("main is responding to ") + aPath); 
                
                auto output = (std::vector<unsigned char>){buffer.begin(), buffer.end()};
                
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
            throw std::runtime_error(std::string(TAG).append("gdk::resources::remote fetch failed: could not allocate system memory to store fetched content!"));
 
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

        PROTECTED::logging_interface::log(TAG, "fetch has begun");
                
        attr.onsuccess = [](emscripten_fetch_t *const fetch)
            {
                PROTECTED::logging_interface::log(TAG, "fetch has succeeded");

                std::vector<unsigned char> binaryData = std::vector<unsigned char>(&(fetch->data[0]), &(fetch->data[fetch->numBytes]));

                auto pCallback = static_cast<callback_type *>(fetch->userData);

                (*pCallback)(true, &binaryData);

                delete pCallback;        
                emscripten_fetch_close(fetch);
            };
        
        attr.onerror = [](emscripten_fetch_t *const fetch)
            {
                PROTECTED::logging_interface::log(TAG, std::string("fetch has failed. url: ") + std::string(fetch->url) + std::string(", status: ") + std::string(fetch->status));

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

        PRIVATE::queued_fetches.push([=]()
        {
            PROTECTED::logging_interface::log(TAG, std::string("worker fetching ") + aURL);
            
            curl_global_init(CURL_GLOBAL_ALL); // MOVE TO A CURL WRAPPER

            if (CURL * curl_handle = curl_easy_init())
            {
                struct MemoryStruct chunk = (MemoryStruct)
                {
                    .memory = [](){
                        if (auto pHeap = static_cast<char *>(malloc(1))) return pHeap;
                        else throw std::runtime_error(std::string(TAG).append("could not allocate space on the heap"));
                    }(),
                    .size =   0
                };

                curl_easy_setopt(curl_handle, CURLOPT_URL, aURL.c_str());                  // specify URL to get
                curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");     // some servers don't like requests that are made without a user-agent field, so we provide one

                curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); // send all data to this function
                curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);          // we pass our 'chunk' struct to the callback function
                           
                const CURLcode curlResult = curl_easy_perform(curl_handle);
            
                if (curlResult == CURLE_OK) // on macos/xcode saw an issue where this passsed although it was not CURLE_OK
                {
                    //printf("%lu bytes retrieved\n", static_cast<unsigned long>(chunk.size));
                    // This writes to a file then loads it from file
                    //FILE *fp = fopen(std::string("resource/mia.png").c_str(), "wb");
                    //fwrite(chunk.memory, 1, chunk.size, fp); //This works! the file looks good.
                    //fclose(fp);
                    //auto output = gdk::resources::local::fetchFile("resource/mia.png");
                
                    std::vector<unsigned char> output(chunk.memory, chunk.memory + chunk.size);

                    PRIVATE::queued_responses.push([=]()
                    {
                        PROTECTED::logging_interface::log(TAG, std::string("main is responding to ") + aURL);
                        
                        aResponseHandler(true, output);
                    });
                }
                else throw std::runtime_error(std::string(TAG).append("curl_easy_perform failed: ").append(curl_easy_strerror(curlResult)));
                
                curl_easy_cleanup(curl_handle);

                free(chunk.memory);
            }
            else throw std::runtime_error(std::string(TAG).append("Failed to initialize a curl session."));
            
            curl_global_cleanup();  // MOVE TO A CURL WRAPPER
        });
 
#else
#error fetchFile is unimplemented on the current platform
#endif

    }
}
