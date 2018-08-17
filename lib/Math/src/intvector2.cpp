// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/intvector2.h>
#include <gdk/vector2.h>

#include <iostream>

using namespace gdk;

const IntVector2 IntVector2::Up    = IntVector2( 0, 1);
const IntVector2 IntVector2::Down  = IntVector2( 0,-1);
const IntVector2 IntVector2::Left  = IntVector2(-1, 0);
const IntVector2 IntVector2::Right = IntVector2( 1, 0);
const IntVector2 IntVector2::Zero  = IntVector2( 0, 0);

std::ostream &gdk::operator<<(std::ostream &s, const gdk::IntVector2 &a)
{
    s.clear(); s
    << "{"
    << "x: " << a.x << ", "
    << "y: " << a.y
    << "}";
    
    return s;
}

IntVector2::IntVector2(const int aX, const int aY)
: x(aX)
, y(aY)
{}

Vector2 IntVector2::toVector2() const
{
    return Vector2(static_cast<float>(x), static_cast<float>(y));
}

IntVector2::operator Vector2() const
{
    return this->toVector2();
}

bool IntVector2::operator==(const IntVector2 &a) const
{
    return (x == a.x && y == a.y);
}

bool IntVector2::operator!=(const IntVector2 &a) const
{
    return (x != a.x || y != a.y);
}

IntVector2 IntVector2::operator+(const IntVector2 &aIntVector2) const
{
    return IntVector2(x + aIntVector2.x, y + aIntVector2.y);
}

IntVector2 IntVector2::operator-(const IntVector2 &aIntVector2) const
{
    return IntVector2(x - aIntVector2.x, y - aIntVector2.y);
}

IntVector2 IntVector2::operator*(const float aScalar) const
{
    return IntVector2(x * aScalar, y * aScalar);
}

IntVector2 IntVector2::operator*(const Vector2& aVector2) const
{
    return IntVector2(x * aVector2.x, y * aVector2.y);
}

IntVector2& IntVector2::operator+=(const IntVector2 &aIntVector2)
{
    x += aIntVector2.x;
    y += aIntVector2.y;
    
    return *this;
}

IntVector2& IntVector2::operator-=(const IntVector2 &aIntVector2)
{
    x -= aIntVector2.x;
    y -= aIntVector2.y;
    
    return *this;
}

IntVector2& IntVector2::operator*=(const float aScalar)
{
    x *= aScalar;
    y *= aScalar;
    
    return *this;
}
