#ifndef GDK_OPENGL
#define GDK_OPENGL

#include <gdkgraphics/buildinfo.h>

#ifdef JFC_TARGET_PLATFORM_Emscripten
    #include <GLES2/gl2.h>
#elif defined JFC_TARGET_PLATFORM_Darwin
    #include <OpenGL/gl.h>
#elif defined JFC_TARGET_PLATFORM_Linux
//    #include <GL/gl.h>
    #include <GL/glew.h>
#elif defined JFC_TARGET_PLATFORM_Windows
    #error win not supported
#else
    #error the current platform is not supported
#endif

namespace gdk
{
    //! Force OpenGL to init. If you need to make GL calls at static time, you should place this call
    /// at the beginning of all such blocks to guarantee the GL context has initialized before you need to use it.
    void InitEarlyOpenGL();
}

#endif
