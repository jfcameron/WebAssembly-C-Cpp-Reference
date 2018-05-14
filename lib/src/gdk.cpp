// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-14.
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>

#include <GL/glfw.h>

#include <gdk/color.h>
#include <gdk/glh.h>

namespace
{
    void initOpenGL()
    {        
        if (!glfwInit()) std::runtime_error("Could not initialize GLFW!");

        const int width = 800, height = 600;
        if (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE)
        {
            std::runtime_error("glfwOpenWindow() failed\n");
        }
    }

    void draw()
    {
        GLH::ClearColor(GDK::Color::CornflowerBlue);
            
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //this->drawCallback(aDelta);

        glfwSwapBuffers();
    }
}

namespace gdk
{
    void init()
    {
        initOpenGL();
        draw();
    }
    
    void free()
    {
    }
}
