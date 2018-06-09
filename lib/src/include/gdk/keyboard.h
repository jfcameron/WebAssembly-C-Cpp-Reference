// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_INPUT_KEYBOARD_H
#define GDK_INPUT_KEYBOARD_H

#include <iosfwd>
#include <memory>

namespace gdk
{
    /*!
      Get keystates for a given Window
    */
    namespace Keyboard
    {            
        //!  Represents all detectable keys       
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
            
        //! Check if the key is being held down
        bool getKeyDown(const Key &aKeyCode);
            
        //! Check if the key was just pressed
        bool getKey(const Key &aKeyCode);            
    }
}

#endif
