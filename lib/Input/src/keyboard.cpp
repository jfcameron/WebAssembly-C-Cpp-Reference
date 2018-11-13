// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/keyboard.h>
#include <gdk/input_private.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

using namespace gdk;

static constexpr char TAG[] = "Keyboard";

static inline int glfwKeyCodeFromKey(const keyboard::Key &a)
{
    switch(a)
    {
        //Top Row
        case keyboard::Key::Escape:       return GLFW_KEY_ESCAPE;
        case keyboard::Key::F1:           return GLFW_KEY_F1;
        case keyboard::Key::F2:           return GLFW_KEY_F2;
        case keyboard::Key::F3:           return GLFW_KEY_F3;
        case keyboard::Key::F4:           return GLFW_KEY_F4;
        case keyboard::Key::F5:           return GLFW_KEY_F5;
        case keyboard::Key::F6:           return GLFW_KEY_F6;
        case keyboard::Key::F7:           return GLFW_KEY_F7;
        case keyboard::Key::F8:           return GLFW_KEY_F8;
        case keyboard::Key::F9:           return GLFW_KEY_F9;
        case keyboard::Key::F10:          return GLFW_KEY_F10;
        case keyboard::Key::F11:          return GLFW_KEY_F11;
        case keyboard::Key::F12:          return GLFW_KEY_F12;
        case keyboard::Key::PrintScreen:  return GLFW_KEY_PRINT_SCREEN;
        case keyboard::Key::ScrollLock:   return GLFW_KEY_SCROLL_LOCK;
        case keyboard::Key::PauseBreak:   return GLFW_KEY_PAUSE;
        
        //Alphabetical characters
        case keyboard::Key::Q:            return GLFW_KEY_Q;
        case keyboard::Key::W:            return GLFW_KEY_W;
        case keyboard::Key::E:            return GLFW_KEY_E;
        case keyboard::Key::R:            return GLFW_KEY_R;
        case keyboard::Key::T:            return GLFW_KEY_T;
        case keyboard::Key::Y:            return GLFW_KEY_Y;
        case keyboard::Key::U:            return GLFW_KEY_U;
        case keyboard::Key::I:            return GLFW_KEY_I;
        case keyboard::Key::O:            return GLFW_KEY_O;
        case keyboard::Key::P:            return GLFW_KEY_P;
        case keyboard::Key::A:            return GLFW_KEY_A;
        case keyboard::Key::S:            return GLFW_KEY_S;
        case keyboard::Key::D:            return GLFW_KEY_D;
        case keyboard::Key::F:            return GLFW_KEY_F;
        case keyboard::Key::G:            return GLFW_KEY_G;
        case keyboard::Key::H:            return GLFW_KEY_H;
        case keyboard::Key::J:            return GLFW_KEY_J;
        case keyboard::Key::K:            return GLFW_KEY_K;
        case keyboard::Key::L:            return GLFW_KEY_L;
        case keyboard::Key::Z:            return GLFW_KEY_Z;
        case keyboard::Key::X:            return GLFW_KEY_X;
        case keyboard::Key::C:            return GLFW_KEY_C;
        case keyboard::Key::V:            return GLFW_KEY_V;
        case keyboard::Key::B:            return GLFW_KEY_B;
        case keyboard::Key::N:            return GLFW_KEY_N;
        case keyboard::Key::M:            return GLFW_KEY_M;
        
        //Number row
        case keyboard::Key::One:          return GLFW_KEY_1;
        case keyboard::Key::Two:          return GLFW_KEY_2;
        case keyboard::Key::Three:        return GLFW_KEY_3;
        case keyboard::Key::Four:         return GLFW_KEY_4;
        case keyboard::Key::Five:         return GLFW_KEY_5;
        case keyboard::Key::Six:          return GLFW_KEY_6;
        case keyboard::Key::Seven:        return GLFW_KEY_7;
        case keyboard::Key::Eight:        return GLFW_KEY_8;
        case keyboard::Key::Nine:         return GLFW_KEY_9;
        case keyboard::Key::Zero:         return GLFW_KEY_0;
        case keyboard::Key::Tilda:        return GLFW_KEY_GRAVE_ACCENT;
        case keyboard::Key::Minus:        return GLFW_KEY_MINUS;
        case keyboard::Key::Equals:       return GLFW_KEY_EQUAL;
        case keyboard::Key::Backspace:    return GLFW_KEY_BACKSPACE;
        case keyboard::Key::Home:         return GLFW_KEY_HOME;
        case keyboard::Key::End:          return GLFW_KEY_END;
        
        //Q row
        case keyboard::Key::Tab:          return GLFW_KEY_TAB;
        case keyboard::Key::OpenBracket:  return GLFW_KEY_LEFT_BRACKET;
        case keyboard::Key::CloseBracket: return GLFW_KEY_RIGHT_BRACKET;
        case keyboard::Key::Backslash:    return GLFW_KEY_BACKSLASH;
        case keyboard::Key::Insert:       return GLFW_KEY_INSERT;
        case keyboard::Key::PageUp:       return GLFW_KEY_PAGE_UP;
        
        //A row
        case keyboard::Key::Capslock:     return GLFW_KEY_CAPS_LOCK;
        case keyboard::Key::SemiColon:    return GLFW_KEY_SEMICOLON;
        case keyboard::Key::Quote:        return GLFW_KEY_APOSTROPHE;
        case keyboard::Key::Enter:        return GLFW_KEY_ENTER;
        case keyboard::Key::Delete:       return GLFW_KEY_DELETE;
        case keyboard::Key::PageDown:     return GLFW_KEY_PAGE_DOWN;
            
        //Z row
        case keyboard::Key::LeftShift:    return GLFW_KEY_LEFT_SHIFT;
        case keyboard::Key::Comma:        return GLFW_KEY_COMMA;
        case keyboard::Key::Period:       return GLFW_KEY_PERIOD;
        case keyboard::Key::ForwardSlash: return GLFW_KEY_SLASH;
        case keyboard::Key::RightShift:   return GLFW_KEY_RIGHT_SHIFT;
        
        //Bottom row
        case keyboard::Key::LeftControl:  return GLFW_KEY_LEFT_CONTROL;
        case keyboard::Key::LeftAlt:      return GLFW_KEY_LEFT_ALT;
        case keyboard::Key::Space:        return GLFW_KEY_SPACE;
        case keyboard::Key::RightAlt:     return GLFW_KEY_RIGHT_ALT;
        case keyboard::Key::RightControl: return GLFW_KEY_RIGHT_CONTROL;
        
        //Arrow keys
        case keyboard::Key::LeftArrow:    return GLFW_KEY_LEFT;
        case keyboard::Key::RightArrow:   return GLFW_KEY_RIGHT;
        case keyboard::Key::UpArrow:      return GLFW_KEY_UP;
        case keyboard::Key::DownArrow:    return GLFW_KEY_DOWN;
        
        //Numpad
        case keyboard::Key::Numlock:      return GLFW_KEY_NUM_LOCK;
        case keyboard::Key::NumSlash:     return GLFW_KEY_SLASH;
        case keyboard::Key::NumAsterisk:  return GLFW_KEY_KP_MULTIPLY;
        case keyboard::Key::NumMinus:     return GLFW_KEY_KP_SUBTRACT;
        case keyboard::Key::Num7:         return GLFW_KEY_KP_7;
        case keyboard::Key::Num8:         return GLFW_KEY_KP_8;
        case keyboard::Key::Num9:         return GLFW_KEY_KP_9;
        case keyboard::Key::NumPlus:      return GLFW_KEY_KP_ADD;
        case keyboard::Key::Num4:         return GLFW_KEY_KP_4;
        case keyboard::Key::Num5:         return GLFW_KEY_KP_5;
        case keyboard::Key::Num6:         return GLFW_KEY_KP_6;
        case keyboard::Key::Num1:         return GLFW_KEY_KP_1;
        case keyboard::Key::Num2:         return GLFW_KEY_KP_2;
        case keyboard::Key::Num3:         return GLFW_KEY_KP_3;
        case keyboard::Key::NumEnter:     return GLFW_KEY_KP_ENTER;
        case keyboard::Key::Num0:         return GLFW_KEY_KP_0;
        case keyboard::Key::NumPeriod:    return GLFW_KEY_KP_DECIMAL;
    }
}

bool keyboard::getKeyDown(const Key &aKeyCode)
{
    return static_cast<bool>(glfwGetKey(gdk::input::PRIVATE::pGLFWwindow, glfwKeyCodeFromKey(aKeyCode))); //return glfw::GetKey(glfwKeyCodeFromKey(aKeyCode));
}

bool keyboard::getKey(const Key &aKeyCode)
{
    (void)aKeyCode;
    
    throw std::runtime_error(std::string(TAG).append("/keyboard::getKey(const Key &aKeyCode) not implemented"));
}
