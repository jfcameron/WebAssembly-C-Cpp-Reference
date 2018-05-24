// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_VECTOR3UNIFORMCOLLECTION_H
#define GDK_GFX_VECTOR3UNIFORMCOLLECTION_H

//gdk inc
#include "UniformCollection.h"
//std inc
#include <iosfwd>

namespace GDK{namespace Math{struct Vector3;}}

namespace GDK
{
    namespace GFX
    {
        /*!
         Manages and supplies Vector3 data for shaderprogram consumption
         */
        class Vector3UniformCollection final : public UniformCollection<std::shared_ptr<Math::Vector3>>
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Vector3UniformCollection &);
      
        public:
            // Public methods
            void bind(const GFXuint aProgramHandle) override;
            void unbind(const GFXuint aProgramHandle) override;
            
            // Mutating operators
            Vector3UniformCollection &operator=(const Vector3UniformCollection &) = delete;
            Vector3UniformCollection &operator=(Vector3UniformCollection &&) = delete;
            
            // Constructors, destructors
            Vector3UniformCollection() = default;
            Vector3UniformCollection(const Vector3UniformCollection &) = delete;
            Vector3UniformCollection(Vector3UniformCollection &&) = delete;
            ~Vector3UniformCollection() = default;
      
        };

        std::ostream &operator<< (std::ostream &, const GFX::Vector3UniformCollection &);
    }
}

#endif /* GDK_GFX_VECTOR3UNIFORMCOLLECTION_H  */
