// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/glh.h>
#include <gdk/opengl.h>
#include <gdk/vertexformat.h>

#include <iostream>

using namespace gdk;


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

std::ostream &gdk::operator<<(std::ostream &s, const VertexFormat &a)
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
        
        glh::EnableVertexAttribute(attributeName, aShaderProgramHandle, attributeSize, attributeOffset,
                                   m_SumOfAttributeComponents);
        
        attributeOffset += attributeSize;
    }
}

int VertexFormat::getSumOfAttributeComponents() const
{
    return m_SumOfAttributeComponents;
}
