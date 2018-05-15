// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-14.

#ifndef GDK_GDK_H
#define GDK_GDK_H

namespace gdk
{
    /// Allocates heap memory and initializes GDK context
    void init();

    /// Renders a frame
    void draw();

    /// Updates all entities.
    void update();

    /// Frees heap memory, cleans up GDK context
    void free();
}

#endif
