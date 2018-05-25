// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_VECTOR2UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR2UNIFORMCOLLECTION_H

//gdk inc
#include "gdk/uniformcollection.h"
//std inc
#include <iosfwd>
#include <memory>

namespace gdk
{
    struct Vector2;
    
    /*!
      Manages and supplies Vector2 data for shaderprogram consumption
    */
    class Vector2UniformCollection final : public UniformCollection<std::shared_ptr<Vector2>>
    {
        friend std::ostream &operator<< (std::ostream &, const Vector2UniformCollection &);
      
    public:
        // Public methods
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        // Mutating operators
        Vector2UniformCollection &operator=(const Vector2UniformCollection &) = delete;
        Vector2UniformCollection &operator=(Vector2UniformCollection &&) = delete;
      
        // Constructors, destructors
        Vector2UniformCollection() = default;
        Vector2UniformCollection(const Vector2UniformCollection &) = default;
        Vector2UniformCollection(Vector2UniformCollection &&) = default;
        ~Vector2UniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const Vector2UniformCollection &);
}

#endif
