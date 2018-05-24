// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_TEXTUREUNIFORMCOLLECTION_H
#define GDK_GFX_TEXTUREUNIFORMCOLLECTION_H

//gdk inc
#include "UniformCollection.h"
#include "Texture.h"
#include "Memory/default_ptr.h"
//std inc
#include <iosfwd>

namespace GDK
{
    namespace GFX
    {
        /*!
         Manages and supplies texture data for shaderprogram consumption
         */
        class TextureUniformCollection final : public UniformCollection<Memory::default_ptr<Texture>>
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::TextureUniformCollection &);
            
        public:
            // Public methods
            void bind(const GFXuint aProgramHandle) override;
            void unbind(const GFXuint aProgramHandle) override;
      
            // Mutating operators
            TextureUniformCollection &operator=(const TextureUniformCollection &) = delete;
            TextureUniformCollection &operator=(TextureUniformCollection &&) = delete;
            
            // Constructors, destructors
            TextureUniformCollection() = default;
            TextureUniformCollection(const TextureUniformCollection &) = delete;
            TextureUniformCollection(TextureUniformCollection &&) = default;
            ~TextureUniformCollection() = default;
        };

        std::ostream &operator<< (std::ostream &, const GFX::TextureUniformCollection &);
    }
}

#endif /* GDK_GFX_TEXTUREUNIFORMCOLLECTION_H  */
