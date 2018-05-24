// © 2017 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 2017-06-26.
#ifndef gdk_MATH_VECTOR2_H
#define gdk_MATH_VECTOR2_H

//std inc
#include <iosfwd>

namespace gdk
{
    /*!
      Useful for storing 2D position, speed, direction, normalized coordinates.
    */
    struct Vector2 final
    {
        // Data members
        float x = 0.f, y = 0.f;
            
        // Non mutating operations
        /// squareroot of the sum of the 2nd power of the components
        float length() const;
            
        /// X/Y
        float getAspectRatio() const;
            
        // Mutating operations
        /// Set length to 1
        void normalize();
            
        // Non mutating operators
        bool operator==(const Vector2&) const;
        bool operator!=(const Vector2&) const;
        Vector2 operator+(const Vector2&) const;
        Vector2 operator-(const Vector2&) const;
        Vector2 operator*(const float) const;
            
        // Mutating operators
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2& operator*=(const float);
        Vector2& operator=(const Vector2&) = default;
            
        // Constructors & Destructors
        Vector2(const float);
        Vector2(const float aX, const float aY);
        Vector2() = default;
        Vector2(const Vector2 &) = default;
        Vector2(Vector2 &&) = default;
        ~Vector2() = default;
            
        // Special values
        static const Vector2 Up;
        static const Vector2 Down;
        static const Vector2 Left;
        static const Vector2 Right;
        static const Vector2 Zero;
    };
        
    std::ostream &operator<< (std::ostream &, const Vector2 &);
}

#endif
