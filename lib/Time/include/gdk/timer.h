// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_TIMER_H
#define GDK_TIME_TIMER_H

namespace gdk
{
    /// \brief no brief
    ///
    /// \detailed no detailed
    class Timer final
    {
        double currentTime = {0};
        double lastTime =    {0};
    
    public:
        /// \brief get the elapsed time since timer started
        double get(); 

        /// \brief restart the timer
        void reset(); 

        /// \brief get elapsed time and reset the timer
        double getAndReset(); 

        Timer();
    };
}

#endif
