#ifndef ENGINE_SRC_WINDOW_LINUXWINDOWINPUT_H_
#define ENGINE_SRC_WINDOW_LINUXWINDOWINPUT_H_

#include <GLFW/glfw3.h>

#include "input.h"
#include "keycode.h"
#include "application.h"
#include "types.h"

namespace engine {

class LinuxWindowInput : public Input {
 protected:
  bool _is_key_pressed(EngineKey key) const override;
  bool _is_mouse_button_pressed(int button) const override;

  Vec2<double> _get_mouse_pos() const override;
};

}  // namespace engine

#endif  // ENGINE_SRC_WINDOW_LINUXWINDOWINPUT_H_
