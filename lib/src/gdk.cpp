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

//draw hack stuff
#include <gdk/texture.h>
#include <gdk/shaderprogram.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>
#include <gdk/camera.h>
#include <gdk/intvector2.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/color.h>
#include <gdk/glh.h>
#include <gdk/model.h>
#include <gdk/defaultresources.h>

//jscpp
#include <gdk.h>
#include <gdk/logger.h>
#include <emscripten/emscripten.h>

extern "C" float js_to_cpp_test(float a)
{
    //gdk::Debug::log("BLAR", "BLORT");
    return a;
}

namespace
{
    EM_JS(void, call_alert, (),
          {
              console.log("C++ says \"Hello\" to the console.log api.");

              var canvas = document.getElementById("canvas");

              console.log("canvas info: " + "size: {" + canvas.width + ", " + canvas.height + "}");

              var c_javascript_add = Module.cwrap(
                  'js_to_cpp_test', // name of C function
                  'number', // return type
                  ['number']); // argument types

//console.log(c_javascript_add(10));
          });

    void jscpphack()
    {
        call_alert();
    }
    
    void drawhack()
    {
        //clear buffer hack. Why does this need to be called first? GLFW is probably initializing weird. Look at wrapper
        glh::ClearColor(gdk::Color::CornflowerBlue);            
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLFW::SwapBuffer();
        //END
        
        std::shared_ptr<gdk::Texture> pTexture = std::make_shared<gdk::Texture>([]()
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

            //gdk::Texture myTexture("CheckerboardOfDeath", textureData);
            return gdk::Texture("CheckerboardOfDeath", textureData);
        }());

        std::shared_ptr<gdk::ShaderProgram> pShader = std::make_shared<gdk::ShaderProgram>([]()
        {
            /*const std::string vertexShaderSource = R"V0G0N(
            //Uniforms
            uniform mat4 _MVP;

            //VertIn
            attribute highp vec3 a_Position;

            void main ()
            {
                gl_Position = _MVP * vec4(a_Position,1.0);
            }
            )V0G0N";

            const std::string fragmentShaderSource = R"V0G0N(
            precision mediump float;
            
            const vec4 DEATHLY_PINK = vec4(1,0.2,0.8,1);

            void main()
            {
                gl_FragColor = DEATHLY_PINK;
            }
            )V0G0N";*/

            const std::string vertexShaderSource = R"V0G0N(
            #version 100

            //Uniforms
            uniform mat4  _MVP;
            uniform mat4  _Model;
            uniform mat4  _View;
            uniform mat4  _Projection;
            uniform float _Time;
          
            //VertIn
            attribute highp vec3 a_Position;
            attribute highp vec2 a_UV;

            //FragIn
            varying lowp vec2 v_UV;

            void main ()
            {
                gl_Position = _MVP * vec4(a_Position,1.0);
                
                v_UV = a_UV;
            }
            )V0G0N";

            const std::string fragmentShaderSource = R"V0G0N(
            #version 100
            precision mediump float;
            
            //Uniforms
            uniform sampler2D _Texture;
            
            //FragIn
            varying lowp vec2 v_UV;

            void main()
            {
                vec4 frag = texture2D(_Texture, v_UV);
                
                if (frag[3] < 1.0) discard;
                
                gl_FragColor = frag;
                
                
                //gl_FragColor = vec4(1,0.2,0.8,1);//DeathlyPink;
            }
            )V0G0N";
            
            return gdk::ShaderProgram("MySuperCoolShader", vertexShaderSource, fragmentShaderSource);
        }());

        std::shared_ptr<gdk::VertexData> pVertexData = std::make_shared<gdk::VertexData>([]()
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

            return gdk::VertexData("Quad",gdk::VertexData::Type::Static,gdk::VertexFormat::Pos3uv2,data);
        }());

        std::shared_ptr<gdk::Camera> pCamera = std::make_shared<gdk::Camera>([]()
        {
            return gdk::Camera();
        }());

        std::shared_ptr<gdk::Model> pModel = std::make_shared<gdk::Model>([&]()
        {
            //Model(const std::string &aName, const default_ptr<VertexData> &, const default_ptr<ShaderProgram> &);
            return gdk::Model("MySuperCoolModel", gdk::DefaultResources::getQuad(), gdk::default_ptr<gdk::ShaderProgram>(pShader));
        }());


        //void setTexture(const std::string &aUniformName, const default_ptr<Texture>     &aTexture);
        pModel->setTexture("_Texture", gdk::default_ptr<gdk::Texture>(pTexture));
        
        //Draw hack. Note: Missing uniform data upload step. Need to import uniform handlers from GDK
        std::cout << "Draw hack begins\n";       
        pCamera->draw((gdk::IntVector2){800, 600});
        
        pModel->draw(gdk::Mat4x4::Identity, gdk::Mat4x4::Identity);        
        //END
    }
}

namespace gdk
{
    void init()
    {
        jscpphack();
        drawhack();
    }

    void draw()
    {
    }
    
    void update()
    {
    }
    
    void free()
    {
    }
}
