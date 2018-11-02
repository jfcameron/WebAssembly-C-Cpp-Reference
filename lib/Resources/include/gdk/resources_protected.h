// © 2018 Joseph Cameron - All Rights Reserved
/// \brief The APIs declared herein must be used in order for resources.h to perform correctly.
///
/// \detailed If the consuming project is a library and not an executable then this header should NOT be propagated to users of the consuming project. Propagating this file will pollute
/// your user's include path and give your users an opportunity to cause this (and therefore) your library to behave incorrectly (by using the APIs declared in this file).
/// These APIs should be called in a way that allows your library to behave as intended and should be hidden from your users.

#ifndef GDK_RESOURCES_PROTECTED_H
#define GDK_RESOURCES_PROTECTED_H

namespace gdk::resources::PROTECTED
{
    /// \brief [required] runs the response handlers for completed fetches.
    /// \note this function must be called periodically by the main thread (not thread safe) for Resources to behave correctly
    /// \note not thread safe; only call from mainthread
    void MainThreadUpdate();

    /// \brief [required] as fetches are made, fetch tasks are put in the fetch queue.
    /// this function processes the fetch queue, performing the fetches.
    /// \note this function must be called periodically by (at least one) thread for Resources to behave correctly
    /// \note fetches can be very slow. Performing this work on the main thread will result in noticable blocking. If this is not acceptable, don't use the mainthread here.
    /// \note thread safe; call from as many threads as you want. More threads will increase the parallelism of the library. Whether or not this will improve performance is device dependant.
    void WorkerThreadUpdate();

    /// \brief [optional] logging interface.
    ///
    /// \detailed logging_interface members are used by the resource project to record logs.
    /// log, warn, error represent different degrees of severity of the log.
    /// \note if the user does not provide an implementation, then the default behaviour is to not log that severity level.
    namespace logging_interface
    {
        using logging_function_signature = std::function<void(std::string aTag, std::string aMessage)>;

        extern logging_function_signature log;
    }
}

#endif
