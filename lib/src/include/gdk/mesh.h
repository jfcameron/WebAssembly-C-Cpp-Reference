// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#ifndef GDK_GFX_MESH_H
#define GDK_GFX_MESH_H

//#include "DataTypes.h"
#include <gdk/vertexformat.h>

#include <iosfwd>
#include <string>

namespace GDK
{
    namespace GFX
    {
        /*!
         Vertex data representing a 3D graphical object
         */
        class Mesh final
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Mesh &);
            
        public:
            /*!
             Hint to the graphics device about how the vertex data will be used.
             Generally, dynamic data (data that is likely to be frequently rewritten) will be placed
             in video memory with fast read write speeds while static will be placed in slower (and more plentiful)
             video memory. Exact behaviours are implementation specific.
             */
            enum class Type
            {
                Static,
                Dynamic
            };
            
            /*
             Determines the primitive type used at the primitive assembly stage.
             */
            enum class PrimitiveMode
            {
                Triangles,
                Lines,
                Points
            };
            
        private:
            // Data members
            std::string m_Name = {};
            
            GLuint m_IndexBufferHandle = 0;
            GLsizei m_IndexCount       = 0;
            
            GLuint m_VertexBufferHandle = 0;
            GLsizei m_VertexCount       = 0;
            
            VertexFormat m_VertexFormat = VertexFormat::Pos3uv2;
            
            PrimitiveMode m_PrimitiveMode = PrimitiveMode::Triangles;
            
        public:
            // Accessors
            std::string const &getName() const;
            GLuint getHandle() const;
            
            // Public functions
            void draw(const GLuint aShaderProgramHandle) const;
            void updateVertexData(const std::vector<GLfloat> &aNewVertexData, const VertexFormat &aNewVertexFormat, const Mesh::Type &aNewType = Type::Dynamic);
            
            // Mutating operators
            Mesh &operator=(const Mesh &) = delete;
            Mesh &operator=(Mesh &&) = delete;
      
            // Constructors, destructors
            Mesh(const std::string &aName, const Mesh::Type &aType, const VertexFormat &aVertexFormat,
                 const std::vector<GLfloat> &aVertexData, const std::vector<GLushort> &aIndexData = std::vector<GLushort>(), const PrimitiveMode &aPrimitiveMode = PrimitiveMode::Triangles);
            Mesh() = delete;
            Mesh(const Mesh &) = delete;
            Mesh(Mesh &&);
            ~Mesh();
        };

        std::ostream &operator<< (std::ostream &, const GFX::Mesh &);
    }
}

#endif
