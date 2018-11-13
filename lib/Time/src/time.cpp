// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#include <gdk/time.h>
#include <gdk/time_private.h>

#include <GLFW/glfw3.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#endif

#include <vector>

namespace gdk::time
{
    double sinceStart(void) noexcept
    {
        return glfwGetTime();
    }
}
