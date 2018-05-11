#include <iostream>
#include <sstream>
#include <exception>

#include <GL/glfw.h>
//#include <emscripten/emscripten.h>

namespace jfc
{
    static void initOpenGL()
    {        
        if (!glfwInit()) std::runtime_error("Could not initialize GLFW!");

        const int width = 800, height = 600;
        if (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE)
        {
            std::runtime_error("glfwOpenWindow() failed\n");
        }        
    }

    static void draw()
    {
        //refactor to draw
        glClearColor(
            0.3921568627450980392156862745098f,
            0.58431372549019607843137254901961f,
            0.92941176470588235294117647058824f,
            1.0f);
            
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //this->drawCallback(aDelta);

        glfwSwapBuffers();
    }
}

int main()
{
    jfc::initOpenGL();
    
    std::cout << "Greetings from C++11!\n";

    jfc::draw();
    
    return 0;
}
