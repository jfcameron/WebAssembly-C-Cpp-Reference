// © 2018 Joseph Cameron - All Rights Reserved

#ifndef gdk_MATH_VECTOR2_H
#define gdk_MATH_VECTOR2_H

//std inc
#include <iosfwd>

namespace gdk
{
    /*!
      Useful for storing 2D position, speed, direction, normalized coordinates.
      \Note in reference to the static members: 
      X is considered the lateral component, pointing right, 
      Y the vertical, pointing up
    */
    struct Vector2 final
    {
        float x = 0.f, y = 0.f;
            
        //! squareroot of the sum of the 2nd power of the components
        float length() const;
            
        //! x component divided by the y component
        float getAspectRatio() const;
            
        //! Reduce length of the vector to 1 while maintaning its direction
        void normalize();
            
        bool operator==(const Vector2&) const;
        bool operator!=(const Vector2&) const;
        
        Vector2 operator+(const Vector2&) const;
        Vector2 operator-(const Vector2&) const;
        Vector2 operator*(const float) const;
            
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2& operator*=(const float);

        Vector2& operator=(const Vector2&) = default;

        //! Assign 1 fp value to all components
        Vector2(const float);
        //! Assign each component independently
        Vector2(const float aX, const float aY);
        Vector2() = default;
        Vector2(const Vector2 &) = default;
        Vector2(Vector2 &&) = default;
        ~Vector2() = default;
            
        static const Vector2 Up;
        static const Vector2 Down;
        static const Vector2 Left;
        static const Vector2 Right;
        static const Vector2 Zero;
    };
        
    std::ostream &operator<< (std::ostream &, const Vector2 &);
}

#endif
