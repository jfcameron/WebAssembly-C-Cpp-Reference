// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_TIME_H
#define GDK_TIME_TIME_H

#include <functional>

namespace gdk::time
{
    using UpdateFunctionSignature = std::function<void(const double &)>;

    //! 
    void addUpdateCallback(const UpdateFunctionSignature aUpdateFunction);

    //! 
    void addRenderCallback(const UpdateFunctionSignature aUpdateFunction);

    //! Get time since program started
    double sinceStart() noexcept;
}

#endif
