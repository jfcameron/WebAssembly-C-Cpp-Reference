// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#ifndef GDK_GFX_CHECKEREDTEXTUREOFDEATH_H
#define GDK_GFX_CHECKEREDTEXTUREOFDEATH_H

//gdk inc
#include <gdk/default_ptr.h>
#include <gdk/vertexdata.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>

namespace gdk
{
    namespace DefaultResources
    {
        /// Creates the checkeredTextureOfDeath.
        /// Very low resolution tiled texture, alternating white a blue.
        /// Useful as a fallback when the intended texture has failed to load.
        default_ptr<Texture> getCheckeredTextureOfDeath();
            
        /// Creates the PinkShaderOfDeath.
        /// Muls verts through standard MVP but colors all frags an obnoxious fluorescent pink.
        /// Useful as a fallback shader.
        default_ptr<ShaderProgram> getPinkShaderOfDeath();
            
        /// Basic alphacutoff shader
        default_ptr<ShaderProgram> getAlphaCutOff();
            
        /// Make a unit length quad
        default_ptr<VertexData> getQuad();
            
        /// Make a unit length cube
        default_ptr<VertexData> getCube();
            
        /// Make a cylinder
        default_ptr<VertexData> getCylinder();
    }
}

#endif
