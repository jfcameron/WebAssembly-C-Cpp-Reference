// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.

#include <gdk/vector3uniformcollection.h>
#include <gdk/vector3.h>
#include <gdk/opengl.h>
#include <gdk/glh.h>

#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &s, const Vector3UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto& pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector3: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector3UniformCollection::bind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind3FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector3UniformCollection::unbind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind3FloatUniform(aProgramHandle, pair.first, Vector3::Zero);
}
