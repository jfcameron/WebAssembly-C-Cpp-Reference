// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-14.
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <gdk.h>
#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/glh.h>
#include <gdk/graphics_gl.h>
#include <gdk/intvector2.h>
#include <gdk/logger.h>
#include <gdk/model.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>

namespace
{    
   void drawhack()
   {
        const auto pCamera = std::make_shared<gdk::Camera>([]()
        {
            return gdk::Camera();
        }());

        const auto pModel = std::make_shared<gdk::Model>([&]()
        {
            gdk::Model model("MySuperCoolModel",
                             gdk::default_ptr<gdk::VertexData>(static_cast<std::shared_ptr<gdk::VertexData>>(gdk::VertexData::Quad)),
                             gdk::default_ptr<gdk::ShaderProgram>(static_cast<std::shared_ptr<gdk::ShaderProgram>>(gdk::ShaderProgram::AlphaCutOff)));

            model.setTexture("_Texture", gdk::default_ptr<gdk::Texture>(static_cast<std::shared_ptr<gdk::Texture>>(gdk::Texture::CheckeredTextureOfDeath)));
     
            return model;
        }());
        
        std::cout << "Draw hack begins\n";

        pCamera->draw((gdk::IntVector2){800, 600});
        pModel->draw(gdk::Mat4x4::Identity, gdk::Mat4x4::Identity);
    }
}

namespace gdk
{
    void init()
    {        
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
