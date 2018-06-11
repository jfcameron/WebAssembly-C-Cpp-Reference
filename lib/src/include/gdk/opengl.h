#ifndef GDK_OPENGL
#define GDK_OPENGL

#include <GLES2/gl2.h> //This is not portable

namespace gdk
{
    /*!
      Force OpenGL to init. If you need to make GL calls at static time, you should place this call
      at the beginning of all such blocks to guarantee the GL context has initialized before you need to use it.
    */
    void InitEarlyOpenGL();
}

#endif
