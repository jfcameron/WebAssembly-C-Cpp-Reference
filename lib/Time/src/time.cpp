// © 2018 Joseph Cameron - All Rights Reserved

#include <gdktime/buildinfo.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
    #include <emscripten.h>
#endif

//#include <gdk/gamepads_private.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/time.h>

#include <vector>

namespace
{
    double currentTime(0.);
    double lastTime(0.);

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
    
/////////////////////////

    double sinceStart(void) noexcept
    {
        return glfw::GetTime();
    }

    double getDeltaTime(void) noexcept
    {
        return currentTime;
    }
}

namespace
{
    void gameloop() //probably refactor
    {
        const double deltaTime = updateDeltaTime();

        //for (const auto &item : updateFunctions) item(deltaTime);

        for (const auto &item : drawFunctions) item(deltaTime);

        //gamepads::update(); //This stuff should be pushed back to a gdk::time::addMainLoopWork(work) or something like that. Reverse the dependencies. or maybe add some work in gdk that does such plumbing. private header called update etc.
        glfw::PollEvents();
        glfw::SwapBuffer(); // This is not required on emscriptn for whatever reason. That worries me a bit. 
    }
}

namespace gdk
{
    int main()
    {
        //gamepads::initialize();

#if defined JFC_TARGET_PLATFORM_Emscripten

        emscripten_set_main_loop(gameloop, -1, 0); // Negative fps will force requestAnimationFrame usage
        
        //emscripten_set_main_loop(update, 60, 0); // must manually call out to requestAnimationFrame and the other timing api to separate gl and logic

#elif defined JFC_TARGET_PLATFORM_Darwin || defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Windows

        while(true) gameloop();

#endif

        return EXIT_SUCCESS;
    }
}
