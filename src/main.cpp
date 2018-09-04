// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/buildinfo.h>

#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/exception.h>
#include <gdk/input_private.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/intvector2.h>
#include <gdk/keyboard.h>
#include <gdk/logger.h>
#include <gdk/model.h>
#include <gdk/mouse.h>
#include <gdk/quaternion.h>
#include <gdk/resources.h>
#include <gdk/resources_private.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>
#include <gdk/time.h>
#include <gdk/time_private.h>
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
#include <thread>

static constexpr auto TAG = "main";

using namespace gdk;

namespace
{
    std::shared_ptr<gdk::Camera> pCamera, pCamera2;
    std::vector<std::shared_ptr<gdk::Camera>> cameras;
    
    std::shared_ptr<gdk::Model> pModel;

    void workerupdate() //Thread safe work goes here
    {
        resources::hidden::updateFetchQueue();
    }
    
    void update(const double &aDeltaTime) // thread unsafe work goes here
    {
        resources::hidden::updateResponseQueue();
    }
    
    void draw(const double &aDelta) //Main thread draw (gl is not threadsafe, stuck here)
    {        
        static Vector3 pos({0., 0., -10.});
        static Vector3 sca({1., 0.5, 1.});
        static Quaternion rot;

        sca.z = sin(time::sinceStart() / 2.f) * 1.f;
        rot.setFromEuler({time::sinceStart() / 2.f, time::sinceStart(), 0});

        if (keyboard::getKeyDown(keyboard::Key::W)) pos.z -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::S)) pos.z += 0.5;
        if (keyboard::getKeyDown(keyboard::Key::A)) pos.x -= 0.5;
        if (keyboard::getKeyDown(keyboard::Key::D)) pos.x += 0.5;
        
        pModel->setModelMatrix(pos, rot, sca);

        for (std::shared_ptr<gdk::Camera> &camera : cameras)
        {
            camera->draw(glfw::GetWindowSize());

            pModel->draw(aDelta, Mat4x4::Identity, pCamera->getProjectionMatrix());
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
                
            gdk::resources::local::fetchFile("resource/awesome.png",
            [](const bool aSucceeded, std::vector<unsigned char> aData)
            {
                if (aSucceeded)
                {
                    auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", aData));
                    
                    pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
                }
                else gdk::log(TAG, "the fetch failed");
            });
            
            gdk::resources::local::fetchFile("resource/BG.png",
            [](const bool aSucceeded, std::vector<unsigned char> aData)
            {
                if (aSucceeded)
                {
                    auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", aData));
                
                    pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
                }
                else gdk::log(TAG, "the fetch failed");
            });
        
            resources::remote::fetchFile("https://jfcameron.updog.co/Public/mia.png",
            [](const bool aSucceeded, std::vector<unsigned char> aData)
            {
                if (aSucceeded)
                {
                    auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("remote and not awesome", aData));

                    pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
                }
                else gdk::log(TAG, "the fetch failed");
            });

            model.setModelMatrix((Vector3){0., 0., 0.}, (Quaternion){});

            return model;
        }());
    }
}

int main()
{
    std::cout << gdk_BuildInfo_TargetPlatform << std::endl << "Greetings from C++\n";

#if !defined JFC_TARGET_PLATFORM_Emscripten // Webassm does not support threading
    
    // Worker pool
    std::vector<std::thread> workers;
    
    if (std::thread::hardware_concurrency() > 1)
    {
        std::atomic<bool> isAlive = true;
        
        for (size_t i = 0; i < std::thread::hardware_concurrency() - 1; ++i)
        {
            workers.push_back(std::thread([&]()
            {
                while(isAlive) workerupdate();
                
                //for (auto &worker : workers) worker.join();
            }));
        }
    }
#endif
    
    init();

    gdk::time::addRenderCallback([](const double &aDeltaTime)
    {
        update(aDeltaTime);
        
#if defined JFC_TARGET_PLATFORM_Emscripten
        workerupdate();
#endif
        
        draw(aDeltaTime);
    });

    return gdk::time::hidden::mainLoop();
}
