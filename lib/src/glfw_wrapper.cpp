// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>

#include <GLFW/glfw3.h>

namespace Math
{
    struct IntVector2
    {
        float x, y;
    };
}

namespace GLFW
{
    void initContext()
    {       
        glfwSetErrorCallback(
            [](int, const char *msg)
            {
                throw std::runtime_error(msg);
            });
                
        if(!glfwInit()) throw std::runtime_error("glfwInit failed");
    }

    GLFWwindow *const initWindow(const Math::IntVector2 &aScreenSize, const std::string &aName)
    {    
        GLFWwindow* aGLFWWindow = nullptr;
    
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);
    
        aGLFWWindow = glfwCreateWindow(aScreenSize.x, aScreenSize.y, aName.c_str(), nullptr, nullptr);
    
        if (!aGLFWWindow) throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
        glfwMakeContextCurrent(aGLFWWindow);
    
        return aGLFWWindow;
    }

    GLFWwindow *const pWindow = []()
    {        
        GLFW::initContext();
        
        return GLFW::initWindow({800,600}, "GDK Window");
    }();

    void SwapBuffer()
    {
        glfwSwapBuffers(pWindow);
    }
}
