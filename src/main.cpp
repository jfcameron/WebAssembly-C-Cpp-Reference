// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/buildinfo.h>
#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/exception.h>
#include <gdk/gamepads_private.h>
#include <gdk/glfw_wrapper.h>
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

#include <cmath>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

static constexpr auto TAG = "gdk";

using namespace gdk;

namespace
{
    std::shared_ptr<gdk::Camera> pCamera, pCamera2;
    std::vector<std::shared_ptr<gdk::Camera>> cameras;
    
    std::shared_ptr<gdk::Model> pModel;

    void draw()
    {        
        static Vector3 pos({0.,0.,-10.f});
        static Vector3 sca({1.,0.5,1.});
        static Quaternion rot;

        sca.z = sin(time::sinceStart() / 2.f) * 1.f;
        rot.setFromEuler({time::sinceStart()/2.f, time::sinceStart(), 0});

        if (keyboard::getKeyDown(keyboard::Key::W)) pos.z -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::S)) pos.z += 0.5;
        if (keyboard::getKeyDown(keyboard::Key::A)) pos.x -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::D)) pos.x += 0.5;
        
        pModel->setModelMatrix(pos, rot, sca);

        for (std::shared_ptr<gdk::Camera> &camera : cameras)
        {
            camera->draw(glfw::GetWindowSize());

            pModel->draw(Mat4x4::Identity, pCamera->getProjectionMatrix());            
        }
    }

    void init()
    {
        pCamera = std::make_shared<Camera>([]()
        {
            Camera camera;

            camera.setViewportSize(0.5, 1.0);
              
            return camera;
        }());

        pCamera2 = std::make_shared<Camera>([]()
        {
            Camera camera;

            camera.setViewportSize(0.5, 1.0);
            camera.setViewportPosition(0.5, 0.0);
            camera.setClearColor(Color::Blue);
              
            return camera;
        }());

        cameras.push_back(pCamera);
        cameras.push_back(pCamera2);

        pModel = std::make_shared<Model>([]()
        {
            Model model("MySuperCoolModel",
                default_ptr<VertexData>(static_cast<std::shared_ptr<VertexData>>(VertexData::Cube)),
                default_ptr<ShaderProgram>(static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::AlphaCutOff)));

            //local load
            {
                //auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", gdk::resources::local::loadBinaryFile("resource/awesome.png")));

                //model.setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
            }
            {
                auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesomer", gdk::resources::local::loadBinaryFile("resource/BG.png")));
                
                model.setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
            }

            //remote load
            {
                /*resources::remote::fetchBinaryFile("https://jfcameron.updog.co/Public/mia.png", //resources::remote::fetchBinaryFile("https://jfcameron.updog.co/Public/Github/Intro-To-WebGL/Example/awesome.png",
                [&](const bool aSucceeded, std::vector<unsigned char> &aData)
                {
                    if (aSucceeded)
                    {
                        auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("remote and not awesome", aData));

                        if (pModel) //This goofy thing comes from my curl usage. Curl is currently synchonous (wrong) wheras ajax on web is not (correct) so pModel is always going ot be null on desktop (until I switch to async)
                        {
                            pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex)); //Works on emscripten, segfaults on desktop
                        }
                        else
                        {
                            gdk::log(TAG, "pModel is null");

                            model.setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex)); // Works on desktop, not emscripten
                        }
                    }
                    else gdk::log(TAG, "the fetch failed");
                });*/
            }

            model.setModelMatrix((Vector3){0., 0., 0.}, (Quaternion){});

            return model;
        }());
    }
}

int main()
{
    std::cout << gdk_BuildInfo_TargetPlatform << std::endl << "Greetings from C++\n";

    init();

    gdk::time::addRenderCallback([](const double &deltaTime)
    {
        draw();
    });

    return gdk::main();
}
