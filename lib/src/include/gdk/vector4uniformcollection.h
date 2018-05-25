// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_VECTOR4UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR4UNIFORMCOLLECTION_H

#include "gdk/uniformcollection.h"

#include <iosfwd>

namespace gdk
{
    struct Vector4;
    
    /*!
      Manages and supplies Vector4 data for shaderprogram consumption
    */
    class Vector4UniformCollection final : public UniformCollection<std::shared_ptr<Vector4>>
    {
        friend std::ostream &operator<< (std::ostream &, const Vector4UniformCollection &);
      
    public:
        // Public methods
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        // Mutating operators
        Vector4UniformCollection &operator=(const Vector4UniformCollection &) = delete;
        Vector4UniformCollection &operator=(Vector4UniformCollection &&) = delete;
            
        // Constructors, destructors
        Vector4UniformCollection() = default;
        Vector4UniformCollection(const Vector4UniformCollection &) = default;
        Vector4UniformCollection(Vector4UniformCollection &&) = default;
        ~Vector4UniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const Vector4UniformCollection &);
}

#endif
