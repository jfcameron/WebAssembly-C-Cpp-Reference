// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#include <gdk/timer.h>
#include <gdk/glfw_wrapper.h>

namespace gdk
{
    double Timer::get()
    {
        return currentTime;
    }

    void Timer::reset()
    {
        currentTime = glfw::GetTime() - lastTime;
        lastTime =    glfw::GetTime();
    }

    double Timer::getAndReset()
    {
        double time = currentTime;
    
        currentTime = glfw::GetTime() - lastTime;
        lastTime =    glfw::GetTime();

        return time;
    }    

    Timer::Timer()
    {}
}
