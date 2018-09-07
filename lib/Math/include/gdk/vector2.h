// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_VECTOR2_H
#define GDK_MATH_VECTOR2_H

#include <iosfwd>
//#include <type_traits>

namespace gdk
{
    /// \brief 2 component floating point struct. 
    ///
    /// \detailed useful for storing 2D position, speed, direction, normalized coordinates.
    ///
    /// \note in reference to the static members: 
    /// X is considered the lateral component, pointing right, 
    /// Y the vertical, pointing up
    //template<typename T = float>
    struct Vector2 final
    {
        //static_assert(std::is_floating_point<T>::value, "MemoryStruct must be C compatible");

        float x = {0.}, y = {0.};
        
        float length() const;         //!< squareroot of the sum of the 2nd power of the components
        float getAspectRatio() const; //!< division of the x component by the y component
        void  normalize();            //!< Reduce length of the vector to 1 while maintaning its direction
            
        bool operator==(const Vector2 &) const;
        bool operator!=(const Vector2 &) const;
        
        Vector2 operator+(const Vector2 &) const;
        Vector2 operator-(const Vector2 &) const;
        Vector2 operator*(const float) const;
            
        Vector2 &operator+=(const Vector2 &);
        Vector2 &operator-=(const Vector2 &);
        Vector2 &operator*=(const float);

        Vector2 &operator=(const Vector2 &) = default;

        Vector2(const float);                    //!< Assign 1 fp value to all components
        Vector2(const float aX, const float aY); //!< Assign each component independently
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
