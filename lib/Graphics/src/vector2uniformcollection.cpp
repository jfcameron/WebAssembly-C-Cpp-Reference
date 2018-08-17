// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/glh.h>
#include <gdk/opengl.h>
#include <gdk/vector2.h>
#include <gdk/vector2uniformcollection.h>

#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &s, const Vector2UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto& pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector2: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector2UniformCollection::bind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::Bind2FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector2UniformCollection::unbind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::Bind2FloatUniform(aProgramHandle, pair.first, Vector2::Zero);
}
