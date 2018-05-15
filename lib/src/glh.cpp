// © 2017 Joseph Cameron - All Rights Reserved
// Created on 17-07-02.

#include <GL/glfw.h>

#include <gdk/glh.h>
#include <gdk/color.h>

namespace GLH
{
    void ClearColor(const GDK::Color &aColor)
    {
        glClearColor(aColor.r, aColor.g, aColor.b, aColor.a);
    }
}
