//#ifdefined glfw
#include <gdk/glfw_wrapper.h>

namespace gdk
{
    void InitEarlyOpenGL()
    {
        GLFW::InitEarly(); //implementation for glfw platforms (wasm, macos, linux, win)
    }
}
//#endif
