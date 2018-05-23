// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-27.
#ifndef GDK_MATH_QUATERNION_H
#define GDK_MATH_QUATERNION_H

//std inc
#include <iosfwd>

class btQuaternion;

namespace GDK
{
    namespace Math
    {
        struct Vector3;
        
        /*!
         Used to represent 3d rotations in a way insusceptible to gimblal lock (unlike Vector3)
         */
        struct Quaternion final
        {
            //Data members
            float x = 0.f, y = 0.f, z = 0.f, w = 1.f;
            
            // Euler convenience
            void setFromEuler(const Vector3& aEulers);
            Math::Vector3 toEuler() const;
            
            // Mutating operators
            Quaternion &operator=(const Quaternion &) = default;
            Quaternion &operator=(Quaternion &&) = default;
            
            // Constructors & Destructors
            Quaternion(const Vector3&);
            Quaternion(const float& aX, const float& aY, const float& aZ, const float& aW);
            Quaternion();
            Quaternion(const Quaternion&) = default;
            Quaternion(Quaternion&&) = default;
            ~Quaternion() = default;
            
            // Special values
            static const Quaternion Identity;
        };
        
        std::ostream& operator<< (std::ostream&, const Math::Quaternion&);
    }
}

#endif /* GDK_MATH_QUATERNION_H */
