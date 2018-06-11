// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_VECTOR2UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR2UNIFORMCOLLECTION_H

#include "gdk/uniformcollection.h"

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
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        Vector2UniformCollection &operator=(const Vector2UniformCollection &) = delete;
        Vector2UniformCollection &operator=(Vector2UniformCollection &&) = delete;
      
        Vector2UniformCollection() = default;
        Vector2UniformCollection(const Vector2UniformCollection &) = default;
        Vector2UniformCollection(Vector2UniformCollection &&) = default;
        ~Vector2UniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const Vector2UniformCollection &);
}

#endif
