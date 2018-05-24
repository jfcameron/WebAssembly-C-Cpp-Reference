// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_VECTOR4UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR4UNIFORMCOLLECTION_H

//gdk inc
#include "UniformCollection.h"
//std inc
#include <iosfwd>

namespace GDK{namespace Math{struct Vector4;}}

namespace GDK
{
    namespace GFX
    {
        /*!
         Manages and supplies Vector4 data for shaderprogram consumption
         */
        class Vector4UniformCollection final : public UniformCollection<std::shared_ptr<Math::Vector4>>
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Vector4UniformCollection &);
      
        public:
            // Public methods
            void bind(const GFXuint aProgramHandle) override;
            void unbind(const GFXuint aProgramHandle) override;
            
            // Mutating operators
            Vector4UniformCollection &operator=(const Vector4UniformCollection &) = delete;
            Vector4UniformCollection &operator=(Vector4UniformCollection &&) = delete;
            
            // Constructors, destructors
            Vector4UniformCollection() = default;
            Vector4UniformCollection(const Vector4UniformCollection &) = delete;
            Vector4UniformCollection(Vector4UniformCollection &&) = delete;
            ~Vector4UniformCollection() = default;
        };

        std::ostream &operator<< (std::ostream &, const GFX::Vector4UniformCollection &);
    }
}

#endif /* GDK_GFX_VECTOR4UNIFORMCOLLECTION_H  */
