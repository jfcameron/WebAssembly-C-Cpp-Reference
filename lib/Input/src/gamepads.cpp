// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/exception.h>
#include <gdk/gamepads.h>
#include <gdk/input_protected.h>
#include <gdk/glfw_wrapper.h>

#include <GLFW/glfw3.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#endif

#include <iostream>
#include <map>
#include <vector>

#include <assert.h> // Remove cstdlib dependencies
#include <stdio.h>
#include <string.h>

static constexpr char TAG[] = "Gamepad";

namespace gdk
{
    /// \brief a gamepad attached to the system.
    ///
    /// \detailed
    ///
    /// \note this class cannot be directly accessed by the user; it is an implementation detail of the gamepads.h api
    class Gamepad final
    {
        friend void gdk::input::hidden::gamepads::initialize();
        
        Gamepad(const int aJoystickIndex);
        
    public:
        std::string m_Name;
        
        std::vector<const unsigned char *> m_Buttons;
        std::vector<const float *> m_Axes;
        
        void update();
    };
    
    void Gamepad::update()
    {
        //check if my pointers in glfw context are null and my behaviour is now evil and undefined
    }

    Gamepad::Gamepad(const int aJoystickIndex)
    : m_Name([&]()
    {
        const char *name = glfwGetJoystickName(aJoystickIndex);

        if (!name) throw gdk::Exception(TAG, "Gamepad handler failed to create a gdk::Gamepad using index: ", aJoystickIndex, " is there a gamepad connected at that index?");
                        
        return name;
    }())
    , m_Buttons([&]()
    {
        int button_count;
        const unsigned char *buttons = glfwGetJoystickButtons(aJoystickIndex, &button_count);
                        
        if (!buttons) throw gdk::Exception(TAG, "Gamepad handler failed to create a gdk::Gamepad using index: ", aJoystickIndex, " is there a gamepad connected at that index?");
                        
                        return (std::vector<const unsigned char *>) {buttons, buttons + button_count};
    }())
    , m_Axes([&]()
    {
        int axes_count;
        const float *axes = glfwGetJoystickAxes(aJoystickIndex, &axes_count);
                        
        if (!axes) throw gdk::Exception(TAG, "Gamepad handler failed to create a gdk::Gamepad using index: ", aJoystickIndex, " is there a gamepad connected at that index?");

        return (std::vector<const float *>) {axes, axes + axes_count};
    }())
    {}
}

namespace
{
//    std::map<std::string, gdk::Gamepad> gamepadMap; //for o1 retrieval?
    
    std::vector<gdk::Gamepad> gamepadList;
}

namespace gdk::input::hidden::gamepads
{
    void initialize()
    {
        glfwSetJoystickCallback(
            [](int joy, int event)
            {
                if (event == GLFW_CONNECTED)
                {
                    std::cout << "Joystick connected: " << joy << glfwGetJoystickName(joy) << std::endl;
                    
                    gamepadList.push_back(gdk::Gamepad(joy));
                }
                else if (event == GLFW_DISCONNECTED)
                {
                    std::cout << "Joystick disconnected: " << joy << std::endl;

                    gamepadList.erase(gamepadList.begin() + joy);
                }
            });
    }
    
    void update()
    {
        for (const auto &gamepad : gamepadList)
        {
            std::cout << "Name: " << gamepad.m_Name << 
            [&]()
            {
                std::string output;

                int i = 0;
                for (const auto &button : gamepad.m_Buttons) output += static_cast<int>(*button);

                return output;
            }()

                      << std::endl;
        }
    }
            
        /*int joystick_count = 0;
    
        for (int j = GLFW_JOYSTICK_1; j < GLFW_JOYSTICK_16; ++j)
        {
            int joy = GLFW_JOYSTICK_1 + j;
        
            if (!glfwJoystickPresent(joy)) continue;
            
            joystick_count++;

            static struct
            {
                int axes_count;
                float axes[16];
                
                int button_count;
                unsigned char buttons[16];
            }
            last_gamepad_state[16] = {0};

            const char *name = glfwGetJoystickName(joy);

            int axes_count = 0;
            const float *axes = glfwGetJoystickAxes(joy, &axes_count);

            int button_count = 0;
            const unsigned char *buttons = glfwGetJoystickButtons(joy, &button_count);

            last_gamepad_state[joy].axes_count = axes_count;
            for (int i = 0; i < axes_count; ++i)
            {
                if (last_gamepad_state[joy].axes[i] != axes[i])
                {
                    printf("(%d %s) axis %d = %f\n", joy, name, i, axes[i]);
                }

                last_gamepad_state[joy].axes[i] = axes[i];
            }

            last_gamepad_state[joy].button_count =  button_count;
            for (int i = 0; i < button_count; ++i)
            {
                if (last_gamepad_state[joy].buttons[i] != buttons[i])
                {
                    printf("(%d %s) button %d = %d\n", joy, name, i, buttons[i]);
                }

                last_gamepad_state[joy].buttons[i] = buttons[i];
            }
            }*/
    // }
}
