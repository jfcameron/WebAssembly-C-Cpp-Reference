// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_RESOURCES_PRIVATE_H
#define GDK_RESOURCES_PRIVATE_H

/// \brief These APIs must be used in order for resources.h to perform correctly.
///
/// \detailed this file should be hidden from the end user (the user of your library); it is irrelevant to them.
/// this file should be used and hidden behind a wrapper or intermediary library.
namespace gdk::resources::hidden
{
    //! as fetches are made, fetch tasks are put in the fetch queue.
    /// this function processes the fetch queue, performing the fetches.
    /// \note this function must be called by (at least one) thread for Resources to behave correctly
    /// \note thread safe
    void updateFetchQueue();

    //! runs the response handlers for completed fetches.
    /// \note this function must be called by the main thread (not thread safe) for Resources to behave correctly
    /// \note not thread safe; only call from mainthread
    void updateResponseQueue();
}

#endif
