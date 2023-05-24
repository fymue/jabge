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
  // TODO(fymue): fill this
};

// contains KeyMaps for engine and GLFW keycodes to ImGuiKey analogs
class EngineKeyMap {
 private:
  void _fill_imgui_keymap();
  void _fill_glfw_keymap();

  // map engine key to imgui key
  ImGuiKey _imgui_keys[ENGINE_KEY_MAP_MAX];

  // map GLFW key to engine key
  EngineKey _glfw_keys[ENGINE_KEY_MAP_MAX];

 public:
  EngineKeyMap() {
    _fill_imgui_keymap();
    _fill_glfw_keymap();
  }

  // get ImGuiKey analog of EngineKey
  inline ImGuiKey get_imgui_key(EngineKey key_code);

  // get EngineKey analog of GLFW key code
  inline EngineKey get_engine_key(int key_code);
};

// convert EngineKey to ImGuiKey analog
inline ImGuiKey convert_to_imgui_key(EngineKey key_code);

// convert GLFW key code to ImGuiKey analog
inline ImGuiKey convert_to_imgui_key(int key_code);

// convert GLFW key code to EngineKey analog
inline EngineKey convert_to_engine_key(int key_code);

}  // namespace engine

#endif  // ENGINE_SRC_KEYCODE_H_
