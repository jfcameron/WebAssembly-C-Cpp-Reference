// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/mouse.h>
#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdk/vector2.h>
#include <gdk/glfw_wrapper.h>

#include <GLFW/glfw3.h>

#include <iostream>

using namespace gdk;

static constexpr char TAG[] = "Mouse";

static inline int glfwMouseButtonFromButton(const Mouse::Button &a)
{
    switch(a)
    {
        case Mouse::Button::Left:   return GLFW_MOUSE_BUTTON_LEFT;
        case Mouse::Button::Right:  return GLFW_MOUSE_BUTTON_RIGHT;
        case Mouse::Button::Middle: return GLFW_MOUSE_BUTTON_MIDDLE;
        case Mouse::Button::Four:   return GLFW_MOUSE_BUTTON_4;
        case Mouse::Button::Five:   return GLFW_MOUSE_BUTTON_5;
        case Mouse::Button::Six:    return GLFW_MOUSE_BUTTON_6;
        case Mouse::Button::Seven:  return GLFW_MOUSE_BUTTON_7;
        case Mouse::Button::Eight:  return GLFW_MOUSE_BUTTON_8;
    }
}

bool Mouse::getButtonDown(const Button &aButton)
{
    return static_cast<bool>(glfw::GetMouseButton(glfwMouseButtonFromButton(aButton)));
}

Vector2 Mouse::getCursorPosition()
{
    return glfw::GetCursorPos();
}

bool Mouse::getButton(const Button &aKeyCode)
{
    (void)aKeyCode;
    throw gdk::Exception(TAG, "Mouse::getButton(const Button &aKeyCode) not implemented");
}
