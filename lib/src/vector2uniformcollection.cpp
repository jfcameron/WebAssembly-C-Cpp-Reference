// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#include "Vector2UniformCollection.h"
//gdk inc
#include "GL.h"
#include "Math/Vector2.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace GFX;

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::Vector2UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto& pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector2: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector2UniformCollection::bind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind2FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector2UniformCollection::unbind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind2FloatUniform(aProgramHandle, pair.first, Math::Vector2::Zero);
}
