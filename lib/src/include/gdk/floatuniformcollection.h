// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#ifndef GDK_GFX_FLOATUNIFORMCOLLECTION_H
#define GDK_GFX_FLOATUNIFORMCOLLECTION_H

#include <gdk/uniformcollection.h>

#include <iosfwd>
#include <memory>

namespace gdk
{
    /*!
      Manages and supplies float data for shaderprogram consumption
    */
    class FloatUniformCollection final : public UniformCollection<std::shared_ptr<float>>
    {
        friend std::ostream& operator<< (std::ostream &, const FloatUniformCollection &);
      
    public:
        // Public methods
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        // Mutating operators
        FloatUniformCollection &operator=(const FloatUniformCollection &) = delete;
        FloatUniformCollection &operator=(FloatUniformCollection &&) = delete;
      
        // Constructors, destructors
        FloatUniformCollection() = default;
        FloatUniformCollection(const FloatUniformCollection &) = delete;
        FloatUniformCollection(FloatUniformCollection &&) = delete;
        ~FloatUniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const FloatUniformCollection &);
}

#endif
