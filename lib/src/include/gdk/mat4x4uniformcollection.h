// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#ifndef GDK_GFX_MAT4X4UNIFORMCOLLECTION_H
#define GDK_GFX_MAT4X4UNIFORMCOLLECTION_H

#include "gdk/mat4x4.h"
#include "gdk/uniformcollection.h"

#include <iosfwd>

namespace gdk
{
    /*!
      No description provided for Mat4x4UniformCollection
    */
    class Mat4x4UniformCollection final : public gdk::UniformCollection<gdk::Mat4x4>
    {
        friend std::ostream& operator<< (std::ostream&, const Mat4x4UniformCollection&);
      
    public:
        // Public methods
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
      
        // Mutating operators
        Mat4x4UniformCollection& operator=(const Mat4x4UniformCollection&) = delete;
      
        // Constructors, destructors
        Mat4x4UniformCollection() = default;
        Mat4x4UniformCollection(const Mat4x4UniformCollection&) = default;
        Mat4x4UniformCollection(Mat4x4UniformCollection&&) = default;
        ~Mat4x4UniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const Mat4x4UniformCollection &);
}

#endif
