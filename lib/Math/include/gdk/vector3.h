// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_VECTOR3_H
#define GDK_MATH_VECTOR3_H

#include <iosfwd>

namespace gdk
{
    /// \brief 3 component floating point struct.
    ///
    /// \detailed Used to represent 3d position, scale, euler angles.
    struct Vector3 final
    {
        float x = {0.}, y = {0.}, z = {0.};

        //! Calculates the length of the vector
        float length(void) const;
        
        //! Sets length of vector to 1
        void normalize(void);
            
        bool operator==(const Vector3 &) const;
        bool operator!=(const Vector3 &) const;
        Vector3 operator+(const Vector3 &) const;
        Vector3 operator-(const Vector3 &) const;
        Vector3 operator*(const float &) const;
            
        Vector3 &operator+=(const Vector3 &);
        Vector3 &operator-=(const Vector3 &);
        Vector3 &operator*=(const float &);
        Vector3 &operator=(const Vector3 &) = default;
            
        Vector3(const float &aX, const float &aY, const float &aZ);
        Vector3() = default;
        Vector3(const Vector3 &aVector3) = default;
        Vector3(Vector3 &&) = default;
        ~Vector3() = default;
            
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;
        static const Vector3 Zero;
        static const Vector3 One;
    };
        
    std::ostream &operator<< (std::ostream &, const gdk::Vector3 &);
}

#endif
