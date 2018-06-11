// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_VERTEXFORMAT_H
#define GDK_GFX_VERTEXFORMAT_H
#include <gdk/opengl.h>
#include <gdk/vertexattribute.h>

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

namespace gdk
{
    /*!
      The purpose of VertexFormat is to inform the context how to interpret Vertex data.
      Vertex data [in the context of OpenGL] is reprented as an array of floating-point values.
      The data and the format of that data is completely arbitrary and user defined. 
      An example of a typical format would be something like this: {Position3, UV2, Normal3, Tangent3}.
      In the above example, the context would know to interpret your vertex data (array of floats) like this:
      floats  0..2 will be uploaded to the position attribute, 3 & 4 to the UV attribute, 5..7 to Normal,
      8..10 Tangent, then repeat (11-13 goes to Position etc...). Attributes, within the context of the graphics pipeline
      represents instanced data. In the context of the Vertex Shader stage, you will be able to access a set of attributes,
      representing a single full vertex.
    */
    class VertexFormat final
    {
        friend std::ostream &operator<< (std::ostream &, const VertexFormat &);
    
        std::vector<VertexAttribute> m_Format = {};
        int m_SumOfAttributeComponents = {0};
            
    public:
        void enableAttributes(const GLuint aShaderProgramHandle) const;
        int getSumOfAttributeComponents() const;
            
        VertexFormat& operator=(const VertexFormat &) = default;
        VertexFormat& operator=(VertexFormat &&) = default;
      
        VertexFormat(const std::vector<VertexAttribute> &aAttributes);
        VertexFormat() = delete;
        VertexFormat(const VertexFormat &) = default;
        VertexFormat(VertexFormat &&) = default;
        ~VertexFormat() = default;
            
        static const VertexFormat Pos3uv2Norm3;
        static const VertexFormat Pos3uv2;
        static const VertexFormat Pos3;
    };

    std::ostream &operator<< (std::ostream &, const VertexFormat &);
}

#endif
