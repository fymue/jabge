#include "enginepch.h"
#include "linuxwindowinput.h"

namespace engine {

bool LinuxWindowInput::_is_key_pressed(EngineKey key) const {
  GLFWwindow *window =
    static_cast<GLFWwindow*>(Application::get().get_window().get_window_impl());
  int GLFW_key = convert_to_glfw_key(key);
  return glfwGetKey(window, GLFW_key)  == GLFW_PRESS;
}

bool LinuxWindowInput::_is_mouse_button_pressed(int button) const {
  GLFWwindow *window =
    static_cast<GLFWwindow*>(Application::get().get_window().get_window_impl());
  return glfwGetMouseButton(window, button)  == GLFW_PRESS;
}

Vec2<double> LinuxWindowInput::_get_mouse_pos() const {
  return Application::get().get_window_data().mouse_pos;
}

}  // namespace engine
