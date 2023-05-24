#ifndef ENGINE_SRC_WINDOW_H_
#define ENGINE_SRC_WINDOW_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include "core.h"
#include "event/event.h"

namespace engine {

using CallBackFunction = std::function<void(Event*)>;

// define basic window properties
class PUB_API WindowProperties {
 public:
  int width, height;
  std::string name;

  WindowProperties() :
    width(1280), height(720), name("Window") {}

  WindowProperties(int width, int height,
                   const char *name) :
    width(width), height(height), name(name) {}
};

/*
 * every implementation of the base "Window" class
 * contains a "WindowData" object that is passed
 * to the GLFWwindow object as a "WindowUserPointer";
 * this object is mainly used to call the callback function
 * of the "Window" object, which is bound to the "on_event"
 * function in the main "Application" class, which dispatches
 * any event and calls it's "on_event" function
 */
struct PUB_API WindowData {
  int width, height;
  std::string name;
  bool vsync;

  /*
   * TODO(fymue): window ptr is currently used to e.g. be able to
   * call the glfwGetKey function in imguilayer.cpp;
   * direct access to window trough this ptr is not really intended
   * for a layer though; so maybe check if this can be substituted
   * for specific access to window resources (in this case to the key map)
   */
  GLFWwindow *window;  // TODO(fymue): mayb
  CallBackFunction callback_fn;
};

// Window interface (is implemented separately for every platform)
class PUB_API Window {
 protected:
  WindowData _data;

  Window() {}

 public:
  virtual ~Window() {}

  virtual int get_width() const = 0;
  virtual int get_height() const = 0;
  virtual bool is_vsync() const = 0;
  virtual void set_vsync(bool on) = 0;

  virtual void on_update() = 0;
  virtual void set_event_callback(const CallBackFunction &callback_fn) = 0;

  inline const WindowData &get_window_data() const {
    return _data;
  }

  static Window *create(const WindowProperties &props);
};

}  // namespace engine

#endif  // ENGINE_SRC_WINDOW_H_
