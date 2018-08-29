#include <gdkresources/buildinfo.h>

#if defined JFC_TARGET_PLATFORM_Emscripten
    #include <emscripten.h>
    #include <emscripten/fetch.h>
#endif

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows || defined JFC_TARGET_PLATFORM_Linux
    #include <stdio.h>
    #include <curl/curl.h>
    #include <curl/easy.h>
    #include <string>
    #include <algorithm>
#endif

#include <gdk/exception.h>
#include <gdk/logger.h>

#include <stb/stb_image.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iterator>

static constexpr char TAG[] = "Resources";

namespace gdk::resources::local
{
    /*std::string loadTextFile(const std::string &aPath)
    {
        std::unique_ptr<FILE, std::function<void(FILE *const)>> pFile(
            fopen(aPath.c_str(), "r"),
            [](FILE *const ptr){fclose(ptr);});
    
        std::string output;

        if (!pFile.get()) throw gdk::Exception(TAG, "no such file exists: ", aPath);
    
        else while (!feof(pFile.get()))
             {
                 char c = fgetc(pFile.get());
        
                 if (c != EOF) output += c;
             }

        return output;
    }*/

    std::vector<unsigned char> loadBinaryFile(const std::string &aPath)
    {        
        std::ifstream input( aPath, std::ios::binary );

        std::vector<char> buffer(
            (std::istreambuf_iterator<char>(input)), 
            (std::istreambuf_iterator<char>()));
        
        return {buffer.begin(), buffer.end()};
    }
}

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows || defined JFC_TARGET_PLATFORM_Linux

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    const size_t realsize = size * nmemb;
    
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
    mem->memory = static_cast<char *>(realloc(mem->memory, mem->size + realsize + 1));
  
    if(mem->memory == NULL)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
 
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
 
    return realsize;
}

#endif

namespace gdk::resources::remote
{    
    void fetchBinaryFile(const std::string &aURL, std::function<void(const bool, std::vector<unsigned char> &)> aResponseHandler)
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

        CURL *curl_handle;
        CURLcode res;
        
        struct MemoryStruct chunk;
        
        chunk.memory = static_cast<char *>(malloc(1));  /* will be grown as needed by the realloc above */ 
        chunk.size = 0;    /* no data at this point */ 
        
        curl_global_init(CURL_GLOBAL_ALL);
        
        curl_handle = curl_easy_init(); /* init the curl session */
        
        curl_easy_setopt(curl_handle, CURLOPT_URL, aURL.c_str()); /* specify URL to get */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); /* send all data to this function  */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk); /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); /* some servers don't like requests that are made without a user-agent field, so we provide one */
        
        res = curl_easy_perform(curl_handle); /* get it! */
        
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("%lu bytes retrieved\n", (unsigned long)chunk.size);

            // This writes to a file then loads it from file
            //FILE *fp = fopen(std::string("resource/mia.png").c_str(), "wb");
            //fwrite(chunk.memory, 1, chunk.size, fp); //This works! the file looks good.
            //fclose(fp);
            //auto output = gdk::resources::local::loadBinaryFile("resource/mia.png");
            
            auto output = [&]() -> std::vector<unsigned char>
            {        
                std::vector<char> buffer(
                    chunk.memory, 
                    chunk.memory + (chunk.size));///sizeof(chunk.size)));

                gdk::log(TAG, "remote size: ", chunk.size);
                
                return (std::vector<unsigned char>){buffer.begin(), buffer.end()};
            }();
            aResponseHandler(true, output);
        }
        
        /* cleanup curl stuff */ 
        curl_easy_cleanup(curl_handle);
        
        free(chunk.memory);
        
        /* we're done with libcurl, so clean it up */ 
        curl_global_cleanup();
 
#else
#error fetchBinaryFile is unimplemented on the current platform
#endif
    }
}

//This works: https://stackoverflow.com/questions/36702888/download-an-image-from-an-url-using-curl-in-c#36702936
