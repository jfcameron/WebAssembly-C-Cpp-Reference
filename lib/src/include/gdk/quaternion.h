// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 2017-06-27.
#ifndef gdk_MATH_QUATERNION_H
#define gdk_MATH_QUATERNION_H

//std inc
#include <iosfwd>

class btQuaternion;

namespace gdk
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
        gdk::Vector3 toEuler() const;
            
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
        
    std::ostream& operator<< (std::ostream&, const gdk::Quaternion&);
}

#endif
