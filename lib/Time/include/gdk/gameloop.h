// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_GAMELOOP_H
#define GDK_TIME_GAMELOOP_H

#include <atomic>
#include <functional>
#include <gdk/timer.h>
#include <memory>
#include <vector>

namespace gdk
{
    /// \brief crossplatform gameloop. Can take advantage of multiple threads if available.
    ///
    /// \warning on most platforms it traps calling thread upon construction. Released when terminate is called. It does not on emscripten.
    ///
    /// \detailed a threadpool will be spawned of size std::thread::hardware_concurrency() - 1.
    /// Threading is not ideal; there is a strong distinction between the main thread (the single thread made available at main) 
    /// and the pooled workers it subsequently spawns. GameLoop was made to be used with OpenGL and other game APIs. These are 
    /// not thread friendly APIs; hence the main vs worker distinction. Any work that can be parallelized should be placed in aWorkerUpdate.
    ///
    /// \todo TIMING is incomplete! Must enforce timing for update, draw, etc.
    class GameLoop
    {
    public:
        using loop_function_type =   std::function<void(const double &)>;
        using worker_function_type = std::function<void()>;
        
    private:
        std::atomic<bool> m_IsAlive = {true};

        Timer updateLoopTimer = {};

        const loop_function_type   m_MainUpdate;
        const loop_function_type   m_MainDraw;
        const worker_function_type m_WorkerUpdate;

        //! Constructs the loop and traps the calling thread until terminate is called.
        GameLoop(const loop_function_type aMainUpdate, const loop_function_type aMainDraw, const worker_function_type aWorkerUpdate);

    public:
        //! ends the loop. Freeing the thread on which the loop was constructed
        void destroy();

        //! Creates a new GameLoop instance. Returns a weak pointer to it
        static void Create(const loop_function_type aMainUpdate, const loop_function_type aMainDraw, const worker_function_type aWorkerUpdate);
    };
}

#endif
