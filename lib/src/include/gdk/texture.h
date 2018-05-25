// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 17-07-03.
#ifndef gdk_GFX_TEXTURE_H
#define gdk_GFX_TEXTURE_H

#include <gdk/opengl.h>

//std inc
#include <iosfwd>
#include <string>

namespace gdk
{
    /*!
      Texture represents an image. RGBA32, 2D.
    */
    class Texture final
    {
        friend std::ostream &operator<< (std::ostream &, const Texture &);
            
        // Data members
        std::string m_Name = {};
        GLuint m_Handle = {0};
    
    public:
        // Accessors
        std::string getName() const;
        GLuint getHandle() const;
            
        // Mutating operators
        Texture &operator=(const Texture&) = delete;
        Texture &operator=(Texture&&) = delete;
      
        // Constructors, destructors
        Texture(const std::string &aName, const std::vector<const GLubyte>& aRGBA32PNGTextureData /*GLuint repeatmode = 0, GLuint magfilter = 0*/);
        Texture() = delete;
        Texture(const Texture&) = delete;
        Texture(Texture&&);
        ~Texture();      
    };

    std::ostream &operator<< (std::ostream &, const Texture &);
}

#endif
