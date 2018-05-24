// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created 2017-06-27.
#include "Vector4.h"
//GDK inc
#include "Vector3.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace Math;

//static const
const Vector4 Vector4::Zero = Vector4( 0.,0.,0.,0.);

//Stringify
std::ostream& GDK::Math::operator<<(std::ostream& s, const Math::Vector4& a)
{
    s.clear(); s << "{"
    << "x: " << a.x << ", "
    << "y: " << a.y << ", "
    << "z: " << a.z << ", "
    << "w: " << a.w
    << "}"; return s;
}

//Constructors
Vector4::Vector4()
: x(0.)
, y(0.)
, z(0.)
, w(1.)
{}

Vector4::Vector4(const Vector3 &aVector3, const float &aW)
: x(aVector3.x)
, y(aVector3.y)
, z(aVector3.z)
, w(aW)
{}

Vector4::Vector4(const float &aX, const float &aY, const float &aZ, const float &aW)
: x(aX)
, y(aY)
, z(aZ)
, w(aW)
{}

//Operators
Vector4& Vector4::operator+=(const Vector4 &aVector4)
{
    x += aVector4.x;
    y += aVector4.y;
    z += aVector4.z;
    w += aVector4.w;
    
    return *this;
}

Vector4& Vector4::operator*=(const float &aScalar)
{
    x *= aScalar;
    y *= aScalar;
    z *= aScalar;
    w *= aScalar;
    
    return *this;
}

bool Vector4::operator==(const Vector4 &a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w ? true : false;
}

bool Vector4::operator!=(const Vector4 &a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w ? true : false;
}
