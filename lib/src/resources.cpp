#include <gdkresources/buildinfo.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#include <emscripten/fetch.h>
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
        
#else
#error fetchBinaryFile is unimplemented on the current platform
#endif
    }
}
