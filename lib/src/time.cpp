// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-16.
#include <gdk/time.h>
#include <gdk/glfw_wrapper.h>

static double currentTime(0.);
static double lastTime(0.);

namespace gdk
{
namespace Time
{
    double getTime(void) noexcept
    {
        return glfw::GetTime();
    }

    double getDeltaTime(void) noexcept
    {
        return currentTime;
    }

    double updateDeltaTime(void) noexcept
    {
        double time = currentTime;
    
        currentTime = glfw::GetTime() - lastTime;
        lastTime = glfw::GetTime();

        return time;
    }
}
}
