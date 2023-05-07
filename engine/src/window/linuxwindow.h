#ifndef ENGINE_SRC_WINDOW_LINUXWINDOW_H_
#define ENGINE_SRC_WINDOW_LINUXWINDOW_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include "window.h"
#include "log.h"

namespace engine {

class LinuxWindow: public Window {
 private:
  GLFWwindow *_window;
  WindowData _data;

  void init(const WindowProperties &props);

 public:
  LinuxWindow(const WindowProperties &props);

  virtual ~LinuxWindow();

  void on_update() override;

  inline int get_width() const override {
    return _data.width;
  }

  inline int get_height() const override {
    return _data.height;
  }

  inline std::string get_name() const {
    return _data.name;
  }

  inline void set_event_callback(const CallBackFunction &callback_fn) override {
    _data.callback_fn = callback_fn;
  }

  bool is_vsync() const override;
  void set_vsync(bool on) override;

  friend std::ostream &operator<<(std::ostream &steam,
                                  const LinuxWindow &window);
};

}  // namespace engine

#endif  // ENGINE_SRC_WINDOW_LINUXWINDOW_H_
