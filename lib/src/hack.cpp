#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

void hack()
{
    //int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

    //std::cout << "present: " << present << "\n";

    std::cout << "gamepad stuff: "
              << glfwJoystickPresent(GLFW_JOYSTICK_1)
              << glfwJoystickPresent(GLFW_JOYSTICK_2)
              << glfwJoystickPresent(GLFW_JOYSTICK_3)
              << glfwJoystickPresent(GLFW_JOYSTICK_4)
              << glfwJoystickPresent(GLFW_JOYSTICK_5)
              << glfwJoystickPresent(GLFW_JOYSTICK_6)
              << glfwJoystickPresent(GLFW_JOYSTICK_7)
              <<glfwJoystickPresent(GLFW_JOYSTICK_8)
              <<glfwJoystickPresent(GLFW_JOYSTICK_9)
              <<glfwJoystickPresent(GLFW_JOYSTICK_10)
              <<glfwJoystickPresent(GLFW_JOYSTICK_11)
              <<glfwJoystickPresent(GLFW_JOYSTICK_12)
              <<glfwJoystickPresent(GLFW_JOYSTICK_13)
              <<glfwJoystickPresent(GLFW_JOYSTICK_14)
              <<glfwJoystickPresent(GLFW_JOYSTICK_15)
              <<glfwJoystickPresent(GLFW_JOYSTICK_LAST)
              << std::endl;

    for (int j = GLFW_JOYSTICK_1; j < GLFW_JOYSTICK_16; ++j) {
    int joy = GLFW_JOYSTICK_1 + j;
    if (!glfwJoystickPresent(joy)) continue;

    static struct {
      int axes_count;
      float axes[16];
      int button_count;
      unsigned char buttons[16];
    } last_gamepad_state[16] = {0};

    const char *name = glfwGetJoystickName(joy);

    int axes_count = 0;
    const float *axes = glfwGetJoystickAxes(joy, &axes_count);

    int button_count = 0;
    const unsigned char *buttons = glfwGetJoystickButtons(joy, &button_count);

    last_gamepad_state[joy].axes_count = axes_count;
    for (int i = 0; i < axes_count; ++i) {
      if (last_gamepad_state[joy].axes[i] != axes[i]) {
        printf("(%d %s) axis %d = %f\n", joy, name, i, axes[i]);
      }

      last_gamepad_state[joy].axes[i] = axes[i];
    }

    last_gamepad_state[joy].button_count =  button_count;
    for (int i = 0; i < button_count; ++i) {
      if (last_gamepad_state[joy].buttons[i] != buttons[i]) {
        printf("(%d %s) button %d = %d\n", joy, name, i, buttons[i]);
      }

      last_gamepad_state[joy].buttons[i] = buttons[i];
    }
  }
}
