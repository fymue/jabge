#include "enginepch.h"
#include "imguilayer.h"

namespace engine {

static void __set_key_codes(ImGuiIO &io) {
}

void ImGUILayer::on_push() {
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGUILayer::on_pop() {
}

void ImGUILayer::on_update() {
  _update_delta_time();
  _update_display_size();

  // create a new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  // static bool t = true;
  // ImGui::ShowDemoWindow(&t);

  // render the new frame
  ImGui::Render();

  // get the newly rendered data that is supposed
  // to be displayed on the screen
  ImDrawData *draw_data = ImGui::GetDrawData();

  // pass the draw data to the OpenGL renderer
  ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

void ImGUILayer::on_event(Event *e) {
}

}  // namespace engine
