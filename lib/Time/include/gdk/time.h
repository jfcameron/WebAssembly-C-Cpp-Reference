// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_TIME_H
#define GDK_TIME_TIME_H

namespace gdk::time
{        
    double getDeltaTime(void) noexcept; //destroy

    using UpdateFunctionSignature = std::function<void(const double &)>;

    //! 
    void addUpdateCallback(const UpdateFunctionSignature aUpdateFunction);

    //! 
    void addRenderCallback(const UpdateFunctionSignature aUpdateFunction);

    //! Get time since program started
    double sinceStart() noexcept;
}

// Should probbaly be moved?
namespace gdk
{
    //! traps the calling thread in the game loop, where it will remain for the program's lifetime.
    int main();
}

#endif
