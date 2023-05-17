#ifndef ENGINE_SRC_LAYER_IMGUILAYER_H_
#define ENGINE_SRC_LAYER_IMGUILAYER_H_

extern "C" {
  #include <GLFW/glfw3.h>
}

#include "core.h"
#include "window.h"
#include "layer.h"
#include "event/event.h"
#include "opengl/imguirenderer.h"

namespace engine {

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
