// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_VECTOR3UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR3UNIFORMCOLLECTION_H

#include <gdk/uniformcollection.h>

#include <iosfwd>

namespace gdk
{
    struct Vector3;
    
    /*!
      Manages and supplies Vector3 data for shaderprogram consumption
    */
    class Vector3UniformCollection final : public UniformCollection<std::shared_ptr<Vector3>>
    {
        friend std::ostream &operator<< (std::ostream &, const Vector3UniformCollection &);
      
    public:
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        Vector3UniformCollection &operator=(const Vector3UniformCollection &) = delete;
        Vector3UniformCollection &operator=(Vector3UniformCollection &&) = delete;
            
        Vector3UniformCollection() = default;
        Vector3UniformCollection(const Vector3UniformCollection &) = default;
        Vector3UniformCollection(Vector3UniformCollection &&) = default;
        ~Vector3UniformCollection() = default;      
    };

    std::ostream &operator<< (std::ostream &, const Vector3UniformCollection &);
}

#endif
