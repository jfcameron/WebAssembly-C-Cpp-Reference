#include <gdk/opengl.h>

#include <gdk/color.h>
#include <gdk/glh.h>
#include <gdk/glfw_wrapper.h>

namespace gdk
{
    namespace gfx
    {   
        void init()
        {
            glh::ClearColor(gdk::Color::CornflowerBlue);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void draw()
        {
            glh::ClearColor(gdk::Color::CornflowerBlue);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GLFW::SwapBuffer();
        }
    }
}
