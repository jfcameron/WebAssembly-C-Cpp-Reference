//#ifdefined glfw
#include <gdk/glfw_wrapper.h>

namespace gdk
{
    void InitEarlyOpenGL()
    {
        //glfw::InitEarly(); //implementation for glfw platforms (wasm, macos, linux, win)
    }
}
//#endif
