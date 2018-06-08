// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/exception.h>
#include <gdk/glh.h>
#include <gdk/shaderprogram.h>

#include <iostream>
#include <sstream>

using namespace gdk;

static constexpr char TAG[] = "ShaderProgram";

//uniform float _Time;
//uniform mat4  _Model;
//uniform mat4  _View;
//uniform mat4  _Projection;
//gl_Position = _Projection * _View * _Model * vec4(a_Position,1.0);

const gdk::lazy_ptr<gdk::ShaderProgram> ShaderProgram::PinkShaderOfDeath([]()
{
    const std::string vertexShaderSource = R"V0G0N(
    #version 100
    
    //Uniforms
    uniform mat4 _MVP;

    //VertIn
    attribute highp vec3 a_Position;

    void main ()
    {
        gl_Position = _MVP * vec4(a_Position,1.0);
    }
    )V0G0N";

    const std::string fragmentShaderSource = R"V0G0N(
    precision mediump float;
            
    const vec4 DEATHLY_PINK = vec4(1,0.2,0.8,1);

    void main()
    {
        gl_FragColor = DEATHLY_PINK;
    }
    )V0G0N";

    return new gdk::ShaderProgram("PinkShaderOfDeath", vertexShaderSource, fragmentShaderSource);
});

const gdk::lazy_ptr<gdk::ShaderProgram> ShaderProgram::AlphaCutOff([]()
{
    const std::string vertexShaderSource = R"V0G0N(
    #version 100

    //hack
    uniform mat4  _Model;
    uniform mat4  _View;
    uniform mat4  _Projection;

    //Uniforms
    uniform mat4 _MVP;
          
    //VertIn
    attribute highp   vec3 a_Position;
    attribute mediump vec2 a_UV;

    //FragIn
    varying mediump vec2 v_UV;

    void main ()
    {
        gl_Position = _MVP * vec4(a_Position,1.0);
               
        v_UV = a_UV;
    }
    )V0G0N";

    const std::string fragmentShaderSource = R"V0G0N(
    #version 100
    precision mediump float;
            
    //Uniforms
    uniform sampler2D _Texture;
            
    //FragIn
    varying lowp vec2 v_UV;

    void main()
    {
        vec4 frag = texture2D(_Texture, v_UV);
                
        if (frag[3] < 1.0) discard;
                
        gl_FragColor = frag;                        
    }
    )V0G0N";
            
    return new gdk::ShaderProgram("AlphaCutOff", vertexShaderSource, fragmentShaderSource);
});

std::ostream &gdk::operator<<(std::ostream &s, const ShaderProgram &a) 
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
        std::ostringstream message;
        
        message << "The shader: \"" << aName << "\" has failed to compile!" << std::endl
        << std::endl << "program compilation log: " <<         glh::GetProgramInfoLog(programHandle) << std::endl
        << std::endl << "vertex shader compilation log: " <<   glh::GetShaderInfoLog(vs) << std::endl
        << std::endl << "fragment shader compilation log: " << glh::GetShaderInfoLog(fs);
        
        throw gdk::Exception(TAG, message.str());
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
    
GLuint ShaderProgram::getHandle() const 
{
    return m_ProgramHandle;
}
