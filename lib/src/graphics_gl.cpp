#include <GLES2/gl2.h>

#include <gdk/color.h>
#include <gdk/glh.h>
#include <gdk/glfw_wrapper.h>

namespace gdk
{
    namespace gfx
    {   
        void init()
        {
            GLH::ClearColor(GDK::Color::CornflowerBlue);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void draw()
        {
            GLH::ClearColor(GDK::Color::CornflowerBlue);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GLFW::SwapBuffer();
        }
    }
}
