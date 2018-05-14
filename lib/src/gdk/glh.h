// Project: GDK
// Created on 17-07-02.
#ifndef GDK_GFX_GLH_H
#define GDK_GFX_GLH_H

/*!
 OpenGL header for GDK
 includes gl functions from glew and declares C++ friendly helpers in the GLH namespace
 */

namespace GDK{namespace GFX{struct Color;}}
/*namespace GDK{namespace Math{struct IntVector2;}}
namespace GDK{namespace Math{struct Vector2;}}
namespace GDK{namespace Math{struct Vector3;}}
namespace GDK{namespace Math{struct Vector4;}}
namespace GDK{namespace Math{struct Mat4x4;}}*/

namespace GLH
{
    // GDK-type friendly conveniences
    void ClearColor(const GDK::GFX::Color &aColor);
    /*void Viewport(const GDK::Math::IntVector2 &aPos, const GDK::Math::IntVector2 &aSize);
      void Scissor(const GDK::Math::IntVector2 &aPos, const GDK::Math::IntVector2 &aSize);
    
    // Error detection & logging
    std::string GetShaderInfoLog(const GLuint aShaderStageHandle);
    std::string GetProgramInfoLog(const GLuint aShaderProgramHandle);
    bool GetError(std::string *aErrorCode = nullptr);
    //std::vector<std::string> GetErrors();
    //void LogErrors(const bool &aDoNotLogIfNoErrors = false);
    void ClearErrors();

    // Vertex binding
    bool EnableVertexAttribute(const std::string &aAttributeName, const GLuint aProgramHandle, const int aAttributeSize, const int aAttributeOffset, const int aTotalNumberOfVertexAttributeComponents);

    //Uniform binding
    bool BindTextureUniform(const GLuint aShaderHandle, const std::string &aUniformName, const GLuint aTextureHandle, const int aTextureUnit);//, final GLenum &aTextureType);
    bool Bind1FloatUniform (const GLuint aShaderHandle, const std::string &aUniformName, const float aScalar);
    bool Bind2FloatUniform (const GLuint aShaderHandle, const std::string &aUniformName, const GDK::Math::Vector2 &aVector2);
    bool Bind3FloatUniform (const GLuint aShaderHandle, const std::string &aUniformName, const GDK::Math::Vector3 &aVector3);
    bool Bind4FloatUniform (const GLuint aShaderHandle, const std::string &aUniformName, const GDK::Math::Vector4 &aVector4);
    bool BindMatrix4x4     (const GLuint aShaderHandle, const std::string &aUniformName, const GDK::Math::Mat4x4  &aMatrix4x4);*/
}

#endif /* GDK_GFX_GL_H  */
