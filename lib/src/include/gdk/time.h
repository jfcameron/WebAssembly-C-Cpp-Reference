// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-16.
#ifndef GDK_TIME_TIME_H
#define GDK_TIME_TIME_H

namespace GDK
{
    namespace Time
    {
        /// Get time since program started
        double getTime(void) noexcept;
        
        /// Gets delta time without resetting the delta timer
        double getDeltaTime(void) noexcept;
        
        /// Returns time since this was last called, call in the program update loop
        double updateDeltaTime(void) noexcept;
    }
}

#endif /* GDK_TIME_TIME_H  */
