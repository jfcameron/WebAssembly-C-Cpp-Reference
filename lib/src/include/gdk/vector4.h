// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created 2017-06-27.
#ifndef GDK_MATH_VECTOR4_H
#define GDK_MATH_VECTOR4_H

//std inc
#include <iosfwd>

namespace gdk
{
    struct Vector3;
        
    /*!
         Like Vector3 but allows w to != 1. Used in Vector vs Mat4x4 operations
         */
    struct Vector4 final
    {
        // Data members
        float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
            
        //Mutating operators
        bool operator==(const Vector4&) const;
        bool operator!=(const Vector4&) const;
        Vector4& operator+=(const Vector4&);
        Vector4& operator*=(const float&);
        Vector4& operator=(const Vector4&) = default;
            
        // Constructors & Destructors
        Vector4(const Vector3& aVector3, const float &aW = 1.);
        Vector4(const float &aX, const float &aY, const float &aZ, const float &aW);
        Vector4();
        Vector4(const Vector4&) = default;
        Vector4(Vector4&&) = default;
        ~Vector4() = default;
            
        // Special values
        static const Vector4 Zero;
    };
    
    std::ostream& operator<< (std::ostream&, const Vector4&);
}

#endif
