// © 2017 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 17-07-03.
#ifndef gdk_GFX_MESH_H
#define gdk_GFX_MESH_H

//#include "DataTypes.h"
#include <gdk/vertexformat.h>

#include <iosfwd>
#include <string>

namespace gdk
{
    namespace GFX
    {
        /*!
         Vertex data representing a 3D graphical object
         */
        class VertexData final
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::VertexData &);
            
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
            
            GLuint m_IndexBufferHandle = {0};
            GLsizei m_IndexCount       = {0};
            
            GLuint m_VertexBufferHandle = {0};
            GLsizei m_VertexCount       = {0};
            
            VertexFormat m_VertexFormat = VertexFormat::Pos3uv2;
            
            PrimitiveMode m_PrimitiveMode = PrimitiveMode::Triangles;
            
        public:
            // Accessors
            std::string const &getName() const;
            GLuint getHandle() const;
            
            // Public functions
            void draw(const GLuint aShaderProgramHandle) const;
            void updateVertexData(const std::vector<GLfloat> &aNewVertexData, const VertexFormat &aNewVertexFormat, const VertexData::Type &aNewType = Type::Dynamic);
            
            // Mutating operators
            VertexData &operator=(const VertexData &) = delete;
            VertexData &operator=(VertexData &&) = delete;
      
            // Constructors, destructors
            VertexData(const std::string &aName, const VertexData::Type &aType, const VertexFormat &aVertexFormat,
                 const std::vector<GLfloat> &aVertexData, const std::vector<GLushort> &aIndexData = std::vector<GLushort>(), const PrimitiveMode &aPrimitiveMode = PrimitiveMode::Triangles);
            VertexData() = delete;
            VertexData(const VertexData &) = delete;
            VertexData(VertexData &&);
            ~VertexData();
        };

        std::ostream &operator<< (std::ostream &, const GFX::VertexData &);
    }
}

#endif
