// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/time.h>
#include <gdk/glfw_wrapper.h>

static double currentTime(0.);
static double lastTime(0.);

namespace gdk::time
{
    double sinceStart(void) noexcept
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
