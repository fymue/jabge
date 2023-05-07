#include "enginepch.h"
#include "linuxwindow.h"

namespace engine {

static bool is_glfw_initialized = false;

Window *Window::create(const WindowProperties &props) {
  return new LinuxWindow(props);
}

void LinuxWindow::init(const WindowProperties &props) {
  _data.width = props.width;
  _data.height = props.height;
  _data.name = props.name;

  if (!is_glfw_initialized) {
    int success = glfwInit();

    if (success) {
        is_glfw_initialized = true;
        _window = glfwCreateWindow(_data.width, _data.height,
                                   _data.name.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, &_data);
        set_vsync(true);
    } else {
      ENGINE_LOG_ERROR("Window couldn't be initialized!");
      std::exit(1);
    }
  }
}

LinuxWindow::LinuxWindow(const WindowProperties &props) :
  _window(nullptr) {
  init(props);
}

LinuxWindow::~LinuxWindow() {
  glfwDestroyWindow(_window);
}

void LinuxWindow::on_update() {
  glfwPollEvents();
  glfwSwapBuffers(_window);
}

void LinuxWindow::set_vsync(bool on) {
  _data.vsync = on;

  if (on) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
}

bool LinuxWindow::is_vsync() const {
  return _data.vsync;
}

std::ostream &operator<<(std::ostream &stream, const LinuxWindow &window) {
  stream << "LinuxWindow (" << window._data.name << "): "
         << window._data.width << " x " << window._data.height;
  return stream;
}

}  // namespace engine
