// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>

#include <GLFW/glfw3.h>

#include <gdk/exception.h>

static constexpr char TAG[] = "GLFW Wrapper";

namespace Math //Should be refactored
{
    struct IntVector2
    {
        float x, y;
    };
}

namespace
{
    void initContext()
    {       
        glfwSetErrorCallback(
            [](int, const char *msg)
            {
                throw gdk::Exception(TAG, msg);
            });
                
        if(!glfwInit()) throw gdk::Exception(TAG, "glfwInit failed");
    }

    GLFWwindow *const initWindow(const Math::IntVector2 &aScreenSize, const std::string &aName)
    {    
        GLFWwindow* aGLFWWindow = nullptr;
    
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);
    
        aGLFWWindow = glfwCreateWindow(aScreenSize.x, aScreenSize.y, aName.c_str(), nullptr, nullptr);
    
        if (!aGLFWWindow) throw gdk::Exception(TAG, "glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
        glfwMakeContextCurrent(aGLFWWindow);
    
        return aGLFWWindow;
    }

    GLFWwindow *const pWindow = []()
    {        
        ::initContext();
        
        return ::initWindow({800,600}, "GDK Window");
    }();
}

namespace GLFW
{
    void SwapBuffer()
    {
        glfwSwapBuffers(::pWindow);
    }
}
