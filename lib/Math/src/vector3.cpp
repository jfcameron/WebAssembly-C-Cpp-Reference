// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/vector3.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <cmath>

using namespace gdk;

static constexpr char TAG[] = "Vector3";

const Vector3 Vector3::Up       = { 0.f, 1.f, 0.f};
const Vector3 Vector3::Down     = { 0.f,-1.f, 0.f};
const Vector3 Vector3::Left     = {-1.f, 0.f, 0.f};
const Vector3 Vector3::Right    = { 1.f, 0.f, 0.f};
const Vector3 Vector3::Forward  = { 0.f, 0.f, 1.f};
const Vector3 Vector3::Backward = { 0.f, 0.f,-1.f};
const Vector3 Vector3::Zero     = { 0.f, 0.f, 0.f};
const Vector3 Vector3::One      = { 1.f, 1.f, 1.f};

std::ostream &gdk::operator<<(std::ostream &s,const gdk::Vector3 &a)
{
    return s << nlohmann::json
    {
        {"Type", TAG},
        
        {"x", a.x},
        {"y", a.y},
        {"z", a.z},
    }
    .dump();
}

Vector3::Vector3(const float &aX, const float &aY, const float &aZ)
: x(aX)
, y(aY)
, z(aZ)
{}

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
