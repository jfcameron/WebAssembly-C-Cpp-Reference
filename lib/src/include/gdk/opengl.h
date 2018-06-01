#ifndef gdk_GFX_GL
#define gdk_GFX_GL

#include <GLES2/gl2.h>

namespace gdk
{
    /*!
      Force OpenGL to init. If you need to make GL calls at static time, you should place this call
      at the beginning of all such blocks to guarantee the GL context has initialized before you need to use it.
    */
    void InitEarlyOpenGL();
}

#endif
