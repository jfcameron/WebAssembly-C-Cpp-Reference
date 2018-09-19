// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#include <gdk/gameloop.h>
#include <gdk/glfw_wrapper.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#endif

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#define MAXSAMPLES 100
int tickindex=0;
int ticksum=0;
int ticklist[MAXSAMPLES];

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPLES last frames */

double CalcAverageTick(int newtick)
{
    ticksum-=ticklist[tickindex];  /* subtract value falling off */
    ticksum+=newtick;              /* add new value */
    ticklist[tickindex]=newtick;   /* save new value so it can be subtracted later */
    if(++tickindex==MAXSAMPLES)    /* inc buffer index */
        tickindex=0;

    /* return average */
    return((double)ticksum/MAXSAMPLES);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
#if defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Windows
        const unsigned int thread_count = std::thread::hardware_concurrency();
#elif defined JFC_TARGET_PLATFORM_Emscripten
        const unsigned int thread_count = 1;
#else 
#error "unsupported platform"
#endif

    std::vector<std::unique_ptr<gdk::GameLoop>> gameloops;
}

namespace gdk
{
    void GameLoop::Create(const loop_function_type aMainUpdate, const loop_function_type aMainDraw, const worker_function_type aWorkerUpdate)
    {
        gameloops.push_back(std::unique_ptr<GameLoop>(new gdk::GameLoop(aMainUpdate, aMainDraw, aWorkerUpdate)));
    }

    void GameLoop::destroy()
    {
        m_IsAlive = false;

#if defined JFC_TARGET_PLATFORM_Emscripten
        emscripten_cancel_main_loop();
#endif

        for (size_t i = {0}, s = gameloops.size(); i < s; ++i) if (gameloops[i].get() == this) gameloops.erase(gameloops.begin() + i);
    }
    
    GameLoop::GameLoop(const loop_function_type aMainUpdate, const loop_function_type aMainDraw, const worker_function_type aWorkerUpdate)
    : m_MainUpdate(aMainUpdate)
    , m_MainDraw(aMainDraw)
    , m_WorkerUpdate(aWorkerUpdate)
    {
        std::vector<std::thread> workers;

        for (unsigned int i = {0}, s = thread_count > 1 ? thread_count - 1 : 0; i < s; ++i)
        {
            workers.push_back(std::thread([&]()
            {
                while(m_IsAlive) aWorkerUpdate();
                
                for (auto &worker : workers) worker.join();
            }));
        }

        auto loopWrapper = [](void *const vpMe)
        {
            auto *const me = static_cast<GameLoop *const>(vpMe);

            const double deltaTime = me->updateLoopTimer.getAndReset();
            //std::cout << "miliseconds: " <<  CalcAverageTick(static_cast<int>(deltaTime * 1000)) << std::endl;

            // Update work \todo lock me at UPDATE RATE
            {
                glfw::PollEvents();

                me->m_MainUpdate(deltaTime); // Should be frame locked?

                if (thread_count < 2) me->m_WorkerUpdate(); // Worker work is done on main if there is only one thread or if hardware_concurrency is "not well defined or not computable" (0)
            }
            // Draw work \todo draw me as fast as possible. Need to interpolate things? Need speed, probably acceleration too.
            {
                me->m_MainDraw(deltaTime); // Or this?

                glfw::SwapBuffer();
            }
        };

#if defined JFC_TARGET_PLATFORM_Emscripten
        emscripten_set_main_loop_arg(loopWrapper, this, 0, 0);
#elif defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Windows
        while(m_IsAlive) loopWrapper(this);
#else
#error "gameloop is being built for an unsupported platform"
#endif

    }
}
