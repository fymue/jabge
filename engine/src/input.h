#ifndef ENGINE_SRC_INPUT_H_
#define ENGINE_SRC_INPUT_H_

#include "keycode.h"
#include "types.h"

namespace engine {

class Input {
 protected:
  static Input *_input;  // input class singleton

  virtual bool _is_key_pressed(EngineKey key) const = 0;
  virtual bool _is_mouse_button_pressed(int button) const = 0;

  virtual Vec2<double> _get_mouse_pos() const = 0;

 public:
  virtual ~Input() {}

  static inline bool is_key_pressed(EngineKey key) {
    ENGINE_ASSERT(_input, "Input is not set!");
    return _input->_is_key_pressed(key);
  }

  static inline bool is_mouse_button_pressed(int button) {
    ENGINE_ASSERT(_input, "Input is not set!");
    return _input->_is_mouse_button_pressed(button);
  }

  static inline Vec2<double> get_mouse_pos() {
    ENGINE_ASSERT(_input, "Input is not set!");
    return _input->get_mouse_pos();
  }

  static const Input &get() {
    ENGINE_ASSERT(_input, "Input is not set!");
    return *_input;
  }

  static void switch_input(Input *input) {
    _input = input;
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_INPUT_H_
