// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#include <gdk/mat4x4uniformcollection.h>
#include <gdk/opengl.h>
#include <gdk/glh.h>

#include <iostream>

namespace gdk
{
std::ostream &operator<<(std::ostream &s, const Mat4x4UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto &pair : a.m_Map)
    {
        auto mat4x4 = pair.second;
        s << i << ": " << "{Name: " << pair.first << ", " << "Matrix: " << mat4x4 << "}";
    }
    
    s << "}";
    
    return s;
}

void Mat4x4UniformCollection::bind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::BindMatrix4x4(aProgramHandle, pair.first, pair.second);
}

void Mat4x4UniformCollection::unbind(const GLuint aProgramHandle)
{
    for (auto &pair : m_Map)
        glh::BindMatrix4x4(aProgramHandle, pair.first, Mat4x4::Identity);    
}
}
