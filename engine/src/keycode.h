#ifndef ENGINE_SRC_KEYCODE_H_
#define ENGINE_SRC_KEYCODE_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include <imgui.h>

namespace engine {

// max size of arrays for key mapping between ImGui, GLFW and engine
#define ENGINE_KEY_MAP_MAX 1024

enum EngineKey {
  // default key (no actual key binding)
  KEY_NONE,

  // number keys
  KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,

  // letter keys
  KEY_A = 65, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
  KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
  KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

  // function keys
  KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9,
  KEY_F10, KEY_F11, KEY_F12,

  // arrow keys
  KEY_ARROW_LEFT, KEY_ARROW_RIGHT, KEY_ARROW_UP, KEY_ARROW_DOWN,

  // functional keys
  KEY_TAB, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME, KEY_END, KEY_INSERT,
  KEY_DELETE, KEY_BACKSPACE, KEY_SPACE, KEY_ENTER, KEY_ESCAPE, KEY_APOSTROPHE,
  KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_SEMICOLON, KEY_EQUAL,
  KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE_ACCENT,
  KEY_CAPS_LOCK, KEY_SCROLL_LOCK, KEY_NUM_LOCK, KEY_PRINT_SCREEN, KEY_PAUSE,

  // keypad keys
  KEY_KEYPAD_0, KEY_KEYPAD_1, KEY_KEYPAD_2, KEY_KEYPAD_3, KEY_KEYPAD_4,
  KEY_KEYPAD_5, KEY_KEYPAD_6, KEY_KEYPAD_7, KEY_KEYPAD_8, KEY_KEYPAD_9,
  KEY_KEYPAD_DECIMAL, KEY_KEYPAD_DIVIDE, KEY_KEYPAD_MULTIPLY,
  KEY_KEYPAD_SUBTRACT, KEY_KEYPAD_ADD, KEY_KEYPAD_ENTER, KEY_KEYPAD_EQUAL,

  // modifier/special keys
  KEY_LEFT_SHIFT, KEY_LEFT_CONTROL, KEY_LEFT_ALT, KEY_LEFT_SUPER,
  KEY_RIGHT_SHIFT, KEY_RIGHT_CONTROL, KEY_RIGHT_ALT, KEY_RIGHT_SUPER,
  KEY_MENU,
};

enum MouseButton {
  MOUSE_BUTTON_1,
  MOUSE_BUTTON_2,
  MOUSE_BUTTON_3,
  MOUSE_BUTTON_4,
  MOUSE_BUTTON_5,
  MOUSE_BUTTON_6,
  MOUSE_BUTTON_7,
  MOUSE_BUTTON_8,
  MOUSE_BUTTON_LAST   = MOUSE_BUTTON_8,
  MOUSE_BUTTON_LEFT   = MOUSE_BUTTON_1,
  MOUSE_BUTTON_RIGHT  = MOUSE_BUTTON_2,
  MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
};

// contains KeyMaps for engine and GLFW keycodes to ImGuiKey analogs
class EngineKeyMap {
 private:
  // map engine key to ImGui key
  ImGuiKey *_engine_to_imgui_keys;

  // map engine key to GLFW key
  int *_engine_to_glfw_keys;

  // map GLFW key to engine key
  EngineKey *_glfw_to_engine_keys;

  // map ImGui key to engine key
  EngineKey *_imgui_to_engine_keys;

  void _fill_engine_to_imgui_keymap();
  void _fill_engine_to_glfw_keymap();
  void _fill_imgui_to_engine_keymap();
  void _fill_glfw_to_engine_keymap();

 public:
  EngineKeyMap();
  ~EngineKeyMap();

  // get ImGuiKey analog of EngineKey
  inline ImGuiKey get_imgui_key(EngineKey key_code) {
    return _engine_to_imgui_keys[key_code];
  }

  // get GLFW analog of EngineKey
  inline int get_glfw_key(EngineKey key_code) {
    return _engine_to_glfw_keys[key_code];
  }

  // get EngineKey analog of GLFW key code
  inline EngineKey get_engine_key(int key_code) {
    return _glfw_to_engine_keys[key_code];
  }

  // get EngineKey analog of ImGuiKey
  inline EngineKey get_engine_key(ImGuiKey key_code) {
    return _imgui_to_engine_keys[key_code];
  }
};

// convert GLFW key code to EngineKey analog
EngineKey convert_to_engine_key(int key_code);

// convert ImGuiKey to EngineKey analog
EngineKey convert_to_engine_key(ImGuiKey key_code);

// convert EngineKey to ImGuiKey analog
ImGuiKey convert_to_imgui_key(EngineKey key_code);

// convert EngineKey to GLFW analog
int convert_to_glfw_key(EngineKey key_code);

}  // namespace engine

#endif  // ENGINE_SRC_KEYCODE_H_
