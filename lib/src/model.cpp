// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/camera.h>
#include <gdk/default_ptr.h>
#include <gdk/glh.h>
#include <gdk/logger.h>
#include <gdk/mat4x4.h>
#include <gdk/model.h>
#include <gdk/opengl.h>
#include <gdk/time.h>

#include <iostream>

using namespace gdk;

static constexpr char TAG[] = "Model";

std::ostream& gdk::operator<<(std::ostream& s, const Model& a)
{
    s.clear(); s
    << "{"
    << "Name: "          << a.m_Name                  << ", "
    << "m_ModelMatrix: " << a.m_ModelMatrix           << ", "
    << "Mesh: "          << *a.m_VertexData.lock()    << ", "
    << "ShaderProgram: " << *a.m_ShaderProgram.lock() << ", "
    << "m_Textures: "    << a.m_Textures              << ", "
    << "m_Floats: "      << a.m_Floats                << ", "
    << "m_Vector2s: "    << a.m_Vector2s              << ", "
    << "m_Vector3s: "    << a.m_Vector3s              << ", "
    << "m_Vector4s: "    << a.m_Vector4s
    << "}";
    
    return s;
}

Model::Model(const std::string &aName, const default_ptr<VertexData> &aVertexData, const default_ptr<ShaderProgram> &aShaderProgram)
: m_Name(aName)
, m_VertexData(aVertexData)
, m_ShaderProgram(aShaderProgram)
{}

Model::Model()
    : Model("",
            gdk::default_ptr<gdk::VertexData>(static_cast<std::shared_ptr<gdk::VertexData>>(VertexData::Quad)),
            gdk::default_ptr<gdk::ShaderProgram>(static_cast<std::shared_ptr<gdk::ShaderProgram>>(ShaderProgram::AlphaCutOff)))
{}

void Model::draw(const Mat4x4 &aViewMatrix, const Mat4x4 &aProjectionMatrix)
{
    gdk::log(TAG, *this);

    if (const auto pShader = m_ShaderProgram.lock())
    {
        if (const auto pVertexData = m_VertexData.lock())
        {
            const GLuint programHandle = pShader->useProgram();
    
            //bind this model's uniforms
            m_Textures.bind(programHandle);
            m_Floats  .bind(programHandle);
            m_Vector2s.bind(programHandle);
            m_Vector3s.bind(programHandle);
            m_Vector4s.bind(programHandle);
            m_Mat4x4s .bind(programHandle);
    
            //bind standard uniforms
            const float time      = time::sinceStart();
            const float deltaTime = time::getDeltaTime();
        
            const Mat4x4 p = aProjectionMatrix;
            const Mat4x4 v = aViewMatrix;
            const Mat4x4 m = getModelMatrix();
        
            const auto mvp = p * v * m;
        
            glh::Bind1FloatUniform(programHandle, "_DeltaTime",  deltaTime);
            glh::Bind1FloatUniform(programHandle, "_Time",       time     );
            glh::BindMatrix4x4(programHandle,     "_Model",      m        );
            glh::BindMatrix4x4(programHandle,     "_View",       v        );
            glh::BindMatrix4x4(programHandle,     "_Projection", p        );
            glh::BindMatrix4x4(programHandle,     "_MVP",        mvp      );

            pVertexData->draw(programHandle);
                
            //unbind this model's uniforms
            m_Textures.unbind(programHandle);
            m_Floats  .unbind(programHandle);
            m_Vector2s.unbind(programHandle);
            m_Vector3s.unbind(programHandle);
            m_Vector4s.unbind(programHandle);
            m_Mat4x4s .unbind(programHandle);
        }
    }
}

// Accessors
void Model::setTexture(const std::string &aUniformName, const default_ptr<Texture> &aTexture)
{
    m_Textures.put(aUniformName, aTexture);
}

void Model::setFloat(const std::string &aUniformName, const std::shared_ptr<float> &aFloat)
{
    m_Floats.put(aUniformName, aFloat);
}

void Model::setVector2(const std::string &aUniformName, const std::shared_ptr<Vector2> &aVector2)
{
    m_Vector2s.put(aUniformName, aVector2);
}

void Model::setVector3(const std::string &aUniformName, const std::shared_ptr<Vector3> &aVector3)
{
    m_Vector3s.put(aUniformName, aVector3);
}

void Model::setVector4(const std::string &aUniformName, const std::shared_ptr<Vector4> &aVector4)
{
    m_Vector4s.put(aUniformName, aVector4);
}

void Model::setMat4x4 (const std::string &aUniformName, const Mat4x4 &aMat4x4 )
{
    m_Mat4x4s.put(aUniformName, aMat4x4);
}

const Mat4x4& Model::getModelMatrix() const
{
    return m_ModelMatrix;
}

void Model::setModelMatrix(const Vector3 &aWorldPos, const Quaternion &aRotation, const Vector3 &aScale)
{
    m_ModelMatrix.setToIdentity();
    m_ModelMatrix.translate(aWorldPos);
    m_ModelMatrix.rotate(aRotation);
    m_ModelMatrix.scale(aScale);
}

void Model::setVertexData(const default_ptr<VertexData> &a)
{
    m_VertexData = a;
}
