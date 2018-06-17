// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk.h>
#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/exception.h>
#include <gdk/gamepads_private.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/hack.h>
#include <gdk/intvector2.h>
#include <gdk/keyboard.h>
#include <gdk/logger.h>
#include <gdk/model.h>
#include <gdk/mouse.h>
#include <gdk/quaternion.h>
#include <gdk/resources.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>
#include <gdk/time.h>
#include <gdk/vector3.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>

#include <emscripten.h>

#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <vector>

constexpr auto TAG = "gdk";

namespace
{
    std::shared_ptr<gdk::Camera> pCamera, pCamera2;
    
    std::shared_ptr<gdk::Model> pModel;
}

namespace gdk
{
    void init()
    {
        try
        {
        pCamera = std::make_shared<Camera>
            ([]()
             {
                 Camera camera;

                 camera.setViewportSize(0.5, 1.0);
              
                 return camera;
             }());

        pCamera2 = std::make_shared<Camera>
            ([]()
             {
                 Camera camera;

                 camera.setViewportSize(0.5, 1.0);
                 camera.setViewportPosition(0.5, 0.0);
                 camera.setClearColor(Color::Blue);
              
                 return camera;
             }());

        pModel = std::make_shared<Model>
            ([]()
             {
                 Model model("MySuperCoolModel",
                             default_ptr<VertexData>(static_cast<std::shared_ptr<VertexData>>(VertexData::Cube)),
                             default_ptr<ShaderProgram>(static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::AlphaCutOff)));

                 auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", gdk::resources::local::loadBinaryFile("resource/awesome.png")));

                 model.setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));

                 model.setModelMatrix((Vector3){0., 0., 0.}, (Quaternion){});
     
                 return model;
             }());

        emscripten_set_main_loop(draw, -1, 0); // Negative fps will force requestAnimationFrame usage
        //emscripten_set_main_loop(update, 60, 0); // must manually call out to requestAnimationFrame and the other timing api to separate gl and logic
        
        resources::remote::fetchBinaryFile("https://jfcameron.updog.co/Public/mia.png",//"https://jfcameron.github.io/Textures/brick.png",
                                           [](const bool aSucceeded, std::vector<unsigned char> &aData)
                                           {
                                               if (aSucceeded)
                                               {
                                                   auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("remote and not awesome", aData));

                                                   pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
                                               }
                                               else gdk::log(TAG, "the fetch failed");
                                           });
        
        gamepads::initialize();

        hack_init();

        }
        catch (gdk::Exception exception)
        {
            std::cout << exception << std::endl;
        }
    }

    void draw()
    {        
        static Vector3 pos({0.,0.,-10.f});
        static Quaternion rot;
        static Vector3 sca({1.,0.5,1.});

        sca.z = sin(time::sinceStart()/2.f)*1.f;
        rot.setFromEuler({time::sinceStart()/2.f, time::sinceStart(), 0});

        if (keyboard::getKeyDown(keyboard::Key::W)) pos.z -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::S)) pos.z += 0.5;
        if (keyboard::getKeyDown(keyboard::Key::A)) pos.x -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::D)) pos.x += 0.5;
        
        pModel->setModelMatrix(pos, rot, sca);
        
        pCamera->draw(glfw::GetWindowSize());
        pModel->draw(Mat4x4::Identity, pCamera->getProjectionMatrix());

        pCamera2->draw(glfw::GetWindowSize());
        pModel->draw(Mat4x4::Identity, pCamera->getProjectionMatrix());

        gamepads::update();

        glfw::PollEvents();

        hack_update();
    }

    void update()
    {
    }
    
    void free()
    {
    }
}
