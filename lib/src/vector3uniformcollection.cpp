// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#include "Vector3UniformCollection.h"
#include "Math/Vector3.h"
#include "GL.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace GFX;

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::Vector3UniformCollection &a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto& pair : a.m_Map)
        s << i << ": " << "{Name: " << pair.first << ", " << "Vector3: " << *pair.second.get() << "}";
    
    s << "}";
    
    return s;
}

void Vector3UniformCollection::bind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind3FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector3UniformCollection::unbind(const GFXuint aProgramHandle)
{
    for (auto &pair : m_Map)
        GLH::Bind3FloatUniform(aProgramHandle, pair.first, Math::Vector3::Zero);
}
