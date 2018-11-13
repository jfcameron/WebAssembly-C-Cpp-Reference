// © 2018 Joseph Cameron - All Rights Reserved
#include <gdk/input_private.h>

namespace gdk::input::PRIVATE
{
    GLFWwindow *pGLFWwindow = nullptr;
}

namespace gdk::input::PROTECTED
{
    void initialize(GLFWwindow *const pWindow)
    {
        gdk::input::PRIVATE::pGLFWwindow = pWindow;
    }
}
