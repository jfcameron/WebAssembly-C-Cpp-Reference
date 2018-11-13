// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/input_private.h>
#include <gdk/mouse.h>
#include <gdk/vector2.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

static constexpr char TAG[] = "mouse";

namespace gdk::mouse
{
    static inline int glfwmouseButtonFromButton(const mouse::Button &a)
    {
        switch(a)
        {
            case Button::Left:   return GLFW_MOUSE_BUTTON_LEFT;
            case Button::Right:  return GLFW_MOUSE_BUTTON_RIGHT;
            case Button::Middle: return GLFW_MOUSE_BUTTON_MIDDLE;
            case Button::Four:   return GLFW_MOUSE_BUTTON_4;
            case Button::Five:   return GLFW_MOUSE_BUTTON_5;
            case Button::Six:    return GLFW_MOUSE_BUTTON_6;
            case Button::Seven:  return GLFW_MOUSE_BUTTON_7;
            case Button::Eight:  return GLFW_MOUSE_BUTTON_8;
        }
    }    
   
    bool getButtonDown(const Button &aButton)
    {
        return static_cast<bool>(glfwGetMouseButton(gdk::input::PRIVATE::pGLFWwindow, glfwmouseButtonFromButton(aButton))); //return static_cast<bool>(glfw::GetMouseButton(glfwmouseButtonFromButton(aButton)));
    }

    Vector2 getCursorPosition()
    {
        //return glfw::GetCursorPos();

        double x,y;
        glfwGetCursorPos(gdk::input::PRIVATE::pGLFWwindow, &x, &y);
        
        return Vector2(x, y);
    }

    bool getButton(const Button &aKeyCode)
    {
        throw std::runtime_error(std::string(TAG).append("/mouse::getButton(const Button &aKeyCode) not implemented"));
    }

    Vector2 getDelta()
    {
        throw std::runtime_error(std::string(TAG).append("/mouse::getDelta not implemented"));
    }
}
