// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/mat4x4.h>
#include <gdk/vector2.h>
#include <gdk/vector3.h>
#include <gdk/quaternion.h>
#include <gdk/logger.h>
#include <gdk/trigonometry.h>
#include <gdk/exception.h>
#include <gdk/time.h>

#include <iostream>
#include <math.h>

using namespace gdk;

static constexpr auto TAG = "Mat4x4";

//static const
const Mat4x4 Mat4x4::Identity = Mat4x4();

//Stringify
std::ostream& gdk::operator<< (std::ostream &s, const gdk::Mat4x4& aMat)
{
    s.clear();s
                  
    << "{" << aMat.m[0][0] << ", " << aMat.m[1][0] << ", " << aMat.m[2][0] << ", " << aMat.m[3][0] << "}\n"
    << "{" << aMat.m[0][1] << ", " << aMat.m[1][1] << ", " << aMat.m[2][1] << ", " << aMat.m[3][1] << "}\n"
    << "{" << aMat.m[0][2] << ", " << aMat.m[1][2] << ", " << aMat.m[2][2] << ", " << aMat.m[3][2] << "}\n"
    << "{" << aMat.m[0][3] << ", " << aMat.m[1][3] << ", " << aMat.m[2][3] << ", " << aMat.m[3][3] << "}\n";
    
    return s;
}

void Mat4x4::setIdentity()
{
    m[0][0] = 1.; m[1][0] = 0.; m[2][0] = 0.; m[3][0] = 0.;
    m[0][1] = 0.; m[1][1] = 1.; m[2][1] = 0.; m[3][1] = 0.;
    m[0][2] = 0.; m[1][2] = 0.; m[2][2] = 1.; m[3][2] = 0.;
    m[0][3] = 0.; m[1][3] = 0.; m[2][3] = 0.; m[3][3] = 1.;    
}

void Mat4x4::setOrthographic(const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio)
{
    (void)aOrthoSize;
    (void)aNearClippingPlane;
    (void)aFarClippingPlane;
    (void)aViewportAspectRatio;
    
    throw gdk::Exception(TAG, "Mat4x4::setOrthographic not implemented!");
}

void Mat4x4::translate(const Vector3 &a)
{
    m[3][0] = m[0][0] * a.x + m[1][0] * a.y + m[2][0] * a.z + m[3][0];
    m[3][1] = m[0][1] * a.x + m[1][1] * a.y + m[2][1] * a.z + m[3][1];
    m[3][2] = m[0][2] * a.x + m[1][2] * a.y + m[2][2] * a.z + m[3][2];
    m[3][3] = m[0][3] * a.x + m[1][3] * a.y + m[2][3] * a.z + m[3][3];
}

void Mat4x4::rotate(const Quaternion &aRotation)
{
    const Quaternion &q = aRotation;
    
    double sqw = q.w * q.w;
    double sqx = q.x * q.x;
    double sqy = q.y * q.y;
    double sqz = q.z * q.z;
    
    // invs (inverse square length) is only required if quaternion is not already normalised
    double invs = 1 / (sqx + sqy + sqz + sqw);
    
    m[0][0] = ( sqx - sqy - sqz + sqw) * invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
    m[1][1] = (-sqx + sqy - sqz + sqw) * invs ;
    m[2][2] = (-sqx - sqy + sqz + sqw) * invs ;
    
    double tmp1 = q.x * q.y;
    double tmp2 = q.z * q.w;
    
    m[1][0] = 2.0 * static_cast<float>(tmp1 + tmp2) * invs;
    m[0][1] = 2.0 * static_cast<float>(tmp1 - tmp2) * invs;
    
    tmp1 = q.x * q.z;
    tmp2 = q.y * q.w;
    
    m[2][0] = 2.0 * static_cast<float>(tmp1 - tmp2) * invs;
    m[0][2] = 2.0 * static_cast<float>(tmp1 + tmp2) * invs;
    
    tmp1 = q.y * q.z;
    tmp2 = q.x * q.w;
    
    m[2][1] = 2.0 * static_cast<float>(tmp1 + tmp2) * invs;
    m[1][2] = 2.0 * static_cast<float>(tmp1 - tmp2) * invs;
}

void Mat4x4::scale(const Vector3 &aPosition)
{
    throw gdk::Exception(TAG, "Mat4x4::scale not implemented!");
}

void Mat4x4::setPerspective(const float aFieldOfView, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio)
{
    float tanHalfFovy = static_cast<float>(tan(aFieldOfView * 0.5f));
    
    m[0][0] = 1.0f / (aViewportAspectRatio * tanHalfFovy);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    
    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFovy;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] =-(aFarClippingPlane + aNearClippingPlane) / (aFarClippingPlane - aNearClippingPlane);
    m[2][3] =-1.0f;
    
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] =-2.0f * aFarClippingPlane * aNearClippingPlane / (aFarClippingPlane - aNearClippingPlane);
    m[3][3] = 0.0f;
}

