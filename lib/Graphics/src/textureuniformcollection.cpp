// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/glh.h>
#include <gdk/logger.h>
#include <gdk/opengl.h>
#include <gdk/textureuniformcollection.h>

#include <nlohmann/json.hpp>

#include <iostream>

using namespace gdk;

constexpr auto TAG = "textureuniform";

std::ostream& gdk::operator<<(std::ostream& s, const TextureUniformCollection& a)
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

void TextureUniformCollection::bind(const GLuint aProgramHandle) const
{
    int i = 0;
    for (auto &pair : m_Map)
    {
        //gdk::log(TAG, "start a bind");

        auto texture = pair.second.lock();
        glh::BindTextureUniform(aProgramHandle, pair.first, texture->getHandle(), i++);

        //gdk::log(TAG, "end a bind");
    }
}

void TextureUniformCollection::unbind(const GLuint aProgramHandle) const
{
    int i = 0;    
    for (auto &pair : m_Map) glh::BindTextureUniform(aProgramHandle, pair.first, 0, i++);
}
