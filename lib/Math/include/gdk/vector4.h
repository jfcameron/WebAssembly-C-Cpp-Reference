// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_VECTOR4_H
#define GDK_MATH_VECTOR4_H

#include <iosfwd>

namespace gdk
{
    struct Vector3;
        
    /// \brief Like Vector3 but allows w to != 1. Used in Vector vs Mat4x4 operations
    struct Vector4 final
    {
        float x = {0.}, y = {0.}, z = {0.}, w = {1.};
            
        bool operator==(const Vector4 &) const;
        bool operator!=(const Vector4 &) const;

        Vector4 &operator+=(const Vector4 &);
        Vector4 &operator*=(const float &);
        Vector4 &operator=(const Vector4 &) = default;
            
        Vector4(const Vector3 &aVector3, const float &aW = 1.);
        Vector4(const float &aX, const float &aY, const float &aZ, const float &aW);
        Vector4();
        Vector4(const Vector4 &) = default;
        Vector4(Vector4 &&) = default;
        ~Vector4() = default;
            
        static const Vector4 Zero;
    };
    
    std::ostream &operator<< (std::ostream &, const Vector4 &);
}

#endif
