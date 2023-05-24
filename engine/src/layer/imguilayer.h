#ifndef ENGINE_SRC_LAYER_IMGUILAYER_H_
#define ENGINE_SRC_LAYER_IMGUILAYER_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include "core.h"
#include "window.h"
#include "layer.h"
#include "event/event.h"
#include "event/mouseevent.h"
#include "event/keyevent.h"
#include "event/windowevent.h"
#include "opengl/imguirenderer.h"

namespace engine {

// update/check if any of the special keys Alt, Shift, Ctrl or Super
// have been pressed; if so this will adjust the behaviour
// of certain other keypresses
static void __update_keys_modfiers(ImGuiIO &io, GLFWwindow *window);

/*
 * taken from:
 * https://github.com/ocornut/imgui/blob/master/backends/imgui_impl_glfw.cpp
 * (24.05.2023)
 * GLFW 3.1+ attempts to "untranslate" keys,
 * which goes the opposite of what every other framework does,
 * making using lettered shortcuts difficult.
 * (It had reasons to do so: namely GLFW is/was more likely to be used for
 * WASD-type game controls rather than lettered shortcuts,
 * but IHMO the 3.1 change could have been done differently)
 * See https://github.com/glfw/glfw/issues/1502 for details.
 * Adding a workaround to undo this (so our keys are
 * translated->untranslated->translated, likely a lossy process).
 * This won't cover edge cases but this is at least going to cover common cases.
 */
static int __translate_untranslated_key(int key, int scancode);

// convert key code to correct ImGuiKey variant
static ImGuiKey __convert_key_to_imgui_key(int key_code);

class PUB_API ImGUILayer: public Layer {
 private:
  float _time;

  // set ImGui delta time and update the internal time of the layer
  void _update_delta_time() {
    float curr_time = static_cast<float>(glfwGetTime());

    ImGuiIO &io = ImGui::GetIO();
    io.DeltaTime = curr_time - _time;

    _time = curr_time;
  }

  void _update_display_size() const {
    ImVec2 curr_display_size;
    curr_display_size.x = static_cast<float>(_window_data.width);
    curr_display_size.y = static_cast<float>(_window_data.height);

    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = curr_display_size;
  }

  bool _on_mouse_pressed_event(MousePressedEvent *e);
  bool _on_mouse_released_event(MouseReleasedEvent *e);
  bool _on_mouse_moved_event(MouseMovedEvent *e);
  bool _on_mouse_scrolled_event(MouseScrolledEvent *e);

  bool _on_key_pressed_event(KeyPressedEvent *e);
  bool _on_key_released_event(KeyReleasedEvent *e);
  bool _on_key_typed_event(KeyTypedEvent *e);

  bool _on_window_resized_event(WindowResizedEvent *e);
  bool _on_window_focused_event(WindowFocusedEvent *e);

 public:
  ImGUILayer(const WindowData &window_data) :
    Layer("ImGUILayer", window_data), _time(0.0f) {}

  ~ImGUILayer() {}

  void on_push();

  void on_pop();

  void on_update();

  void on_event(Event *e);
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYER_IMGUILAYER_H_
