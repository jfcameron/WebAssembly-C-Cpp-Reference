// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#ifndef GDK_GFX_MODEL_H
#define GDK_GFX_MODEL_H

#include <gdk/floatuniformcollection.h>
#include <gdk/mat4x4.h>
#include <gdk/mat4x4uniformcollection.h>
#include <gdk/shaderprogram.h>
#include <gdk/textureuniformcollection.h>
#include <gdk/vector2uniformcollection.h>
#include <gdk/vector3uniformcollection.h>
#include <gdk/vector4uniformcollection.h>
#include <gdk/vertexdata.h>

#include <iosfwd>
#include <memory>

namespace gdk
{
    struct Mat4x4;
    
    /*!
      Represents an observable 3D object. 
      Contains a VertexData, a set of uniform collections, a shader, animations, a skeleton.
    */
    class Model final
    {
        friend std::ostream &operator<< (std::ostream &, const Model &);
            
        // Data members
        std::string m_Name = {};
        Mat4x4 m_ModelMatrix = {};
        default_ptr<VertexData> m_VertexData;
        default_ptr<ShaderProgram> m_ShaderProgram;
            
        TextureUniformCollection m_Textures = {};
        FloatUniformCollection   m_Floats   = {};
        Vector2UniformCollection m_Vector2s = {};
        Vector3UniformCollection m_Vector3s = {};
        Vector4UniformCollection m_Vector4s = {};
        Mat4x4UniformCollection  m_Mat4x4s  = {};
            
    public:
        // Accessors
        void setVertexData(const default_ptr<VertexData> &);
        
        void setTexture(const std::string &aUniformName, const default_ptr<Texture>     &aTexture);
        void setFloat  (const std::string &aUniformName, const std::shared_ptr<float>   &aFloat  );
        void setVector2(const std::string &aUniformName, const std::shared_ptr<Vector2> &aVector2);
        void setVector3(const std::string &aUniformName, const std::shared_ptr<Vector3> &aVector3);
        void setVector4(const std::string &aUniformName, const std::shared_ptr<Vector4> &aVector4);
        void setMat4x4 (const std::string &aUniformName, const Mat4x4                   &aMat4x4 );
            
        const Mat4x4 &getModelMatrix() const;
        void setModelMatrix(const Vector3 &aWorldPos, const Quaternion &aRotation);
            
        // public methods
        void draw(const Mat4x4 &aViewMatrix, const Mat4x4 &aProjectionMatrix);
            
        // Mutating operators
        Model &operator=(const Model &) = delete;
        Model &operator=(Model &&) = delete;
      
        // Constructors, destructors
        Model(const std::string &aName, const default_ptr<VertexData> &, const default_ptr<ShaderProgram> &);
        Model();
        Model(const Model &) = default;
        Model(Model &&) = default;
        ~Model() = default;
    };
        
    std::ostream &operator<< (std::ostream &, const Model &);
}

#endif
