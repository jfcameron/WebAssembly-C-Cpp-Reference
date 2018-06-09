// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.
#include <functional>

#include <gdk/intvector2.h>
#include <gdk/vector2.h>

namespace glfw
{
    using windowsizecallback_type = std::function<void(int aX, int aY)>;
    
    //! Force GDK to init. If you need to make GLFW calls at static time, you should place this call
    //  at the beginning of all such blocks to guarantee GLFW has initialized before you need to use it.
    void InitEarly();

    //! Swap the front buffer (currently presented on display) with the backbuffer (currently being written to)
    void SwapBuffer();

    //! Get time since app start
    //  \WARN What is the unit?
    double GetTime();

    //! Get size in pixels of the window
    gdk::IntVector2 GetWindowSize();

    //! Attach a callback to the window which will be called whenver the window is resized and provides that size info.
    //  \WARN You can only attach one function at a time.
    //  \WARN Should this support an arbitray number of callbacks?
    void SetWindowSizeCallback(windowsizecallback_type aWindowSizeCallback);
    
    //glfwGetMouseButton(ptr.get(), glfwMouseButtonFromButton(aButton))
    bool GetMouseButton(const int aButton);

    //! Get position of the mouse cursor
    gdk::Vector2 GetCursorPos();

    //! Get a key value
    bool GetKey(const int aKeyCode);
}
