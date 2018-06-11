// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GAMEPADS_H
#define GDK_GAMEPADS_H

#include <memory>
#include <string>

namespace gdk
{
    class Gamepad;
    
    namespace Gamepads
    {
        //! Get a gamepad by index. Index value is based on order in
        //  which the device was connected to the system.
        std::weak_ptr<Gamepad> get(const int aIndex);

        //! Get a gamepad by device name
        std::weak_ptr<Gamepad> get(const std::string &aName);
    }
}

#endif
