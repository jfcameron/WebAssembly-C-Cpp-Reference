// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_TEXTUREUNIFORMCOLLECTION_H
#define GDK_GFX_TEXTUREUNIFORMCOLLECTION_H

#include <gdk/uniformcollection.h>
#include <gdk/texture.h>
#include <gdk/default_ptr.h>

#include <iosfwd>

namespace gdk
{
    /*!
      Manages and supplies texture data for shaderprogram consumption
    */
    class TextureUniformCollection final : public UniformCollection<default_ptr<Texture>>
    {
        friend std::ostream &operator<< (std::ostream &, const TextureUniformCollection &);
            
    public:
        // Public methods
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
      
        // Mutating operators
        TextureUniformCollection &operator=(const TextureUniformCollection &) = delete;
        TextureUniformCollection &operator=(TextureUniformCollection &&) = delete;
            
        // Constructors, destructors
        TextureUniformCollection() = default;
        TextureUniformCollection(const TextureUniformCollection &) = default;
        TextureUniformCollection(TextureUniformCollection &&) = default;
        ~TextureUniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const TextureUniformCollection &);
}

#endif
