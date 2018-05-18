// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#include <gdk/texture.h>

#include <stb/stb_image.h>

#include <iostream>
#include <vector>

using namespace GDK;
using namespace GFX;

namespace
{
    constexpr char TAG[] = "Texture";
}

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::Texture &a)
{
    s.clear(); s
    << "{"
    << "m_Name: "   << a.m_Name   << ", "
    << "m_Handle: " << a.m_Handle
    << "}";
    
    return s;
}

Texture::Texture(const std::string &aName, const std::vector<const GLubyte> &aTextureData)
    : m_Name(aName)
{
    //decode the png rgba32 data
    int width, height, components;
    if (GLubyte *const decodedData = stbi_load_from_memory(&aTextureData[0], static_cast<int>(aTextureData.size()), &width, &height, &components, 4))
    {
        //Copy the texture data to video memory
        glGenTextures(1, &m_Handle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Handle);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, decodedData );
    
        //Apply texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
        //Cleanup
        glBindTexture( GL_TEXTURE_2D,0);
        stbi_image_free(decodedData);
    }
    else throw std::runtime_error(std::string(TAG).append(" could not decode RGBA32 PNG data"));//throw GDK::Exception(TAG, message.str());
}

Texture::Texture(Texture &&other)
{
    m_Name   = std::move(other.m_Name);
    m_Handle = std::move(other.m_Handle);
    
    other.m_Handle = 0;
}

Texture::~Texture()
{
    if (m_Handle > 0) glDeleteBuffers(1, &m_Handle);
}

std::string Texture::getName()const
{
    return m_Name;
}

GLuint Texture::getHandle()const
{
    return m_Handle;
}
