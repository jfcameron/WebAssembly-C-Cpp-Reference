#include <gdk/exception.h>

#include <emscripten.h>
#include <stb/stb_image.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

static constexpr char TAG[] = "File";

namespace gdk::resources
{
    std::string load_text_file(const std::string &aPath)
    {
        std::unique_ptr<FILE, std::function<void(FILE *const)>> pFile(
            fopen(aPath.c_str(), "r"),
            [](FILE *const ptr){ fclose(ptr);});
    
        std::string output;

        if (!pFile.get()) throw gdk::Exception(TAG, "no such file exists: ", aPath);
    
        else while (!feof(pFile.get()))
             {
                 char c = fgetc(pFile.get());
        
                 if (c != EOF) output += c;
             }

        return output;
    }

    std::vector<unsigned char> load_RGBA32png_file(const std::string &aPath)
    {
        int pxWidth, pxHeight, componentsPerPixel;
        unsigned char *const pImageBuffer = stbi_load(aPath.c_str(), &pxWidth, &pxHeight, &componentsPerPixel, STBI_rgb_alpha);

        if (!pImageBuffer) throw gdk::Exception(TAG, "The image file \"", aPath, "\" does not exist or is malformed.");
    
        if (componentsPerPixel != 4) throw gdk::Exception(TAG, __func__, " only supports RGBA32. The file \"", aPath, "\" does not match this requirement!");

        return {pImageBuffer, pImageBuffer + (pxWidth * pxHeight)};
    }
}
