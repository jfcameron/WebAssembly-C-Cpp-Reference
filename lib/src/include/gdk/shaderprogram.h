// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_SHADERPROGRAM_H
#define GDK_GFX_SHADERPROGRAM_H

#include <gdk/opengl.h>
#include <gdk/lazy_ptr.h>

#include <iosfwd>
#include <string>

namespace gdk
{
    //! ShaderProgram specifies drawing behaviours at the programmable stages in the OpenGL
    /// programmable pipeline.
    class ShaderProgram final
    {
        friend std::ostream &operator<< (std::ostream &, const ShaderProgram &);
        
        std::string m_Name = {};      //!< Human friendly identifier        
        GLuint m_ProgramHandle = {0}; //!< handle to the program in the context.
        
    public:
        //! Installs the program to the pipeline. This program's programmable stages
        /// will be used for draw calls until a different program is installed.
        GLuint useProgram() const;
        
        std::string getName() const;
        GLuint getHandle() const;
                
        ShaderProgram &operator=(const ShaderProgram &) = delete;
        ShaderProgram &operator=(ShaderProgram &&) = delete;
                
        ShaderProgram() = delete;
        ShaderProgram(const std::string &aName, const std::string &aVertexSource, const std::string &aFragmentSource);
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram(ShaderProgram &&);
        ~ShaderProgram();
        
        static const gdk::lazy_ptr<gdk::ShaderProgram> PinkShaderOfDeath; //!< shader for indicating some kind of failure
        static const gdk::lazy_ptr<gdk::ShaderProgram> AlphaCutOff;       //!< shader for drawing sprites
    };

    std::ostream &operator<< (std::ostream &, const ShaderProgram &);
}

#endif
