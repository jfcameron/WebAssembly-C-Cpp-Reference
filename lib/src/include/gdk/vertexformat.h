// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#ifndef GDK_GFX_VERTEXFORMAT_H
#define GDK_GFX_VERTEXFORMAT_H

#include <GLES2/gl2.h>

#include <gdk/vertexattribute.h>

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

namespace GDK
{
    namespace GFX
    {
        /*!
         Vertex data is arbitrary and user defined. Vertexformat is used to inform the
         device how to interpret your vertex data. An example of a typical format would be
         something like this: {Position,UV,Normal,Tangent}. The important thing is that this matches
         the actual vertex data in the vertex buffer.
         */
        class VertexFormat final
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::VertexFormat &);
    
            // Data members
            std::vector<VertexAttribute> m_Format = {};
            int m_SumOfAttributeComponents = {0};
            
        public:
            // Public methods
            void enableAttributes(const GLuint aShaderProgramHandle) const;
            int getSumOfAttributeComponents() const;
            
            // Mutating operators
            VertexFormat& operator=(const VertexFormat &) = default;
            VertexFormat& operator=(VertexFormat &&) = default;
      
            // Constructors, destructors
            VertexFormat(const std::vector<VertexAttribute> &aAttributes);
            VertexFormat() = delete;
            VertexFormat(const VertexFormat &) = default;
            VertexFormat(VertexFormat &&) = default;
            ~VertexFormat() = default;
            
            // Special values
            static const VertexFormat Pos3uv2Norm3;
            static const VertexFormat Pos3uv2;
            static const VertexFormat Pos3;
        };

        std::ostream &operator<< (std::ostream &, const GFX::VertexFormat &);
    }
}

#endif
