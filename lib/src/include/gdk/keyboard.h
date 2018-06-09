// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#ifndef GDK_INPUT_KEYBOARD_H
#define GDK_INPUT_KEYBOARD_H

//std inc
#include <iosfwd>
#include <memory>

struct GLFWwindow;
namespace GDK{namespace GFX{class Window;}}

namespace GDK
{
    namespace Input
    {
        /*!
         Get keystates for a given Window
         */
        class Keyboard final
        {
            friend std::ostream &operator<< (std::ostream &, const Input::Keyboard &);
            
            // Data members
            std::weak_ptr<GLFWwindow> m_HandleToGLFWWindow = {};
            
        public:
            /*!
             Represents all detectable keys
             */
            enum class Key
            {
                //Top Row
                Escape,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,PrintScreen,ScrollLock,PauseBreak,
                
                //Alphabetical characters
                Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,H,J,K,L,Z,X,C,V,B,N,M,
                
                //Number row
                One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Zero,
                Tilda,Minus,Equals,Backspace,Home,End,
                
                //Q row
                Tab,OpenBracket,CloseBracket,Backslash,Insert,PageUp,
                
                //A row
                Capslock,SemiColon,Quote,Enter,Delete,PageDown,
                
                //Z row
                LeftShift,Comma,Period,ForwardSlash,RightShift,
                
                //Bottom row
                LeftControl,LeftAlt,Space,RightAlt,RightControl,
                
                //Arrow keys
                LeftArrow,RightArrow,UpArrow,DownArrow,
                
                //Numpad
                Numlock,NumSlash,NumAsterisk,NumMinus,
                Num7,Num8,Num9,NumPlus,
                Num4,Num5,Num6,
                Num1,Num2,Num3,NumEnter,
                Num0,NumPeriod
            };
            
            // Public methods
            /// Check if the key is being held down
            bool getKeyDown(const Key &aKeyCode) const;
            
            /// Check if the key was just pressed
            bool getKey(const Key &aKeyCode) const;
            
            // Mutating operators
            Keyboard &operator=(const Keyboard &) = default;
            Keyboard &operator=(Keyboard &&) = default;
      
            // Constructors, destructors
            Keyboard(const GFX::Window &);
            Keyboard() = delete;
            Keyboard(const Keyboard &) = default;
            Keyboard(Keyboard &&) = default;
            ~Keyboard() = default;
        };

        std::ostream &operator<< (std::ostream &, const Input::Keyboard &);
    }
}

#endif /* GDK_INPUT_KEYBOARD_H  */
