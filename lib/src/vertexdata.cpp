// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 17-07-03.
#include <gdk/vertexdata.h>
#include <gdk/glh.h>
#include "gdk/exception.h"
//#include "Debug/Logger.h"

#include <gdk/opengl.h>

#include <iostream>

using namespace gdk;


static constexpr char TAG[] = "VertexData";

std::ostream& gdk::operator<<(std::ostream &s, const VertexData &a)
{
    s.clear(); s
    << "{"
    << "Name: "         << a.m_Name               << ", "
    << "Handle: "       << a.m_VertexBufferHandle << ", "
    << "VertexCount: "  << a.m_VertexCount        << ", "
    << "VertexFormat: " << a.m_VertexFormat
    << "}";
    
    return s;
}

static GLenum VertexDataTypeToOpenGLDrawType(const VertexData::Type &aType)
{
    switch (aType)
    {
        case VertexData::Type::Dynamic:
            return GL_DYNAMIC_DRAW;
        
        case VertexData::Type::Static:
            return GL_STATIC_DRAW;
    }
}

static GLenum PrimitiveModeToOpenGLPrimitiveType(const VertexData::PrimitiveMode &aPrimitiveMode)
{
    switch (aPrimitiveMode)
    {
        case VertexData::PrimitiveMode::Triangles:
            return GL_TRIANGLES;
            
        case VertexData::PrimitiveMode::Lines:
            return GL_LINES;
        
        case VertexData::PrimitiveMode::Points:
            return GL_POINTS;
    }
}

void VertexData::draw(const GLuint aShaderProgramHandle) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferHandle);
    
    m_VertexFormat.enableAttributes(aShaderProgramHandle);
    
    GLenum primitiveMode = PrimitiveModeToOpenGLPrimitiveType(m_PrimitiveMode);
    
    if (m_IndexBufferHandle > 0)
    {
        //Debug::log(TAG, m_IndexBufferHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferHandle);
        
        glDrawElements
        (
            primitiveMode,
            m_IndexCount,
            GL_UNSIGNED_SHORT,
            static_cast<void *>(0)
        );
    }
    else glDrawArrays(primitiveMode, 0, m_VertexCount);
}

void VertexData::updateVertexData(const std::vector<GLfloat> &aNewVertexData, const VertexFormat &aNewVertexFormat, const VertexData::Type &aNewType)
{
    m_VertexFormat = aNewVertexFormat;
    m_VertexCount  = static_cast<GLsizei>(aNewVertexData.size()/aNewVertexFormat.getSumOfAttributeComponents());
    GLint type = VertexDataTypeToOpenGLDrawType(aNewType);
    
    glBindBuffer (GL_ARRAY_BUFFER, m_VertexBufferHandle);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * aNewVertexData.size(), &aNewVertexData[0], type);
    glBindBuffer (GL_ARRAY_BUFFER,0);
}

// Constructors & Destructors
VertexData::VertexData(const std::string &aName, const VertexData::Type &aType, const VertexFormat &aVertexFormat,
           const std::vector<GLfloat> &aVertexData, const std::vector<GLushort> &aIndexData,
           const PrimitiveMode &aPrimitiveMode)
: m_Name(aName)
, m_IndexBufferHandle([&aIndexData, &aType]() -> GLuint
{
    //Create and populate the IBO
    GLuint ibo = 0;
    
    if (aIndexData.size() > 0)
    {
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * aIndexData.size(), &aIndexData[0],
                     VertexDataTypeToOpenGLDrawType(aType));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
        std::string errorCode;
        
        if (glh::GetError(&errorCode)) gdk::Exception(TAG, errorCode);
    }
    
    return ibo;
}())
, m_IndexCount((GLsizei)aIndexData.size())
, m_VertexBufferHandle([&aVertexData, &aType]() -> GLuint
{
    if (aVertexData.size() <= 0) gdk::Exception(TAG, "bad vertex data");
    
    // Create and populate a VBO
    GLuint vbo = 0;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * aVertexData.size(), &aVertexData[0], VertexDataTypeToOpenGLDrawType(aType));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    std::string errorCode;

    if (glh::GetError(&errorCode)) gdk::Exception(TAG, errorCode);
    
    return vbo;
}())
, m_VertexCount((int)aVertexData.size()/aVertexFormat.getSumOfAttributeComponents())
, m_VertexFormat(aVertexFormat)
, m_PrimitiveMode(aPrimitiveMode)
{}

VertexData::~VertexData()
{
    if (m_VertexBufferHandle > 0)
        glDeleteBuffers(1, &m_VertexBufferHandle);
    
    if (m_IndexBufferHandle > 0)
        glDeleteBuffers(1, &m_IndexBufferHandle);
}

VertexData::VertexData(VertexData &&a)
{
    m_Name               = std::move(a.m_Name);
    m_IndexBufferHandle  = std::move(a.m_IndexBufferHandle);
    m_IndexCount         = std::move(a.m_IndexCount);
    m_VertexBufferHandle = std::move(a.m_VertexBufferHandle);
    m_VertexCount        = std::move(a.m_VertexCount);
    m_VertexFormat       = std::move(a.m_VertexFormat);
    m_PrimitiveMode      = std::move(a.m_PrimitiveMode);
    
    a.m_IndexBufferHandle  = 0;
    a.m_VertexBufferHandle = 0;
}

// Accessors
std::string const &VertexData::getName()const
{
    return m_Name;
}

GLuint VertexData::getHandle()const
{
    return m_VertexBufferHandle;
}
