// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>

#include <GLFW/glfw3.h>

#include <gdk/exception.h>
#include <gdk/intvector2.h>

static constexpr char TAG[] = "GLFW Wrapper";

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

    GLFWwindow *const initWindow(const gdk::IntVector2 &aScreenSize, const std::string &aName)
    {        
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);
    
        GLFWwindow *const pGLFWWindow = glfwCreateWindow(aScreenSize.x, aScreenSize.y, aName.c_str(), nullptr, nullptr);
    
        if (!pGLFWWindow) throw gdk::Exception(TAG, "glfwCreateWindow failed. Can the environment provide a GLES2.0/WebGL1.0 context?");
    
        glfwMakeContextCurrent(pGLFWWindow);
    
        return pGLFWWindow;
    }

    GLFWwindow *const pWindow = []()
    {        
        ::initContext();
        
        return ::initWindow({800,600}, "gdk Window"); //Refactor this
    }();
}

namespace GLFW
{
    void SwapBuffer()
    {
        glfwSwapBuffers(::pWindow);
    }

    double GetTime()
    {
        return glfwGetTime();
    }
}
