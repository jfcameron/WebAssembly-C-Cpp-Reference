// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-16.
#include "Time.h"
//thirdparty inc
#include <glfw/include/GLFW/glfw3.h> // must come after GL

using namespace GDK;
using namespace Time;

static double currentTime(0.);
static double lastTime(0.);

double Time::getTime(void) noexcept
{
    return glfwGetTime();
}

double Time::getDeltaTime(void) noexcept
{
    return currentTime;
}

double Time::updateDeltaTime(void) noexcept
{
    double time = currentTime;
    
    currentTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    return time;
}
