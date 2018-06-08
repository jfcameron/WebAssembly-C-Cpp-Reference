// © 2018 Joseph Cameron - All Rights Reserved
#ifndef gdk_MATH_MAT4x4_H
#define gdk_MATH_MAT4x4_H

#include <iosfwd>

namespace gdk
{
    struct Vector2;
    struct Vector3;
    struct Quaternion;

    /*!
      a 4 by 4 matrix of floating point numbers, used to store 3D transformations.
    */
    struct Mat4x4 final
    {
        float m[4][4] = {};
            
        void setIdentity();            
        void setOrthographic(const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);
        void setPerspective(const float aFieldOfView, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);
            
        void translate(const Vector3 &aTranslation);
        void rotate(const Quaternion &aRotation);
        void scale(const Vector3 &aScale);
        void transpose();
        Mat4x4 set(
            const float m00, const float m01, const float m02, const float m03, const float m10, const float m11, const float m12, const float m13,
            const float m20, const float m21, const float m22, const float m23, const float m30, const float m31, const float m32, const float m33
            );
        
        Mat4x4 multiply(const Mat4x4 &right);
            
        // Operators
        Mat4x4 operator*(const Mat4x4&) const;
        Mat4x4& operator*=(const Mat4x4&);
        
        Mat4x4& operator=(const Mat4x4&) = default;

            
        // Constructors & Destructors
        Mat4x4(
            const float a00, const float a01, const float a02, const float a03,
            const float a10, const float a11, const float a12, const float a13,
            const float a20, const float a21, const float a22, const float a23,
            const float a30, const float a31, const float a32, const float a33
            );        
        Mat4x4();
        Mat4x4(const Mat4x4&) = default;
        Mat4x4(Mat4x4&&) = default;
        ~Mat4x4() = default;
        
        static const Mat4x4 Identity;
    };
        
    std::ostream& operator<< (std::ostream&, const gdk::Mat4x4&);
}

#endif
