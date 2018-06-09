// © 2018 Joseph Cameron - All Rights Reserved

#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <cmath>

#include <emscripten.h>

#include <gdk.h>
#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/glh.h>
#include <gdk/graphics_gl.h>
#include <gdk/intvector2.h>
#include <gdk/logger.h>
#include <gdk/model.h>
#include <gdk/quaternion.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>
#include <gdk/time.h>
#include <gdk/vector3.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>

namespace
{
    std::shared_ptr<gdk::Camera> pCamera, pCamera2;
    
    std::shared_ptr<gdk::Model> pModel;
}

namespace gdk
{
    void init()
    {
        pCamera = std::make_shared<gdk::Camera>
            ([]()
             {
                 gdk::Camera camera;

                 camera.setViewportSize(0.5, 1.0);
              
                 return camera;
             }());

        pCamera2 = std::make_shared<gdk::Camera>
            ([]()
             {
                 gdk::Camera camera;

                 camera.setViewportSize(0.5, 1.0);
                 camera.setViewportPosition(0.5, 0.0);
                 camera.setClearColor(Color::Blue);
              
                 return camera;
             }());

        pModel = std::make_shared<gdk::Model>
            ([]()
             {
                 gdk::Model model("MySuperCoolModel",
                                  gdk::default_ptr<gdk::VertexData>(static_cast<std::shared_ptr<gdk::VertexData>>(gdk::VertexData::Cube)),
                                  gdk::default_ptr<gdk::ShaderProgram>(static_cast<std::shared_ptr<gdk::ShaderProgram>>(gdk::ShaderProgram::AlphaCutOff)));

                 model.setTexture("_Texture", gdk::default_ptr<gdk::Texture>(static_cast<std::shared_ptr<gdk::Texture>>(gdk::Texture::CheckeredTextureOfDeath)));

                 model.setModelMatrix((gdk::Vector3){0., 0., 0.}, (gdk::Quaternion){});
     
                 return model;
             }());

        emscripten_set_main_loop(gdk::draw, -1, 0); // Negative fps will force requestAnimationFrame usage
        //emscripten_set_main_loop(gdk::update, 60, 0); // must manually call out to requestAnimationFrame and the other timing api to separate gl and logic
    }

    void draw()
    {
        static gdk::Vector3 pos;
        static gdk::Quaternion rot;
        static gdk::Vector3 sca({1.,0.5,1.});

        pos.z = -10.f + (sin(gdk::time::sinceStart())*5.f);
        sca.z = sin(gdk::time::sinceStart()/2.f)*10.f;
        //rot.setFromEuler({45, 35, 0});
        rot.setFromEuler({time::sinceStart()/2.f, time::sinceStart(), 0});
        
        pModel->setModelMatrix(pos, rot, sca);
        
        pCamera->draw(glfw::GetWindowSize());
        pModel->draw(Mat4x4::Identity, pCamera->getProjectionMatrix());

        pCamera2->draw(glfw::GetWindowSize());
        pModel->draw(Mat4x4::Identity, pCamera->getProjectionMatrix());        
    }

    void update()
    {        
    }
    
    void free()
    {
    }
}
