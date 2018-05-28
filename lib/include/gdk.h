// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-14.

#ifndef gdk_gdk_H
#define gdk_gdk_H

//hack
extern "C" float js_to_cpp_test(float a);

namespace gdk
{
    /// Allocates heap memory and initializes gdk context
    void init();

    /// Renders a frame
    void draw();

    /// Updates all entities.
    void update();

    /// Frees heap memory, cleans up gdk context
    void free();
}

#endif
