// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-26.
#ifndef GDK_MATH_INTVECTOR2_H
#define GDK_MATH_INTVECTOR2_H

//std inc
#include <iosfwd>

namespace GDK
{
    namespace Math
    {
        struct Vector2;
        
        /*! 
         Behaves like a Vector2 but uses integers for storage rather than floats.
         Useful for describing such things as non-normalized texel position,
         tilegrid position, window size, etc.
         */
        struct IntVector2 final
        {
            // Data members
            int x = 0, y = 0;
            
            Vector2 toVector2() const;
            
            // Non mutating operators
            bool operator==(const IntVector2 &) const;
            bool operator!=(const IntVector2 &) const;
            IntVector2 operator+(const IntVector2 &) const;
            IntVector2 operator-(const IntVector2 &) const;
            IntVector2 operator*(const float aScalar) const;
            IntVector2 operator*(const Vector2 &aVector2) const;
            
            // Mutating operators
            IntVector2 &operator+=(const IntVector2 &);
            IntVector2 &operator-=(const IntVector2 &);
            IntVector2 &operator*=(const float);
            IntVector2 &operator=(const IntVector2 &) = default;
            IntVector2 &operator=(IntVector2 &&) = default;
            
            // Constructors  &Destructors
            IntVector2(const int aX, const int aY);
            IntVector2() = default;
            IntVector2(const IntVector2 &) = default;
            IntVector2(IntVector2 &&) = default;
            ~IntVector2() = default;
            
            // Special values
            static const IntVector2 Up;
            static const IntVector2 Down;
            static const IntVector2 Left;
            static const IntVector2 Right;
            static const IntVector2 Zero;
        };
        
        std::ostream &operator<< (std::ostream &, const Math::IntVector2 &);
    }
}

#endif /* GDK_MATH_INTVECTOR2_H */
