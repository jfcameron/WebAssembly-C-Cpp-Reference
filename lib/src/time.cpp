// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-16.
#include <gdk/time.h>
#include <gdk/glfw_wrapper.h>

using namespace GDK;

static double currentTime(0.);
static double lastTime(0.);

namespace Time
{
    double getTime(void) noexcept
    {
        return GLFW::GetTime();
    }

    double getDeltaTime(void) noexcept
    {
        return currentTime;
    }

    double updateDeltaTime(void) noexcept
    {
        double time = currentTime;
    
        currentTime = GLFW::GetTime() - lastTime;
        lastTime = GLFW::GetTime();

        return time;
    }
}
