// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/gamepads.h>
#include <gdk/glfw_wrapper.h>

#include <map>
#include <vector>

namespace gdk
{
    class Gamepad final
    {
        std::string m_Name;        
    };   
}

namespace
{
    std::map<std::string, gdk::Gamepad> gamepadMap;
    
    std::vector<gdk::Gamepad> gamepadList;
}

namespace gdk
{
    
}
