// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-26.
#include "Vector3.h"
//std inc
#include <math.h>
#include <iostream>

using namespace GDK;
using namespace Math;

//static const
const Vector3 Vector3::Up       = Vector3( 0.f, 1.f, 0.f);
const Vector3 Vector3::Down     = Vector3( 0.f,-1.f, 0.f);
const Vector3 Vector3::Left     = Vector3(-1.f, 0.f, 0.f);
const Vector3 Vector3::Right    = Vector3( 1.f, 0.f, 0.f);
const Vector3 Vector3::Forward  = Vector3( 0.f, 0.f, 1.f);
const Vector3 Vector3::Backward = Vector3( 0.f, 0.f,-1.f);
const Vector3 Vector3::Zero     = Vector3( 0.f, 0.f, 0.f);

//stringify
std::ostream& GDK::Math::operator<<(std::ostream& s,const Math::Vector3& a)
{
    s.clear(); s << "{"
    << "x: " << a.x << ", "
    << "y: " << a.y << ", "
    << "z: " << a.z
    << "}"; return s;
}

//ctors
Vector3::Vector3(const float &aX, const float &aY, const float &aZ)
: x(aX)
, y(aY)
, z(aZ)
{}

//operators
Vector3 Vector3::operator+(const Vector3 &aVector) const
{
    return
    {
        aVector.x + x,
        aVector.y + y,
        aVector.z + z
    };
}

Vector3 Vector3::operator-(const Vector3 &aVector) const
{
    return
    {
        aVector.x - x,
        aVector.y - y,
        aVector.z - z
    };
}

bool Vector3::operator==(const Vector3 &a) const
{
    return x == a.x && y == a.y && z == a.z ? true : false;
}

bool Vector3::operator!=(const Vector3 &a) const
{
    return x != a.x || y != a.y || z != a.z ? true : false;
}

Vector3& Vector3::operator+=(const Vector3 &aVector)
{
    x += aVector.x;
    y += aVector.y;
    z += aVector.z;
    
    return *this;
}

Vector3& Vector3::operator-=(const Vector3 &aVector)
{
    x -= aVector.x;
    y -= aVector.y;
    z -= aVector.z;
    
    return *this;
}

Vector3 Vector3::operator*(const float &aScalar) const
{
    return
    {
        x * aScalar,
        y * aScalar,
        z * aScalar
    };
}

Vector3& Vector3::operator*=(const float &aScalar)
{
    x *= aScalar;
    y *= aScalar;
    z *= aScalar;
    
    return *this;
}

float Vector3::length(void) const
{
    return sqrt( (x*x) + (y*y) + (z*z) );
}

void Vector3::normalize(void)
{
    float magnitude = Vector3::length();
    
    if (magnitude == 0.0f) // n/0 case
        return;
    
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}
