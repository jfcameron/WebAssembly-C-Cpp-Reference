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
        double get(); //! get the elapsed time since timer started

        void reset(); //! restart the timer

        double getAndReset(); //! get elapsed time and reset the timer

        Timer();
    };
}

#endif
