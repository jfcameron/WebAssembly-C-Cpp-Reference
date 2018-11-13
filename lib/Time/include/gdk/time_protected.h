// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_TIME_PROTECTED_H
#define GDK_TIME_PROTECTED_H

struct GLFWwindow;

/// \brief These APIs must be used in order for time.h to perform correctly.
///
/// \detailed this file should be used and hidden behind a wrapper or intermediary library.
/// this file should be hidden from the end user (the user of your library); it is irrelevant to them.
namespace gdk::time::PROTECTED
{
    /// \brief initialize time project using GLFW-dependent implementation
    void initialize(GLFWwindow *const aGLFW);
}

#endif
