// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_PRIVATE_H
#define GDK_TIME_PRIVATE_H

/// \brief These APIs must be used in order for time.h to perform correctly.
///
/// \detailed this file should be used and hidden behind a wrapper or intermediary library.
/// this file should be hidden from the end user (the user of your library); it is irrelevant to them.
namespace gdk::time::hidden
{
    //! traps the calling thread in a loop, where it will remain for the program's lifetime.
    int mainLoop();
}

#endif
