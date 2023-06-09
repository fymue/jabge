#include "enginepch.h"
#include "imguilayer.h"

namespace engine {

#define __CNVRT(k) __convert_key_to_imgui_key(k)

// update/check if any of the special keys Alt, Shift, Ctrl or Super
// have been pressed; if so this will adjust the behaviour
// of certain other keypresses
static void __update_key_modifiers(ImGuiIO &io, GLFWwindow *window) {
  io.AddKeyEvent(ImGuiMod_Ctrl,
                 (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)  == GLFW_PRESS) ||
                 (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Shift,
                 (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS) ||
                 (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Alt,
                 (glfwGetKey(window, GLFW_KEY_LEFT_ALT)  == GLFW_PRESS) ||
                 (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Super,
                 (glfwGetKey(window, GLFW_KEY_LEFT_SUPER)  == GLFW_PRESS) ||
                 (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS));
}

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
static int __translate_untranslated_key(int key, int scancode) {
#if GLFW_HAS_GETKEYNAME && !defined(__EMSCRIPTEN__)
  if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_EQUAL) {
    return key;
  }
  GLFWerrorfun prev_error_callback = glfwSetErrorCallback(nullptr);
  const char* key_name = glfwGetKeyName(key, scancode);
  glfwSetErrorCallback(prev_error_callback);
#if GLFW_HAS_GETERROR && !defined(__EMSCRIPTEN__)  // Eat errors (see #5908)
  (void)glfwGetError(nullptr);
#endif
  if (key_name && key_name[0] != 0 && key_name[1] == 0) {
    const char char_names[] = "`-=[]\\,;\'./";
    const int char_keys[] = {GLFW_KEY_GRAVE_ACCENT, GLFW_KEY_MINUS,
                             GLFW_KEY_EQUAL, GLFW_KEY_LEFT_BRACKET,
                             GLFW_KEY_RIGHT_BRACKET, GLFW_KEY_BACKSLASH,
                             GLFW_KEY_COMMA, GLFW_KEY_SEMICOLON,
                             GLFW_KEY_APOSTROPHE, GLFW_KEY_PERIOD,
                             GLFW_KEY_SLASH, 0};
    ENGINE_ASSERT(IM_ARRAYSIZE(char_names) == IM_ARRAYSIZE(char_keys));
    if (key_name[0] >= '0' && key_name[0] <= '9') {
      key = GLFW_KEY_0 + (key_name[0] - '0');
    } else if (key_name[0] >= 'A' && key_name[0] <= 'Z') {
      key = GLFW_KEY_A + (key_name[0] - 'A');
    } else if (key_name[0] >= 'a' && key_name[0] <= 'z') {
      key = GLFW_KEY_A + (key_name[0] - 'a');
    } else if (const char* p = strchr(char_names, key_name[0])) {
      key = char_keys[p - char_names]; }
  }
#else
    IM_UNUSED(scancode);
#endif
  return key;
}

// pass pressed mouse button to ImGui
// (event not handled since this just records the press in ImGui)
bool ImGuiLayer::_on_mouse_pressed_event(MousePressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // add code for pressed mouse button
  io.AddMouseButtonEvent(e->get_button_code(), true);

  return false;
}

// pass released mouse button to ImGui
// (event not handled since this just records the release in ImGui)
bool ImGuiLayer::_on_mouse_released_event(MouseReleasedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // add code for released mouse button
  io.AddMouseButtonEvent(e->get_button_code(), false);

  return false;
}

// pass new mouse position to ImGui
// (event not handled since this just records the move in ImGui)
bool ImGuiLayer::_on_mouse_moved_event(MouseMovedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  float new_x_pos = static_cast<float>(e->get_x_pos());
  float new_y_pos = static_cast<float>(e->get_y_pos());
  io.AddMousePosEvent(new_x_pos, new_y_pos);

  return false;
}

// pass new mouse scroll position (vertical AND horizontal) to ImGui
// (event not handled since this just records the scroll in ImGui)
bool ImGuiLayer::_on_mouse_scrolled_event(MouseScrolledEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // set vertical scroll offset
  float new_x_offset = static_cast<float>(e->get_x_offset());

  // set horizontal scroll offset
  float new_y_offset = static_cast<float>(e->get_y_offset());

  io.AddMouseWheelEvent(new_x_offset, new_y_offset);

  return false;
}

// pass pressed key to ImGui
// (event not handled since this just records the key press in ImGui)
bool ImGuiLayer::_on_key_pressed_event(KeyPressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // check if any key modifiers have been pressed
  __update_key_modifiers(io, _window_data.window);

  // translate key code (maybe temporary, see function description)
  int key_code = __translate_untranslated_key(e->get_key_code(),
                                              e->get_scan_code());

  // convert keycode to correct ImGuiKey variant
  ImGuiKey imgui_key = convert_to_imgui_key(convert_to_engine_key(key_code));

  // add pressed key to ImGui
  io.AddKeyEvent(imgui_key, true);

  return false;
}

// pass typed key to ImGui
// (event not handled since this just records the key type in ImGui)
bool ImGuiLayer::_on_key_typed_event(KeyTypedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  unsigned int key_code = static_cast<unsigned int>(e->get_key_code());
  io.AddInputCharacter(key_code);

  return false;
}

// pass released key to ImGui
// (event not handled since this just records the key release in ImGui)
bool ImGuiLayer::_on_key_released_event(KeyReleasedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // check if any key modifiers have been pressed
  __update_key_modifiers(io, _window_data.window);

  // translate key code (maybe temporary, see function description)
  int key_code = __translate_untranslated_key(e->get_key_code(),
                                              e->get_scan_code());

  // convert keycode to correct ImGuiKey variant
  ImGuiKey imgui_key = convert_to_imgui_key(convert_to_engine_key(key_code));

  // add released key to ImGui
  io.AddKeyEvent(imgui_key, false);

  return false;
}

bool ImGuiLayer::_on_window_resized_event(WindowResizedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  ImVec2 new_display_size(e->get_width(), e->get_height());
  io.DisplaySize = new_display_size;

  return true;
}

bool ImGuiLayer::_on_window_focused_event(WindowFocusedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  io.AddFocusEvent(e->get_focus() != 0);

  return false;
}

void ImGuiLayer::on_push() {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  ImGui_ImplOpenGL3_Init(ENGINE_GLSL_VERSION);
  // init GLFW with proper mapping from ImGui callbacks to GLFW callbacks
  ImGui_ImplGlfw_InitForOpenGL(_window_data.window, true);
}

void ImGuiLayer::on_pop() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::begin_render() {
  // create a new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::end_render() {
  // render the new frame
  _update_delta_time();
  _update_display_size();

  ImGui::Render();

  // get the newly rendered data that is supposed
  // to be displayed on the screen
  ImDrawData *draw_data = ImGui::GetDrawData();

  // pass the draw data to the OpenGL renderer
  ImGui_ImplOpenGL3_RenderDrawData(draw_data);

  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *window = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(window);
  }
}

void ImGuiLayer::on_imgui_render() {
  static bool t = true;
  ImGui::ShowDemoWindow(&t);
}

void ImGuiLayer::on_event(Event *e) {
  // dispatch incoming event and call its according event function
  EventDispatcher dispatcher(e);

  dispatcher.dispatch<MousePressedEvent>(
    BIND_EVENT(ImGuiLayer::_on_mouse_pressed_event));
  dispatcher.dispatch<MouseReleasedEvent>(BIND_EVENT(
    ImGuiLayer::_on_mouse_released_event));
  dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT(
    ImGuiLayer::_on_mouse_scrolled_event));
  dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT(
    ImGuiLayer::_on_mouse_moved_event));

  dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT(
    ImGuiLayer::_on_key_pressed_event));
  dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT(
    ImGuiLayer::_on_key_released_event));
  dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT(
    ImGuiLayer::_on_key_typed_event));

  dispatcher.dispatch<WindowResizedEvent>(BIND_EVENT(
    ImGuiLayer::_on_window_resized_event));
}

}  // namespace engine
