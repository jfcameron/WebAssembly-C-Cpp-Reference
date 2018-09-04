// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#include <gdk/glfw_wrapper.h>
#include <gdk/time.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
#include <emscripten.h>
#endif

#include <vector>

namespace
{
    double currentTime = {0};
    double lastTime =    {0};

    double updateDeltaTime() noexcept
    {
        double time = currentTime;
    
        currentTime = glfw::GetTime() - lastTime;
        lastTime = glfw::GetTime();

        return time;
    }

    std::vector<gdk::time::UpdateFunctionSignature> updateFunctions;
    std::vector<gdk::time::UpdateFunctionSignature> drawFunctions;
}

namespace
{
    void gameloop() //probably refactor
    {
        const double deltaTime = updateDeltaTime();

        //for (const auto &item : updateFunctions) item(deltaTime);

        for (const auto &item : drawFunctions) item(deltaTime);
        
        glfw::PollEvents();
        glfw::SwapBuffer(); // This is not required on emscriptn for whatever reason. That worries me a bit. 
    }
}

namespace gdk::time
{
    void addUpdateCallback(const UpdateFunctionSignature aUpdateFunction)
    {
        updateFunctions.push_back(aUpdateFunction);
    }
    
    void addRenderCallback(const UpdateFunctionSignature aUpdateFunction)
    {
        drawFunctions.push_back(aUpdateFunction);
    }
    
    double sinceStart(void) noexcept
    {
        return glfw::GetTime();
    }

    double getDeltaTime(void) noexcept
    {
        return currentTime;
    }
}

namespace gdk::time::hidden
{
    int mainLoop()
    {
#if defined JFC_TARGET_PLATFORM_Emscripten

        emscripten_set_main_loop(gameloop, -1, 0); // Negative fps will force requestAnimationFrame usage
        
        //emscripten_set_main_loop(update, 60, 0); // must manually call out to requestAnimationFrame and the other timing api to separate gl and logic

#elif defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Windows

        while(true) gameloop();

#endif
        return EXIT_SUCCESS;
    }
}
