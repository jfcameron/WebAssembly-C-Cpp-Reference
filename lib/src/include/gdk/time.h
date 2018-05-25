// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-16.
#ifndef GDK_TIME_TIME_H
#define GDK_TIME_TIME_H

namespace gdk
{
    namespace Time
    {
        //getEpoch
        
        /// Get time since program started
        double getTime(void) noexcept; //getTimeSinceStart?
        
        /// Gets delta time without resetting the delta timer
        double getDeltaTime(void) noexcept;
        
        /// Returns time since this was last called, call in the program update loop
        double updateDeltaTime(void) noexcept;
    }
}

#endif
