// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 17-07-02.
#ifndef gdk_GFX_SHADERPROGRAM_H
#define gdk_GFX_SHADERPROGRAM_H

#include <iosfwd>
#include <string>

#include <gdk/opengl.h>
#include <gdk/lazy_ptr.h>

namespace gdk
{
    /*!
      ShaderProgram specifies drawing behaviours at the programmable stages in the OpenGL
      programmable pipeline.
    */
    class ShaderProgram final
    {
        friend std::ostream &operator<< (std::ostream &, const ShaderProgram &);
            
        // Data members
        std::string m_Name = {};
        GLuint m_ProgramHandle = {0};
            
    public: // Public interface
            /// Installs a program object as part of current rendering state
        GLuint useProgram() const;
            
        // Accessors
        std::string getName() const;
        GLuint getHandle() const;
            
        // Mutating operators
        ShaderProgram &operator=(const ShaderProgram &) = delete;
        ShaderProgram &operator=(ShaderProgram &&) = delete;
      
        // Constructors, destructors
        ShaderProgram() = delete;
        ShaderProgram(const std::string &aName, const std::string &aVertexSource, const std::string &aFragmentSource);
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram(ShaderProgram &&);
        ~ShaderProgram();

        static const gdk::lazy_ptr<gdk::ShaderProgram> PinkShaderOfDeath;        
        static const gdk::lazy_ptr<gdk::ShaderProgram> AlphaCutOff;
    };

    std::ostream &operator<< (std::ostream &, const ShaderProgram &);
}

#endif
