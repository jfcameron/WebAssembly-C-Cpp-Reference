// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/floatuniformcollection.h>
#include <gdk/glh.h>

#include <iostream>

namespace gdk
{
std::ostream &operator<<(std::ostream &s, const FloatUniformCollection &a)
{
    s.clear(); s
    << "{";
    
    size_t i = 0;
    
    for (auto &pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Float: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void FloatUniformCollection::bind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind1FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void FloatUniformCollection::unbind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind1FloatUniform(aProgramHandle, pair.first, 0);
}
}
