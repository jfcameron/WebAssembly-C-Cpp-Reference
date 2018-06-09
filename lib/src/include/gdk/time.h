// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_TIME_H
#define GDK_TIME_TIME_H

namespace gdk::time
{
    //! getEpoch
        
    //! Get time since program started
    double sinceStart(void) noexcept; //getTimeSinceStart?
        
    //! Gets delta time without resetting the delta timer
    double getDeltaTime(void) noexcept;
        
    //! Returns time since this was last called, call in the program update loop
    double updateDeltaTime(void) noexcept;
}

#endif
