// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GAMEPADS_PRIVATE_H
#define GDK_GAMEPADS_PRIVATE_H

/// \brief declares private functions for the gamepad input handler.
///
/// \detailed These functions are required for gamepad handler to function correctly,
/// Therefore if your project is to make use of gamepads, you will have to call these
/// in an appropriate place in your project.
/// However, these functions should not be exposed to the user of your project, as they
/// offer no value to the user and only reduce legibility/offer a way to break things.
namespace gdk::input::hidden::gamepads
{
    //! Initializes gamepads handler. Must be called once, before gamepads is used.
    void initialize();
    
    //! Update gamepad states, should be called at the same rate at which user input is handled
    void update();
}

#endif
