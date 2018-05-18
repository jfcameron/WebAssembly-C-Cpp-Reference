// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-26.
#include "IntVector2.h"
//math inc
#include "Vector2.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace Math;

// Special values
const IntVector2 IntVector2::Up    = IntVector2( 0, 1);
const IntVector2 IntVector2::Down  = IntVector2( 0,-1);
const IntVector2 IntVector2::Left  = IntVector2(-1, 0);
const IntVector2 IntVector2::Right = IntVector2( 1, 0);
const IntVector2 IntVector2::Zero  = IntVector2( 0, 0);

// Stringify
std::ostream &GDK::Math::operator<<(std::ostream &s, const Math::IntVector2 &a)
{
    s.clear(); s
    << "{"
    << "x: " << a.x << ", "
    << "y: " << a.y
    << "}";
    
    return s;
}

//Contructors
IntVector2::IntVector2(const int aX, const int aY)
: x(aX)
, y(aY)
{}

Vector2 IntVector2::toVector2() const
{
    return Vector2(x,y);
}

// Non mutating operators
bool IntVector2::operator==(const IntVector2 &a) const
{
    return x == a.x && y == a.y ? true : false;
}

bool IntVector2::operator!=(const IntVector2 &a) const
{
    return x != a.x || y != a.y ? true : false;
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

// Mutating operators
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
