#include <gdkresources/buildinfo.h>

#if defined JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif

/*#if defined JFC_TARGET_PLATFORM_Darwin
#include <gdk/httprequest.h>
#endif*/

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <algorithm>
#endif

#include <stb/stb_image.h>

#include <gdk/exception.h>
#include <gdk/logger.h>

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
    std::string loadTextFile(const std::string &aPath)
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
    }

    std::vector<unsigned char> loadBinaryFile(const std::string &aPath)
    {        
        std::ifstream input( aPath, std::ios::binary );

        std::vector<char> buffer(
            (std::istreambuf_iterator<char>(input)), 
            (std::istreambuf_iterator<char>()));
        
        return {buffer.begin(), buffer.end()};
    }
}

#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = static_cast<char *>(realloc(mem->memory, mem->size + realsize + 1));
  if(mem->memory == NULL) {
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
                
        attr.onsuccess = [](emscripten_fetch_t *const fetch)
            {
                std::vector<unsigned char> binaryData = std::vector<unsigned char>(&(fetch->data[0]), &(fetch->data[fetch->numBytes]));

                auto pCallback = static_cast<callback_type *>(fetch->userData);

                (*pCallback)(true, &binaryData);

                delete pCallback;        
                emscripten_fetch_close(fetch);
            };
        
        attr.onerror = [](emscripten_fetch_t *const fetch)
            {
                //printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

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

#elif defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Windows

        CURL *curl_handle;
        CURLcode res;
        
        struct MemoryStruct chunk;
        
        chunk.memory = static_cast<char *>(malloc(1));  /* will be grown as needed by the realloc above */ 
        chunk.size = 0;    /* no data at this point */ 
        
        curl_global_init(CURL_GLOBAL_ALL);
        
        /* init the curl session */ 
        curl_handle = curl_easy_init();
        
        /* specify URL to get */ 
        curl_easy_setopt(curl_handle, CURLOPT_URL, aURL.c_str()); //"http://www.example.com/");
        
        /* send all data to this function  */ 
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        
        /* we pass our 'chunk' struct to the callback function */ 
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        
        /* some servers don't like requests that are made without a user-agent
            field, so we provide one */ 
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        /* get it! */ 
        res = curl_easy_perform(curl_handle);
        
        /* check for errors */ 
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        else {
            /*
            * Now, our chunk.memory points to a memory block that is chunk.size
            * bytes big and contains the remote file.
            *
            * Do something nice with it!
            */ 
        
            printf("%lu bytes retrieved\n", (unsigned long)chunk.size);

            //std::vector<unsigned char> output(reinterpret_cast<const char *const>(chunk.memory), reinterpret_cast<const char *const>(chunk.memory) + (chunk.size/sizeof(chunk.size)));
            //gdk::log(TAG, "size of output: ", output.size(), ", chunksizeof: ", sizeof(chunk.size), ", chunk.size: ", chunk.size);
            //aResponseHandler(true, output);

            FILE *fp = fopen(std::string("resource/mia.png").c_str(), "wb");
            fwrite(chunk.memory, 1, chunk.size, fp); //This works! the file looks good.
            fclose(fp);

            

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


        /*if (CURL *const curl = curl_easy_init())
        {
            FILE *fp = fopen(std::string("/Users/josephcameron/Downloads/").append(curl_easy_escape(curl, aURL.c_str(), aURL.size())).c_str(), "wb");

            curl_easy_setopt(curl, CURLOPT_URL, aURL.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, 
                [&](void* ptr, size_t size, size_t nmemb, FILE* stream)
                {
                    size_t written;

                    written = fwrite(ptr, size, nmemb, stream);

                    return written;
                }
            );

            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            CURLcode res = curl_easy_perform(curl);

            // always cleanup
            curl_easy_cleanup(curl);
            fclose(fp);
        }*/

        /*if (CURL *const curl = curl_easy_init())
        {
            //FILE *fp = fopen(std::string("/Users/josephcameron/Downloads/").append(curl_easy_escape(curl, aURL.c_str(), aURL.size())).c_str(), "wb");
            std::vector<unsigned char> output;// = new std::vector<unsigned char>();

            curl_easy_setopt(curl, CURLOPT_URL, aURL.c_str());
            
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(const char *const, const size_t, const size_t, void *const)>
            (
                [](const char * contents, const size_t size, const size_t nmemb, void * userp)
                {
                    // *static_cast<std::vector<unsigned char> *>(userp) = std::vector<unsigned char>((const char *const)contents, (const char *const)contents + nmemb);

                    for(size_t i = 0, s = nmemb; i < s; ++i)
                    {
                        static_cast<std::vector<unsigned char> *>(userp)->push_back(*contents);

                        contents++;
                    }

                    gdk::log(TAG, "vecsize: ", (*static_cast<std::vector<unsigned char> *>(userp)).size(), ", nmemb: ", nmemb);

                    return size * nmemb;
                }
            ));

            gdk::log(TAG, "url: ", aURL);

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            CURLcode res = curl_easy_perform(curl);

            curl_easy_cleanup(curl);
            //fclose(fp);

            //std::function<void(const bool, std::vector<unsigned char> &)> aResponseHandler
//            aResponseHandler(true, output);
        }*/
 
#else
#error fetchBinaryFile is unimplemented on the current platform
#endif
    }
}

//This works: https://stackoverflow.com/questions/36702888/download-an-image-from-an-url-using-curl-in-c#36702936
