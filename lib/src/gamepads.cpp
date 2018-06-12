// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/gamepads.h>
#include <gdk/glfw_wrapper.h>

#include <GLFW/glfw3.h>
#include <emscripten.h>

#include <assert.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
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

namespace gdk::gamepads
{
    void initialize()
    {
        glfwSetJoystickCallback(
            [](int joy, int event)
            {
                if (event == GLFW_CONNECTED)
                {
                    std::cout << "Joystick was connected: " << joy << glfwGetJoystickName(joy) << std::endl;
                }
                else if (event == GLFW_DISCONNECTED)
                {
                    std::cout << "Joystick was disconnected: " << joy << std::endl;
                }
            });
    }
    
    void update()
    {
        int joystick_count = 0;
    
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
        }

        if (joystick_count == 0) printf("No joysticsk detected\n");      
    }
}
