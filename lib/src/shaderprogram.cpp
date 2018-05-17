// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-02.
#include "gdk/shaderprogram.h"
//std inc
#include <iostream>
#include <sstream>
//gdk inc
//#include "Debug/Logger.h"
//#include "Debug/Exception.h"

using namespace GDK;
using namespace GFX;

namespace
{
    //constexpr char TAG[] = "ShaderProgram";
}

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::ShaderProgram &a) 
{
    GLint activeAttribs = 0, activeUniforms = 0;
    glGetProgramiv(a.m_ProgramHandle, GL_ACTIVE_ATTRIBUTES, &activeAttribs);
    glGetProgramiv(a.m_ProgramHandle, GL_ACTIVE_UNIFORMS, &activeUniforms);
    
    s.clear(); s
    << "{"
    << "m_Name: "            << a.m_Name          << ", "
    << "m_Handle: "          << a.m_ProgramHandle << ", "
    << "Active attributes: " << activeAttribs     << ", "
    << "Active uniforms: "   << activeUniforms
    << "}";
    
    return s;
}

ShaderProgram::ShaderProgram(const std::string &aName, const std::string &aVertexSource, const std::string &aFragmentSource)
: m_Name(aName)
, m_ProgramHandle([&]()
{
    // Compile vertex stage
    const char *const vertex_shader = aVertexSource.c_str();
    const GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, 0);
    glCompileShader(vs);
 
    // Compile fragment stage
    const char *const fragment_shader = aFragmentSource.c_str();
    const GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, 0);
    glCompileShader(fs);
    
    // Link the program
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vs);
    glAttachShader(programHandle, fs);
    glLinkProgram(programHandle);
    
    GLint status = -1;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        /*std::ostringstream message;
        
        message << "The shader: \"" << aName << "\" has failed to compile!" << std::endl
        << std::endl << "program compilation log: " <<         GLH::GetProgramInfoLog(programHandle) << std::endl
        << std::endl << "vertex shader compilation log: " <<   GLH::GetShaderInfoLog(vs) << std::endl
        << std::endl << "fragment shader compilation log: " << GLH::GetShaderInfoLog(fs);*/
        
        //throw std::runtime_error(message.str());//throw GDK::Exception(TAG, message.str());
        throw std::runtime_error("Shader failed to compile");
    }

    return programHandle;
}())
{}

ShaderProgram::ShaderProgram(ShaderProgram &&aShaderProgram) 
{
    m_Name =          std::move(aShaderProgram.m_Name);
    m_ProgramHandle = std::move(aShaderProgram.m_ProgramHandle);
    
    aShaderProgram.m_ProgramHandle = 0;
}

ShaderProgram::~ShaderProgram() 
{
    if (m_ProgramHandle > 0) glDeleteProgram(m_ProgramHandle);
}

GLuint ShaderProgram::useProgram() const 
{
    glUseProgram(m_ProgramHandle);
    //glDrawCalls();
    
    return m_ProgramHandle;
}

std::string ShaderProgram::getName() const 
{
    return m_Name;
}
    
/*GLuint ShaderProgram::getHandle() const 
{
    return m_ProgramHandle;
}*/
