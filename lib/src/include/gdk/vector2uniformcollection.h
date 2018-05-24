// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_VECTOR2UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR2UNIFORMCOLLECTION_H

//gdk inc
#include "UniformCollection.h"
//std inc
#include <iosfwd>
#include <memory>

namespace GDK{namespace Math{struct Vector2;}}

namespace GDK
{
    namespace GFX
    {
        /*!
         Manages and supplies Vector2 data for shaderprogram consumption
         */
        class Vector2UniformCollection final : public UniformCollection<std::shared_ptr<Math::Vector2>>
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Vector2UniformCollection &);
      
        public:
            // Public methods
            void bind(const GFXuint aProgramHandle) override;
            void unbind(const GFXuint aProgramHandle) override;
            
            // Mutating operators
            Vector2UniformCollection &operator=(const Vector2UniformCollection &) = delete;
            Vector2UniformCollection &operator=(Vector2UniformCollection &&) = delete;
      
            // Constructors, destructors
            Vector2UniformCollection() = default;
            Vector2UniformCollection(const Vector2UniformCollection &) = delete;
            Vector2UniformCollection(Vector2UniformCollection &&) = delete;
            ~Vector2UniformCollection() = default;
        };

        std::ostream &operator<< (std::ostream &, const GFX::Vector2UniformCollection &);
    }
}

#endif /* GDK_GFX_VECTOR2UNIFORMCOLLECTION_H  */
