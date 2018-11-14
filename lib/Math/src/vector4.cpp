// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/vector3.h>
#include <gdk/vector4.h>

#include <nlohmann/json.hpp>

#include <iostream>

using namespace gdk;

static constexpr char TAG[] = "Vector4";

const Vector4 Vector4::Zero = {0., 0., 0., 0.};

std::ostream &gdk::operator<<(std::ostream &s, const Vector4 &a)
{
    return s << nlohmann::json
    {
        {"Type", TAG},
        
        {"x", a.x},
        {"y", a.y},
        {"z", a.z},
        {"w", a.w},
    }
    .dump();
}

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
