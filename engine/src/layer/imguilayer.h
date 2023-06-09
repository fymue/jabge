#ifndef ENGINE_SRC_LAYER_IMGUILAYER_H_
#define ENGINE_SRC_LAYER_IMGUILAYER_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include <imgui.h>

#include "core.h"
#include "window.h"
#include "layer.h"
#include "event/event.h"
#include "event/mouseevent.h"
#include "event/keyevent.h"
#include "event/windowevent.h"
#include "keycode.h"
#include "application.h"
#include "opengl/imguirenderer.h"

namespace engine {

class PUB_API ImGuiLayer: public Layer {
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
  ImGuiLayer(const WindowData &window_data) :
    Layer("ImGUILayer", window_data), _time(0.0f) {}

  ~ImGuiLayer() {}

  // handles stuff that needs to happen when the layer is attached
  void on_push() override;

  // handles stuff that needs to happen when the layer is detached
  void on_pop() override;

  void on_event(Event *e);

  // set up a new layer-specific frame to render
  void begin_render();

  // render the previously created layer-specific frame
  void end_render();

  void on_imgui_render() override;

  void on_update() {
    // begin_render();
    // on_imgui_render();
    // end_render();
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYER_IMGUILAYER_H_
