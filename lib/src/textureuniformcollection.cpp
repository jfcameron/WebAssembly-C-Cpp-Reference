// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-09.
#include "TextureUniformCollection.h"
//gdk inc
#include "GL.h"
//std inc
#include <iostream>

using namespace GDK;
using namespace GFX;

std::ostream& GDK::GFX::operator<<(std::ostream& s, const GFX::TextureUniformCollection& a)
{
    s.clear(); s
    
    << "{";
    
    size_t i = 0;
    
    for (auto &pair : a.m_Map)
    {
        auto texture = pair.second.lock();
        s << i << ": " << "{Name: " << pair.first << ", " << "Texture: " << *texture.get() << "}";
    }
    
    s << "}";
    
    return s;
}

void TextureUniformCollection::bind(const GFXuint aProgramHandle)
{
    int i = 0;
    for (auto &pair : m_Map)
    {
        auto texture = pair.second.lock();
        GLH::BindTextureUniform(aProgramHandle, pair.first, texture->getHandle(), i++);
    }
}

void TextureUniformCollection::unbind(const GFXuint aProgramHandle)
{
    int i = 0;
    for (auto &pair : m_Map)
        GLH::BindTextureUniform(aProgramHandle, pair.first, 0, i++);
}
