// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#include <gdk/vertexformat.h>
#include <gdk/glh.h>
//#include "Debug/Logger.h"

#include <gdk/opengl.h>

#include <iostream>

using namespace GDK;
using namespace GFX;

static constexpr char TAG[] = "VertexFormat";

// Special values
VertexFormat const VertexFormat::Pos3uv2Norm3(
{
    {"a_Position",3},
    {"a_UV"      ,2},
    {"a_Normal"  ,3}
});

VertexFormat const VertexFormat::Pos3uv2(
{
    {"a_Position",3},
    {"a_UV"      ,2}
});

VertexFormat const VertexFormat::Pos3(
{
    {"a_Position",3}
});

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::VertexFormat &a)
{
    (void)a;
    
    s << "{";
    s << TAG << " << not implemented.";
    s << "}";
    
    return s;
}

VertexFormat::VertexFormat(const std::vector<VertexAttribute> &aAttributes)
: m_Format(aAttributes)
, m_SumOfAttributeComponents(([aAttributes]() -> int
{
    int buf = 0;
    
    for (auto attribute : aAttributes)
        buf += attribute.size;
    
    return buf;
    
})())
{}

void VertexFormat::enableAttributes(const GLuint aShaderProgramHandle) const
{
    int attributeOffset = 0;
    
    for(auto attribute : m_Format)
    {
        std::string attributeName = attribute.name;
        int attributeSize = attribute.size;
        
        GLH::EnableVertexAttribute(attributeName, aShaderProgramHandle, attributeSize, attributeOffset,
                                   m_SumOfAttributeComponents);
        
        attributeOffset += attributeSize;
    }
}

int VertexFormat::getSumOfAttributeComponents() const
{
    return m_SumOfAttributeComponents;
}
