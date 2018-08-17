// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_MODEL_H
#define GDK_GFX_MODEL_H

#include <gdk/floatuniformcollection.h>
#include <gdk/mat4x4.h>
#include <gdk/mat4x4uniformcollection.h>
#include <gdk/shaderprogram.h>
#include <gdk/textureuniformcollection.h>
#include <gdk/vector2uniformcollection.h>
#include <gdk/vector3.h>
#include <gdk/vector3uniformcollection.h>
#include <gdk/vector4uniformcollection.h>
#include <gdk/vertexdata.h>

#include <iosfwd>
#include <memory>

namespace gdk
{
    struct Mat4x4;
    
    //! Represents an observable 3D object. 
    /// Contains a VertexData, a set of uniform collections, a shader, animations, a skeleton.
    ///
    /// \Warning: I think this class contains a bit too much implementation. (see draw method). It seems weird that "Model"
    /// is responsible for binding and clearing all uniform data for the shader. the shaderprogram and uniform data (textures etc.) Should probably
    /// be broken out into a new abstraction. This work would be a good match for the "material" class seen in many engines.
    class Model final
    {
        friend std::ostream &operator<< (std::ostream &, const Model &);
            
        std::string m_Name =   {}; //!< Resource Identifier
        Mat4x4 m_ModelMatrix = {}; //!< Position in the world
        
        default_ptr<VertexData> m_VertexData;
        default_ptr<ShaderProgram> m_ShaderProgram;
            
        TextureUniformCollection m_Textures = {};
        FloatUniformCollection   m_Floats   = {};
        Vector2UniformCollection m_Vector2s = {};
        Vector3UniformCollection m_Vector3s = {};
        Vector4UniformCollection m_Vector4s = {};
        Mat4x4UniformCollection  m_Mat4x4s  = {};
            
    public:
        void setVertexData(const default_ptr<VertexData> &);
        
        void setTexture(const std::string &aUniformName, const default_ptr<Texture>     &aTexture);
        void setFloat  (const std::string &aUniformName, const std::shared_ptr<float>   &aFloat  );
        void setVector2(const std::string &aUniformName, const std::shared_ptr<Vector2> &aVector2);
        void setVector3(const std::string &aUniformName, const std::shared_ptr<Vector3> &aVector3);
        void setVector4(const std::string &aUniformName, const std::shared_ptr<Vector4> &aVector4);
        void setMat4x4 (const std::string &aUniformName, const Mat4x4                   &aMat4x4 );
            
        void setModelMatrix(const Vector3 &aWorldPos, const Quaternion &aRotation, const Vector3 &aScale = Vector3::One);
        const Mat4x4 &getModelMatrix() const;
            
        void draw(const Mat4x4 &aViewMatrix, const Mat4x4 &aProjectionMatrix);
            
        Model &operator=(const Model &) = delete;
        Model &operator=(Model &&) = delete;
      
        Model(const std::string &aName, const default_ptr<VertexData> &, const default_ptr<ShaderProgram> &);
        Model();
        Model(const Model &) = default;
        Model(Model &&) = default;
        ~Model() = default;
    };
        
    std::ostream &operator<< (std::ostream &, const Model &);
}

#endif
