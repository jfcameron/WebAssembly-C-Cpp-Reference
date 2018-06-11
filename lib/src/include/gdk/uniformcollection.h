// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_UNIFORMCOLLECTION_H
#define GDK_GFX_UNIFORMCOLLECTION_H

#include <gdk/opengl.h>

#include <iosfwd>
#include <string>
#include <map>

namespace gdk
{
    /*!
      UniformCollection is used to supply data to shaderprograms.
      It is a baseclass that manages, binds and unbinds a collection of T to a
      shaderprogram
    */
    template<typename T> class UniformCollection
    {
    protected:
        std::map<std::string,T> m_Map = {};
            
    public:
        void put(const std::string &aName, const T &aItem)
        {
            m_Map.insert({aName, aItem});
        }
            
        T get(const std::string &aName) const
        {
            return m_Map.find(aName);
        }
            
        virtual void bind(const GLuint aProgramHandle) =   0;
        virtual void unbind(const GLuint aProgramHandle) = 0;
            
        UniformCollection &operator=(const UniformCollection &) = delete;
        UniformCollection &operator=(UniformCollection &&) = delete;
      
        UniformCollection() = default;
        UniformCollection(const UniformCollection &) = default;
        UniformCollection(UniformCollection &&) = default;
        virtual ~UniformCollection() = default;
    };
}

#endif
