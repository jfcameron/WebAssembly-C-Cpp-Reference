// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_MAT4X4_H
#define GDK_MATH_MAT4X4_H

#include <iosfwd>
//#include <type_traits>

namespace gdk
{
    struct Vector2;
    struct Vector3;
    struct Quaternion;

    /// \brief 4 by 4 matrix of floating point numbers, used to calculate 3D transformations and camera projections.
    //template<typename T = float>
    struct Mat4x4 final
    {
        //static_assert(std::is_floating_point<T>::value, "MemoryStruct must be C compatible");

        float m[4][4] = {}; //<! the 16 floats of data, arranged in 2d grid

        //! Sets matrix to an identity matrix
        void setToIdentity();

        //! Sets matrix to an orthographic projection matrix, typically used to render a 2D scene or to render maps (lighting, depth) of a 3D scene
        void setToOrthographic(const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);

        //! Sets matrix to a perspective projection matrix, typically used to render a 3D scene
        void setToPerspective(const float aFieldOfView, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);

        //! apply a translation to the matrix
        void translate(const Vector3 &aTranslation);

        //! apply a rotation to the matrix
        void rotate(const Quaternion &aRotation);

        //! apply a scale to the matrix
        void scale(const Vector3 &aScale);

        //! transpose the matrix
        void transpose();

        //! assign values to all 16 elements of the matrix
        Mat4x4 set(
            const float m00, const float m01, const float m02, const float m03, const float m10, const float m11, const float m12, const float m13,
            const float m20, const float m21, const float m22, const float m23, const float m30, const float m31, const float m32, const float m33
        );

        //! multiply the matrix against another
        Mat4x4 multiply(const Mat4x4 &right);

        //! returns a new matrix which is the result of a multiplication, without mutating this
        Mat4x4 operator*(const Mat4x4&) const;
        //! alias for multiply
        Mat4x4& operator*=(const Mat4x4&);
        
        Mat4x4& operator=(const Mat4x4&) = default;
            
        /*Mat4x4(
            const float a00, const float a01, const float a02, const float a03, const float a10, const float a11, const float a12, const float a13,
            const float a20, const float a21, const float a22, const float a23, const float a30, const float a31, const float a32, const float a33
            );*/
        Mat4x4();
        Mat4x4(const Mat4x4&) = default;
        Mat4x4(Mat4x4&&) = default;
        ~Mat4x4() = default;
        
        static const Mat4x4 Identity; //< multiplicative identity matrix
    };
        
    std::ostream& operator<< (std::ostream&, const gdk::Mat4x4&);
}

#endif
