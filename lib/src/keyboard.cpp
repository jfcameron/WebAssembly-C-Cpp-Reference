// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/keyboard.h>
#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdk/glfw_wrapper.h>

#include <GLFW/glfw3.h>

#include <iostream>

using namespace gdk;

static constexpr char TAG[] = "Keyboard";

static inline int glfwKeyCodeFromKey(const Keyboard::Key &a)
{
    switch(a)
    {
        //Top Row
        case Keyboard::Key::Escape:       return GLFW_KEY_ESCAPE;
        case Keyboard::Key::F1:           return GLFW_KEY_F1;
        case Keyboard::Key::F2:           return GLFW_KEY_F2;
        case Keyboard::Key::F3:           return GLFW_KEY_F3;
        case Keyboard::Key::F4:           return GLFW_KEY_F4;
        case Keyboard::Key::F5:           return GLFW_KEY_F5;
        case Keyboard::Key::F6:           return GLFW_KEY_F6;
        case Keyboard::Key::F7:           return GLFW_KEY_F7;
        case Keyboard::Key::F8:           return GLFW_KEY_F8;
        case Keyboard::Key::F9:           return GLFW_KEY_F9;
        case Keyboard::Key::F10:          return GLFW_KEY_F10;
        case Keyboard::Key::F11:          return GLFW_KEY_F11;
        case Keyboard::Key::F12:          return GLFW_KEY_F12;
        case Keyboard::Key::PrintScreen:  return GLFW_KEY_PRINT_SCREEN;
        case Keyboard::Key::ScrollLock:   return GLFW_KEY_SCROLL_LOCK;
        case Keyboard::Key::PauseBreak:   return GLFW_KEY_PAUSE;
        
        //Alphabetical characters
        case Keyboard::Key::Q:            return GLFW_KEY_Q;
        case Keyboard::Key::W:            return GLFW_KEY_W;
        case Keyboard::Key::E:            return GLFW_KEY_E;
        case Keyboard::Key::R:            return GLFW_KEY_R;
        case Keyboard::Key::T:            return GLFW_KEY_T;
        case Keyboard::Key::Y:            return GLFW_KEY_Y;
        case Keyboard::Key::U:            return GLFW_KEY_U;
        case Keyboard::Key::I:            return GLFW_KEY_I;
        case Keyboard::Key::O:            return GLFW_KEY_O;
        case Keyboard::Key::P:            return GLFW_KEY_P;
        case Keyboard::Key::A:            return GLFW_KEY_A;
        case Keyboard::Key::S:            return GLFW_KEY_S;
        case Keyboard::Key::D:            return GLFW_KEY_D;
        case Keyboard::Key::F:            return GLFW_KEY_F;
        case Keyboard::Key::G:            return GLFW_KEY_G;
        case Keyboard::Key::H:            return GLFW_KEY_H;
        case Keyboard::Key::J:            return GLFW_KEY_J;
        case Keyboard::Key::K:            return GLFW_KEY_K;
        case Keyboard::Key::L:            return GLFW_KEY_L;
        case Keyboard::Key::Z:            return GLFW_KEY_Z;
        case Keyboard::Key::X:            return GLFW_KEY_X;
        case Keyboard::Key::C:            return GLFW_KEY_C;
        case Keyboard::Key::V:            return GLFW_KEY_V;
        case Keyboard::Key::B:            return GLFW_KEY_B;
        case Keyboard::Key::N:            return GLFW_KEY_N;
        case Keyboard::Key::M:            return GLFW_KEY_M;
        
        //Number row
        case Keyboard::Key::One:          return GLFW_KEY_1;
        case Keyboard::Key::Two:          return GLFW_KEY_2;
        case Keyboard::Key::Three:        return GLFW_KEY_3;
        case Keyboard::Key::Four:         return GLFW_KEY_4;
        case Keyboard::Key::Five:         return GLFW_KEY_5;
        case Keyboard::Key::Six:          return GLFW_KEY_6;
        case Keyboard::Key::Seven:        return GLFW_KEY_7;
        case Keyboard::Key::Eight:        return GLFW_KEY_8;
        case Keyboard::Key::Nine:         return GLFW_KEY_9;
        case Keyboard::Key::Zero:         return GLFW_KEY_0;
        case Keyboard::Key::Tilda:        return GLFW_KEY_GRAVE_ACCENT;
        case Keyboard::Key::Minus:        return GLFW_KEY_MINUS;
        case Keyboard::Key::Equals:       return GLFW_KEY_EQUAL;
        case Keyboard::Key::Backspace:    return GLFW_KEY_BACKSPACE;
        case Keyboard::Key::Home:         return GLFW_KEY_HOME;
        case Keyboard::Key::End:          return GLFW_KEY_END;
        
        //Q row
        case Keyboard::Key::Tab:          return GLFW_KEY_TAB;
        case Keyboard::Key::OpenBracket:  return GLFW_KEY_LEFT_BRACKET;
        case Keyboard::Key::CloseBracket: return GLFW_KEY_RIGHT_BRACKET;
        case Keyboard::Key::Backslash:    return GLFW_KEY_BACKSLASH;
        case Keyboard::Key::Insert:       return GLFW_KEY_INSERT;
        case Keyboard::Key::PageUp:       return GLFW_KEY_PAGE_UP;
        
        //A row
        case Keyboard::Key::Capslock:     return GLFW_KEY_CAPS_LOCK;
        case Keyboard::Key::SemiColon:    return GLFW_KEY_SEMICOLON;
        case Keyboard::Key::Quote:        return GLFW_KEY_APOSTROPHE;
        case Keyboard::Key::Enter:        return GLFW_KEY_ENTER;
        case Keyboard::Key::Delete:       return GLFW_KEY_DELETE;
        case Keyboard::Key::PageDown:     return GLFW_KEY_PAGE_DOWN;
            
        //Z row
        case Keyboard::Key::LeftShift:    return GLFW_KEY_LEFT_SHIFT;
        case Keyboard::Key::Comma:        return GLFW_KEY_COMMA;
        case Keyboard::Key::Period:       return GLFW_KEY_PERIOD;
        case Keyboard::Key::ForwardSlash: return GLFW_KEY_SLASH;
        case Keyboard::Key::RightShift:   return GLFW_KEY_RIGHT_SHIFT;
        
        //Bottom row
        case Keyboard::Key::LeftControl:  return GLFW_KEY_LEFT_CONTROL;
        case Keyboard::Key::LeftAlt:      return GLFW_KEY_LEFT_ALT;
        case Keyboard::Key::Space:        return GLFW_KEY_SPACE;
        case Keyboard::Key::RightAlt:     return GLFW_KEY_RIGHT_ALT;
        case Keyboard::Key::RightControl: return GLFW_KEY_RIGHT_CONTROL;
        
        //Arrow keys
        case Keyboard::Key::LeftArrow:    return GLFW_KEY_LEFT;
        case Keyboard::Key::RightArrow:   return GLFW_KEY_RIGHT;
        case Keyboard::Key::UpArrow:      return GLFW_KEY_UP;
        case Keyboard::Key::DownArrow:    return GLFW_KEY_DOWN;
        
        //Numpad
        case Keyboard::Key::Numlock:      return GLFW_KEY_NUM_LOCK;
        case Keyboard::Key::NumSlash:     return GLFW_KEY_SLASH;
        case Keyboard::Key::NumAsterisk:  return GLFW_KEY_KP_MULTIPLY;
        case Keyboard::Key::NumMinus:     return GLFW_KEY_KP_SUBTRACT;
        case Keyboard::Key::Num7:         return GLFW_KEY_KP_7;
        case Keyboard::Key::Num8:         return GLFW_KEY_KP_8;
        case Keyboard::Key::Num9:         return GLFW_KEY_KP_9;
        case Keyboard::Key::NumPlus:      return GLFW_KEY_KP_ADD;
        case Keyboard::Key::Num4:         return GLFW_KEY_KP_4;
        case Keyboard::Key::Num5:         return GLFW_KEY_KP_5;
        case Keyboard::Key::Num6:         return GLFW_KEY_KP_6;
        case Keyboard::Key::Num1:         return GLFW_KEY_KP_1;
        case Keyboard::Key::Num2:         return GLFW_KEY_KP_2;
        case Keyboard::Key::Num3:         return GLFW_KEY_KP_3;
        case Keyboard::Key::NumEnter:     return GLFW_KEY_KP_ENTER;
        case Keyboard::Key::Num0:         return GLFW_KEY_KP_0;
        case Keyboard::Key::NumPeriod:    return GLFW_KEY_KP_DECIMAL;
    }
}

bool Keyboard::getKeyDown(const Key &aKeyCode)
{
    return glfw::GetKey(glfwKeyCodeFromKey(aKeyCode));
}

bool Keyboard::getKey(const Key &aKeyCode)
{
    (void)aKeyCode;
    throw gdk::Exception(TAG, "Keyboard::getKey(const Key &aKeyCode) not implemented");
}
