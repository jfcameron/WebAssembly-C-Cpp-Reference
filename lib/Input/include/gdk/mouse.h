// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_INPUT_MOUSE_H
#define GDK_INPUT_MOUSE_H

#include <memory>

namespace gdk
{
    struct Vector2;
    
    /// \brief Get mouse keys and position on a window    
    namespace mouse
    {      
        /// \brief Represents all detectable mouse buttons
        enum class Button
        { 
            Left, 
            Right, 
            Middle, 
            Four, 
            Five, 
            Six, 
            Seven, 
            Eight 
        };
            
        /// \brief Check if the button is being held down
        bool getButtonDown(const Button &aKeyCode);

        /// \brief Check if the button was just pressed
        bool getButton(const Button &aKeyCode);

        /// \brief Viewcoordinate of cursor
        Vector2 getCursorPosition();

        /// \brief Get amount of cursor movement since the last frame
        Vector2 getDelta();
    }
}

#endif
