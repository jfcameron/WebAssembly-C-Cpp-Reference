// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#include <gdk/mesh.h>
#include <gdk/glh.h>
//#include "Debug/Exception.h"
//#include "Debug/Logger.h"

#include <GLES2/gl2.h>

#include <iostream>

using namespace GDK;
using namespace GFX;

namespace
{
    //constexpr char TAG[] = "Mesh";
}

std::ostream& GDK::GFX::operator<<(std::ostream &s, const GFX::Mesh &a)
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

static GLenum MeshTypeToOpenGLDrawType(const Mesh::Type &aType)
{
    switch (aType)
    {
        case Mesh::Type::Dynamic:
            return GL_DYNAMIC_DRAW;
        
        case Mesh::Type::Static:
            return GL_STATIC_DRAW;
    }
}

static GLenum PrimitiveModeToOpenGLPrimitiveType(const Mesh::PrimitiveMode &aPrimitiveMode)
{
    switch (aPrimitiveMode)
    {
        case Mesh::PrimitiveMode::Triangles:
            return GL_TRIANGLES;
            
        case Mesh::PrimitiveMode::Lines:
            return GL_LINES;
        
        case Mesh::PrimitiveMode::Points:
            return GL_POINTS;
    }
}

void Mesh::draw(const GLuint aShaderProgramHandle) const
{
    glBindBuffer( GL_ARRAY_BUFFER, m_VertexBufferHandle);
    
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
            static_cast<void*>(0)
        );
    }
    else
    {
        glDrawArrays( primitiveMode, 0, m_VertexCount );
    }
}

void Mesh::updateVertexData(const std::vector<GLfloat> &aNewVertexData, const VertexFormat &aNewVertexFormat, const Mesh::Type &aNewType)
{
    m_VertexFormat = aNewVertexFormat;
    m_VertexCount  = static_cast<GLsizei>(aNewVertexData.size()/aNewVertexFormat.getSumOfAttributeComponents());
    GLint type = MeshTypeToOpenGLDrawType(aNewType);
    
    glBindBuffer (GL_ARRAY_BUFFER, m_VertexBufferHandle);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * aNewVertexData.size(), &aNewVertexData[0], type);
    glBindBuffer (GL_ARRAY_BUFFER,0);
}

// Constructors & Destructors
Mesh::Mesh(const std::string &aName, const Mesh::Type &aType, const VertexFormat &aVertexFormat,
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
                     MeshTypeToOpenGLDrawType(aType));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
        std::string errorCode;
        if (GLH::GetError(&errorCode))
            throw std::runtime_error(errorCode);//GDK::Exception(TAG, errorCode);
    }
    
    return ibo;
}())
, m_IndexCount((GLsizei)aIndexData.size())
, m_VertexBufferHandle([&aVertexData, &aType]() -> GLuint
{
    if (aVertexData.size() <= 0)
        throw std::runtime_error("Bad vertex data");//GDK::Exception(TAG, "bad vertex data");
    
    // Create and populate a VBO
    GLuint vbo = 0;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * aVertexData.size(), &aVertexData[0], MeshTypeToOpenGLDrawType(aType));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    std::string errorCode;
    if (GLH::GetError(&errorCode))
        throw std::runtime_error(errorCode);//GDK::Exception(TAG, errorCode);
    
    return vbo;
}())
, m_VertexCount((int)aVertexData.size()/aVertexFormat.getSumOfAttributeComponents())
, m_VertexFormat(aVertexFormat)
, m_PrimitiveMode(aPrimitiveMode)
{}

Mesh::~Mesh()
{
    if (m_VertexBufferHandle > 0)
        glDeleteBuffers(1, &m_VertexBufferHandle);
    
    if (m_IndexBufferHandle > 0)
        glDeleteBuffers(1, &m_IndexBufferHandle);
}

Mesh::Mesh(Mesh&& a)
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
std::string const &Mesh::getName()const
{
    return m_Name;
}

GLuint Mesh::getHandle()const
{
    return m_VertexBufferHandle;
}
