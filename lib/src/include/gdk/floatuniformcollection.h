// © 2018 Joseph Cameron - All Rights Reserved

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
        void bind(const GLuint aProgramHandle) override;
        void unbind(const GLuint aProgramHandle) override;
            
        FloatUniformCollection &operator=(const FloatUniformCollection &) = delete;
        FloatUniformCollection &operator=(FloatUniformCollection &&) = delete;
      
        FloatUniformCollection() = default;
        FloatUniformCollection(const FloatUniformCollection &) = default;
        FloatUniformCollection(FloatUniformCollection &&) = default;
        ~FloatUniformCollection() = default;
    };

    std::ostream &operator<< (std::ostream &, const FloatUniformCollection &);
}

#endif
