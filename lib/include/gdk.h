// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GDK_H
#define GDK_GDK_H

namespace gdk
{
    //! Allocates heap memory and initializes gdk context
    void init();

    //! Renders a frame
    void draw();

    //! Updates all entities.
    void update();

    //! Frees heap memory, cleans up gdk context
    void free();
}

#endif
