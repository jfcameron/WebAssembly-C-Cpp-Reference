// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_QUATERNION_H
#define GDK_MATH_QUATERNION_H

#include <iosfwd>

namespace gdk
{
    struct Vector3;
        
    /// \brief Used to represent 3d rotations in a way insusceptible to gimblal lock (unlike Vector3)
    struct Quaternion final
    {
        float x = {0.}, y = {0.}, z = {0.}, w = {1.};
            
        void setFromEuler(const Vector3 &aEulers);
        gdk::Vector3 toEuler() const;
            
        Quaternion &operator=(const Quaternion &) = default;
        Quaternion &operator=(Quaternion &&) = default;
            
        Quaternion(const Vector3 &);
        Quaternion(const float &aX, const float &aY, const float &aZ, const float &aW);
        Quaternion();
        Quaternion(const Quaternion &) = default;
        Quaternion(Quaternion &&) = default;
        ~Quaternion() = default;
        
        static const Quaternion Identity;
    };
        
    std::ostream &operator<< (std::ostream &, const gdk::Quaternion &);
}

#endif