void Mat4x4::transpose()
{
    float t00 = m[0][0]; float t10 = m[0][1]; float t20 = m[0][2]; float t30 = m[0][3];
    float t01 = m[1][0]; float t11 = m[1][1]; float t21 = m[1][2]; float t31 = m[1][3];
    float t02 = m[2][0]; float t12 = m[2][1]; float t22 = m[2][2]; float t32 = m[2][3];
    float t03 = m[3][0]; float t13 = m[3][1]; float t23 = m[3][2]; float t33 = m[3][3];
    
    set(
        t00, t10, t20, t30,
        t01, t11, t21, t31,
        t02, t12, t22, t32,
        t03, t13, t23, t33
    );
}

void Mat4x4::set
(
 const float a00, const float a10, const float a20, const float a30,
 const float a01, const float a11, const float a21, const float a31,
 const float a02, const float a12, const float a22, const float a32,
 const float a03, const float a13, const float a23, const float a33
)
{
    m[0][0] = a00; m[1][0] = a10; m[2][0] = a20; m[3][0] = a30;
    m[0][1] = a01; m[1][1] = a11; m[2][1] = a21; m[3][1] = a31;
    m[0][2] = a02; m[1][2] = a12; m[2][2] = a22; m[3][2] = a32;
    m[0][3] = a03; m[1][3] = a13; m[2][3] = a23; m[3][3] = a33;
}

// Operators
Mat4x4& Mat4x4::operator*=(const Mat4x4& a)
{
    set(
        m[0][0] * a.m[0][0] + m[1][0] * a.m[0][1] + m[2][0] * a.m[0][2] + m[3][0] * a.m[0][3],
        m[0][1] * a.m[0][0] + m[1][1] * a.m[0][1] + m[2][1] * a.m[0][2] + m[3][1] * a.m[0][3],
        m[0][2] * a.m[0][0] + m[1][2] * a.m[0][1] + m[2][2] * a.m[0][2] + m[3][2] * a.m[0][3],
        m[0][3] * a.m[0][0] + m[1][3] * a.m[0][1] + m[2][3] * a.m[0][2] + m[3][3] * a.m[0][3],
        m[0][0] * a.m[1][0] + m[1][0] * a.m[1][1] + m[2][0] * a.m[1][2] + m[3][0] * a.m[1][3],
        m[0][1] * a.m[1][0] + m[1][1] * a.m[1][1] + m[2][1] * a.m[1][2] + m[3][1] * a.m[1][3],
        m[0][2] * a.m[1][0] + m[1][2] * a.m[1][1] + m[2][2] * a.m[1][2] + m[3][2] * a.m[1][3],
        m[0][3] * a.m[1][0] + m[1][3] * a.m[1][1] + m[2][3] * a.m[1][2] + m[3][3] * a.m[1][3],
        m[0][0] * a.m[2][0] + m[1][0] * a.m[2][1] + m[2][0] * a.m[2][2] + m[3][0] * a.m[2][3],
        m[0][1] * a.m[2][0] + m[1][1] * a.m[2][1] + m[2][1] * a.m[2][2] + m[3][1] * a.m[2][3],
        m[0][2] * a.m[2][0] + m[1][2] * a.m[2][1] + m[2][2] * a.m[2][2] + m[3][2] * a.m[2][3],
        m[0][3] * a.m[2][0] + m[1][3] * a.m[2][1] + m[2][3] * a.m[2][2] + m[3][3] * a.m[2][3],
        m[0][0] * a.m[3][0] + m[1][0] * a.m[3][1] + m[2][0] * a.m[3][2] + m[3][0] * a.m[3][3],
        m[0][1] * a.m[3][0] + m[1][1] * a.m[3][1] + m[2][1] * a.m[3][2] + m[3][1] * a.m[3][3],
        m[0][2] * a.m[3][0] + m[1][2] * a.m[3][1] + m[2][2] * a.m[3][2] + m[3][2] * a.m[3][3],
        m[0][3] * a.m[3][0] + m[1][3] * a.m[3][1] + m[2][3] * a.m[3][2] + m[3][3] * a.m[3][3]
        );

    return *this;
}

Mat4x4 Mat4x4::operator*(const Mat4x4 &a) const
{
    Mat4x4 r(*this);
    
    r *= a;
    
    return r;
}

// Constructors
Mat4x4::Mat4x4()
: m
{
    {1.,0.,0.,0.},
    {0.,1.,0.,0.},
    {0.,0.,1.,0.},
    {0.,0.,0.,1.},
}
{}

Mat4x4::Mat4x4
(
 const float a00, const float a10, const float a20, const float a30,
 const float a01, const float a11, const float a21, const float a31,
 const float a02, const float a12, const float a22, const float a32,
 const float a03, const float a13, const float a23, const float a33
)
: m
{
    {a00,a01,a02,a03},
    {a10,a11,a12,a13},
    {a20,a21,a22,a23},
    {a30,a31,a32,a33},
}
{}
