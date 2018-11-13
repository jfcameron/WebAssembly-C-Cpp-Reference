// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#include <gdk/timer.h>

#include <GLFW/glfw3.h>

namespace gdk
{
    double Timer::get()
    {
        return currentTime;
    }

    void Timer::reset()
    {
        currentTime = glfwGetTime() - lastTime;
        lastTime =    glfwGetTime();
    }

    double Timer::getAndReset()
    {
        double time = currentTime;
    
        currentTime = glfwGetTime() - lastTime;
        lastTime =    glfwGetTime();

        return time;
    }    

    Timer::Timer()
    {}
}
