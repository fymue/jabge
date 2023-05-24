#include "enginepch.h"
#include "imguilayer.h"

namespace engine {

static void __set_key_codes(ImGuiIO &io) {
}

// update/check if any of the special keys Alt, Shift, Ctrl or Super
// have been pressed; if so this will adjust the behaviour of certain
// other keypresses
// static void __check_special_keys(ImGuiIO &io) {
//   io.KeySuper = io.KeysDown[LEFT_SUPER] || io.KeysDown[RIGHT_SUPER];
//   io.KeyAlt = io.KeysDown[ALT];
//   io.KeyCtrl = io.KeysDown[CTRL];
//   io.KeyShift = io.KeyShift[SHIFT];
// }

// pass pressed mouse button to ImGui
// (event not handled since this just records the press in ImGui)
bool ImGUILayer::_on_mouse_pressed_event(MousePressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e->get_button_code()] = true;

  return false;
}

// pass released mouse button to ImGui
// (event not handled since this just records the release in ImGui)
bool ImGUILayer::_on_mouse_released_event(MouseReleasedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e->get_button_code()] = false;

  return false;
}

// pass new mouse position to ImGui
// (event not handled since this just records the move in ImGui)
bool ImGUILayer::_on_mouse_moved_event(MouseMovedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  ImVec2 new_mouse_position(e->get_x_pos(), e->get_y_pos());
  io.MousePos = new_mouse_position;

  return false;
}

// pass new mouse scroll position (vertical AND horizontal) to ImGui
// (event not handled since this just records the scroll in ImGui)
bool ImGUILayer::_on_mouse_scrolled_event(MouseScrolledEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // set vertical scroll offset
  io.MouseWheel += e->get_x_offset();

  // set horizontal scroll offset
  io.MouseWheelH += e->get_y_offset();

  return false;
}

// pass pressed key to ImGui
// (event not handled since this just records the key press in ImGui)
bool ImGUILayer::_on_key_pressed_event(KeyPressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e->get_key_code()] = true;

  // __check_special_keys(io);

  return false;
}

// pass typed key to ImGui
// (event not handled since this just records the key type in ImGui)
bool ImGUILayer::_on_key_typed_event(KeyTypedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  unsigned int key_code = static_cast<unsigned int>(e->get_key_code());
  io.AddInputCharacter(key_code);

  return false;
}

// pass released key to ImGui
// (event not handled since this just records the key release in ImGui)
bool ImGUILayer::_on_key_released_event(KeyReleasedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e->get_key_code()] = false;

  return false;
}

bool ImGUILayer::_on_window_resized_event(WindowResizedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  ImVec2 new_display_size(e->get_width(), e->get_height());
  io.DisplaySize = new_display_size;

  return true;
}

bool ImGUILayer::_on_window_focused_event(WindowFocusedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  return false;
}

void ImGUILayer::on_push() {
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  ImGui_ImplOpenGL3_Init(ENGINE_GLSL_VERSION);
}

void ImGUILayer::on_pop() {
}

void ImGUILayer::on_update() {
  _update_delta_time();
  _update_display_size();

  // create a new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool t = true;
  ImGui::ShowDemoWindow(&t);

  // render the new frame
  ImGui::Render();

  // get the newly rendered data that is supposed
  // to be displayed on the screen
  ImDrawData *draw_data = ImGui::GetDrawData();

  // pass the draw data to the OpenGL renderer
  ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

void ImGUILayer::on_event(Event *e) {
  // dispatch incoming event and call its according event function
  EventDispatcher dispatcher(e);

  dispatcher.dispatch<MousePressedEvent>(
    BIND_EVENT(ImGUILayer::_on_mouse_pressed_event));
  dispatcher.dispatch<MouseReleasedEvent>(BIND_EVENT(
    ImGUILayer::_on_mouse_released_event));
  dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT(
    ImGUILayer::_on_mouse_scrolled_event));
  dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT(
    ImGUILayer::_on_mouse_moved_event));

  dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT(
    ImGUILayer::_on_key_pressed_event));
  dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT(
    ImGUILayer::_on_key_released_event));
  dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT(
    ImGUILayer::_on_key_typed_event));

  dispatcher.dispatch<WindowResizedEvent>(BIND_EVENT(
    ImGUILayer::_on_window_resized_event));
}

}  // namespace engine
