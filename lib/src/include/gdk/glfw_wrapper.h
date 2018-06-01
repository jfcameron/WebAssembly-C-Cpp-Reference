// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-05-15.

namespace GLFW
{
    /*!
      Force GDK to init. If you need to make GLFW calls at static time, you should place this call
      at the beginning of all such blocks to guarantee GLFW has initialized before you need to use it.
    */
    void InitEarly();
    
    void SwapBuffer();

    double GetTime();
}
