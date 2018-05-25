// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#include "gdk/vector4uniformcollection.h"
#include "gdk/opengl.h"
#include "gdk/glh.h"
#include "gdk/vector4.h"

#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &s, const Vector4UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto &pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector4: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector4UniformCollection::bind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind4FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector4UniformCollection::unbind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::Bind4FloatUniform(aProgramHandle, pair.first, Vector4::Zero);
}
