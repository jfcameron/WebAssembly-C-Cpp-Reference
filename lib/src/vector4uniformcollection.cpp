// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#include "Vector4UniformCollection.h"
//gdk inc
#include "GL.h"
#include "Math/Vector4.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace GFX;

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::Vector4UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto &pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector4: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector4UniformCollection::bind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind4FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector4UniformCollection::unbind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind4FloatUniform(aProgramHandle, pair.first, Math::Vector4::Zero);
}
