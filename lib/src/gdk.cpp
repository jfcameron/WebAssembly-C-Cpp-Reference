// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-14.
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>

#include <gdk/graphics_gl.h>

//hacks
#include <memory>

#include <vector>
#include <gdk/texture.h>
#include <gdk/shaderprogram.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>
namespace
{
    void hack()
    {
        std::shared_ptr<gdk::GFX::Texture> pTexture = std::make_shared<gdk::GFX::Texture>([]()
        {
            std::vector<const GLubyte> textureData({
                    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
                        0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08,
                        0x08, 0x02, 0x00, 0x00, 0x00, 0x4b, 0x6d, 0x29, 0xdc, 0x00, 0x00, 0x00,
                        0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
                        0x00, 0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc,
                        0x61, 0x05, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00,
                        0x0e, 0xc3, 0x00, 0x00, 0x0e, 0xc3, 0x01, 0xc7, 0x6f, 0xa8, 0x64, 0x00,
                        0x00, 0x00, 0x1b, 0x49, 0x44, 0x41, 0x54, 0x18, 0x57, 0x63, 0xf8, 0xff,
                        0xff, 0xff, 0xcc, 0x9b, 0xaf, 0x30, 0x49, 0x06, 0xac, 0xa2, 0x40, 0x72,
                        0x30, 0xea, 0xf8, 0xff, 0x1f, 0x00, 0xd3, 0x06, 0xab, 0x21, 0x92, 0xd9,
                        0xa4, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
                        0x60, 0x82});

            //gdk::GFX::Texture myTexture("CheckerboardOfDeath", textureData);
            return gdk::GFX::Texture("CheckerboardOfDeath", textureData);
        }());

        std::shared_ptr<gdk::GFX::ShaderProgram> pShader = std::make_shared<gdk::GFX::ShaderProgram>([]()
        {
            const std::string vertexShaderSource = R"V0G0N(
            //Uniforms
            uniform mat4 _MVP;

            //VertIn
            attribute highp vec3 a_Position;

            void main ()
            {
                gl_Position = _MVP * vec4(a_Position,1.0); //Make use of actual verts
            }
            )V0G0N";

            const std::string fragmentShaderSource = R"V0G0N(
            precision mediump float;
            
            //const highp vec4 DeathlyPink(1,0.2,0.8,1);

            void main()
            {
                gl_FragColor = vec4(1,0.2,0.8,1);//DeathlyPink;
            }
            )V0G0N";
            
            return gdk::GFX::ShaderProgram("MySuperCoolShader", vertexShaderSource, fragmentShaderSource);
        }());

        std::shared_ptr<gdk::GFX::VertexData> pVertexData = std::make_shared<gdk::GFX::VertexData>([]()
        {
            float size  = 1.;
            float hsize = size/2.;
            std::vector<GLfloat> data({
                    //        x,           y,    z,    u,    v,
                    size -hsize, size -hsize, 0.0f, 1.0f, 0.0f, // 1--0
                        0.0f -hsize, size -hsize, 0.0f, 0.0f, 0.0f, // | /
                        0.0f -hsize, 0.0f -hsize, 0.0f, 0.0f, 1.0f, // 2
                        size -hsize, size -hsize, 0.0f, 1.0f, 0.0f, //    0
                        0.0f -hsize, 0.0f -hsize, 0.0f, 0.0f, 1.0f, //  / |
                        size -hsize, 0.0f -hsize, 0.0f, 1.0f, 1.0f, // 1--2
                        });

            return gdk::GFX::VertexData("Quad",gdk::GFX::VertexData::Type::Static,gdk::GFX::VertexFormat::Pos3uv2,data);
        }());

        //Draw hack
        pShader->useProgram();
        pVertexData->draw(pShader->getHandle());
    }
}

namespace gdk
{
    void init()
    {        
        gfx::init();

        hack();
    }

    void draw()
    {
        gfx::draw();
    }
    
    void update()
    {
    }
    
    void free()
    {
    }
}
