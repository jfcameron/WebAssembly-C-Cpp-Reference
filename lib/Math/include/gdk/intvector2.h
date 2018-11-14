// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_INTVECTOR2_H
#define GDK_MATH_INTVECTOR2_H

#include <utility>
#include <iosfwd>

namespace gdk
{
    struct Vector2;
        
    /// \brief Behaves like a Vector2 but uses integers for storage rather than floats.
    ///
    /// \detailed Useful for describing such things as non-normalized texel position,
    /// tilegrid position, window size, etc.
    struct IntVector2 final
    {
        using std_pair_type = std::pair<int, int>;

        int x = {0}, y = {0};

        Vector2 toVector2() const; //<! create a Vector2 (related floating-point struct) from an IntVector2 instance
    
        bool operator==(const IntVector2 &) const;
        bool operator!=(const IntVector2 &) const;
        
        IntVector2 operator+(const IntVector2 &) const;
        IntVector2 operator-(const IntVector2 &) const;
        IntVector2 operator*(const float aScalar) const;
        IntVector2 operator*(const Vector2 &aVector2) const;

        IntVector2 &operator=(const IntVector2 &) = default;
        IntVector2 &operator=(IntVector2 &&) = default;
        
        IntVector2 &operator+=(const IntVector2 &);
        IntVector2 &operator-=(const IntVector2 &);
        IntVector2 &operator*=(const float);

        explicit operator std_pair_type() const;

        explicit operator Vector2() const; //<! alias for toVector2() using explicit c++ cast semantics

        IntVector2(const int aX, const int aY);
        IntVector2(const std_pair_type &aPair);
        IntVector2() = default;
        IntVector2(const IntVector2 &) = default;
        IntVector2(IntVector2 &&) = default;
        ~IntVector2() = default;
            
        static const IntVector2 Up;
        static const IntVector2 Down;
        static const IntVector2 Left;
        static const IntVector2 Right;
        static const IntVector2 Zero;
    };
        
    std::ostream &operator<< (std::ostream &, const gdk::IntVector2 &);
}

#endif
