Human input library. Provides crossplat APIs for Keyboard, Mouse and Gamepads connected to the device.
Supports Linux, MacOS, Windows and Emscripten platforms. 

Implementation currently requires GLFW. Provide a ptr to an initialized glfw window struct via input::PROTECTED::initialize(ptr); glfwPollEvents() must be called regularily to update the state of input devices, this is not handled by input project itself
