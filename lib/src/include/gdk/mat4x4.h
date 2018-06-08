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
        void set(
            const float a00, const float a01, const float a02, const float a03,
            const float a10, const float a11, const float a12, const float a13,
            const float a20, const float a21, const float a22, const float a23,
            const float a30, const float a31, const float a32, const float a33
            );
            
        // Operators
        Mat4x4 operator*(const Mat4x4&) const;
        
        Mat4x4& operator=(const Mat4x4&) = default;
        Mat4x4& operator*=(const Mat4x4&);
            
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

        //Hacks
        Mat4x4 _set(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
                            float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
        
        Mat4x4 multiply(const Mat4x4 &right);
    };
        
    std::ostream& operator<< (std::ostream&, const gdk::Mat4x4&);
}

#endif
