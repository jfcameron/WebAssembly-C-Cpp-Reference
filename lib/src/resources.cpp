#include <gdkresources/buildinfo.h>

#if defined JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif

/*#if defined JFC_TARGET_PLATFORM_Darwin
#include <gdk/httprequest.h>
#endif*/

#if defined JFC_TARGET_PLATFORM_Darwin
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <algorithm>
#endif

#include <stb/stb_image.h>

#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdk/texture.h>

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

#elif defined JFC_TARGET_PLATFORM_Darwin

        if (CURL *const curl = curl_easy_init())
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
        }

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
