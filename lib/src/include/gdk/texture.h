// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#ifndef GDK_GFX_TEXTURE_H
#define GDK_GFX_TEXTURE_H

#include <GLES2/gl2.h>

//std inc
#include <iosfwd>
#include <string>

namespace GDK
{
    namespace GFX
    {
        /*!
         Texture represents an image. RGBA32, 2D.
         */
        class Texture final
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Texture &);
            
            // Data members
            std::string m_Name = {};
            GFXuint m_Handle = 0;
    
        public:
            // Accessors
            std::string const &getName() const;
            GFXuint getHandle() const;
            
            // Mutating operators
            Texture &operator=(const Texture&) = delete;
            Texture &operator=(Texture&&) = delete;
      
            // Constructors, destructors
            Texture(const std::string &aName, std::vector<GFXbyte>& aRGBA32PNGTextureData /*GFXuint repeatmode = 0, GFXuint magfilter = 0*/);
            Texture() = delete;
            Texture(const Texture&) = delete;
            Texture(Texture&&);
            ~Texture();
      
        };

        std::ostream &operator<< (std::ostream &, const GFX::Texture &);
    }
}

#endif /* GDK_GFX_TEXTURE_H  */
