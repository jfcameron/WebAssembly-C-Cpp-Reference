// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>

#include <GLFW/glfw3.h>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#include <gdk/exception.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/intvector2.h>

static constexpr char TAG[] = "GLFW Wrapper";

namespace
{
    gdk::IntVector2 windowSize;

    GLFW::windowsizecallback_type WindowSizeCallback;
    
    static GLFWwindow *const pWindow = []()
    {        
        []()
        {       
            glfwSetErrorCallback(
            [](int, const char *msg)
            {
                throw gdk::Exception(TAG, msg);
            });
        
            if (!glfwInit()) throw gdk::Exception(TAG, "glfwInit failed");
        }();
            
        return []()
        {
            const gdk::IntVector2 aScreenSize(800,600);
            const std::string aName("GDK Window");
        
            windowSize = aScreenSize;
        
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, true);
    
            GLFWwindow *const pGLFWWindow = glfwCreateWindow(aScreenSize.x, aScreenSize.y, aName.c_str(), nullptr, nullptr);
    
            if (!pGLFWWindow) throw gdk::Exception(TAG, "glfwCreateWindow failed. Can the environment provide a GLES2.0/WebGL1.0 context?");

            glfwMakeContextCurrent(pGLFWWindow);
                
            glfwSetWindowSizeCallback(pGLFWWindow, [](GLFWwindow *const aWindow, int aX, int aY)
                                      {
                                          windowSize.x = aX;
                                          windowSize.y = aY;

                                          WindowSizeCallback(aX, aY);
                                      });
    
            return pGLFWWindow;
        }();
    }();
}

namespace GLFW
{
    void InitEarly()
    {
        static_cast<void>(pWindow);
    }
    
    void SwapBuffer()
    {
        glfwSwapBuffers(pWindow);
    }

    double GetTime()
    {
        return glfwGetTime();
    }

    gdk::IntVector2 GetWindowSize()        
    {
        return ::windowSize;
    }

    void SetWindowSizeCallback(GLFW::windowsizecallback_type aWindowSizeCallback)
    {
        ::WindowSizeCallback = aWindowSizeCallback;
    }
}
