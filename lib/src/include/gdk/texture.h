// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_TEXTURE_H
#define GDK_GFX_TEXTURE_H

#include <gdk/opengl.h>
#include <gdk/lazy_ptr.h>

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
        
        std::string m_Name = {}; //!< Human friendly identifier
        GLuint m_Handle = {0};   //!< handle to the texture in the context
    
    public:
        std::string getName() const;
        GLuint getHandle() const;
            
        Texture &operator=(const Texture &) = delete;
        Texture &operator=(Texture &&) = delete;
        
        Texture(const std::string &aName, const std::vector<const GLubyte> &aRGBA32PNGTextureData /*GLuint repeatmode = 0, GLuint magfilter = 0*/);
        Texture() = delete;
        Texture(const Texture &) = delete;
        Texture(Texture &&);
        ~Texture();

        static const gdk::lazy_ptr<gdk::Texture> CheckeredTextureOfDeath; //!< texture for indicating some kind of failure
    };

    std::ostream &operator<< (std::ostream &, const Texture &);
}

#endif
