#include "enginepch.h"
#include "imguilayer.h"

namespace engine {

#define __CNVRT(k) __convert_key_to_imgui_key(k)

static void __update_keys_modfiers(ImGuiIO &io, GLFWwindow *window) {
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

static ImGuiKey __convert_key_to_imgui_key(int key_code) {
  switch (key_code) {
        case GLFW_KEY_TAB: return ImGuiKey_Tab;
        case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
        case GLFW_KEY_UP: return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
        case GLFW_KEY_HOME: return ImGuiKey_Home;
        case GLFW_KEY_END: return ImGuiKey_End;
        case GLFW_KEY_INSERT: return ImGuiKey_Insert;
        case GLFW_KEY_DELETE: return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE: return ImGuiKey_Space;
        case GLFW_KEY_ENTER: return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
        case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
        case GLFW_KEY_COMMA: return ImGuiKey_Comma;
        case GLFW_KEY_MINUS: return ImGuiKey_Minus;
        case GLFW_KEY_PERIOD: return ImGuiKey_Period;
        case GLFW_KEY_SLASH: return ImGuiKey_Slash;
        case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
        case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
        case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
        case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
        case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
        case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
        case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
        case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
        case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
        case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
        case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
        case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
        case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
        case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
        case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
        case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
        case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
        case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
        case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
        case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
        case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
        case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
        case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
        case GLFW_KEY_MENU: return ImGuiKey_Menu;
        case GLFW_KEY_0: return ImGuiKey_0;
        case GLFW_KEY_1: return ImGuiKey_1;
        case GLFW_KEY_2: return ImGuiKey_2;
        case GLFW_KEY_3: return ImGuiKey_3;
        case GLFW_KEY_4: return ImGuiKey_4;
        case GLFW_KEY_5: return ImGuiKey_5;
        case GLFW_KEY_6: return ImGuiKey_6;
        case GLFW_KEY_7: return ImGuiKey_7;
        case GLFW_KEY_8: return ImGuiKey_8;
        case GLFW_KEY_9: return ImGuiKey_9;
        case GLFW_KEY_A: return ImGuiKey_A;
        case GLFW_KEY_B: return ImGuiKey_B;
        case GLFW_KEY_C: return ImGuiKey_C;
        case GLFW_KEY_D: return ImGuiKey_D;
        case GLFW_KEY_E: return ImGuiKey_E;
        case GLFW_KEY_F: return ImGuiKey_F;
        case GLFW_KEY_G: return ImGuiKey_G;
        case GLFW_KEY_H: return ImGuiKey_H;
        case GLFW_KEY_I: return ImGuiKey_I;
        case GLFW_KEY_J: return ImGuiKey_J;
        case GLFW_KEY_K: return ImGuiKey_K;
        case GLFW_KEY_L: return ImGuiKey_L;
        case GLFW_KEY_M: return ImGuiKey_M;
        case GLFW_KEY_N: return ImGuiKey_N;
        case GLFW_KEY_O: return ImGuiKey_O;
        case GLFW_KEY_P: return ImGuiKey_P;
        case GLFW_KEY_Q: return ImGuiKey_Q;
        case GLFW_KEY_R: return ImGuiKey_R;
        case GLFW_KEY_S: return ImGuiKey_S;
        case GLFW_KEY_T: return ImGuiKey_T;
        case GLFW_KEY_U: return ImGuiKey_U;
        case GLFW_KEY_V: return ImGuiKey_V;
        case GLFW_KEY_W: return ImGuiKey_W;
        case GLFW_KEY_X: return ImGuiKey_X;
        case GLFW_KEY_Y: return ImGuiKey_Y;
        case GLFW_KEY_Z: return ImGuiKey_Z;
        case GLFW_KEY_F1: return ImGuiKey_F1;
        case GLFW_KEY_F2: return ImGuiKey_F2;
        case GLFW_KEY_F3: return ImGuiKey_F3;
        case GLFW_KEY_F4: return ImGuiKey_F4;
        case GLFW_KEY_F5: return ImGuiKey_F5;
        case GLFW_KEY_F6: return ImGuiKey_F6;
        case GLFW_KEY_F7: return ImGuiKey_F7;
        case GLFW_KEY_F8: return ImGuiKey_F8;
        case GLFW_KEY_F9: return ImGuiKey_F9;
        case GLFW_KEY_F10: return ImGuiKey_F10;
        case GLFW_KEY_F11: return ImGuiKey_F11;
        case GLFW_KEY_F12: return ImGuiKey_F12;
        default: return ImGuiKey_None;
    }
}

// pass pressed mouse button to ImGui
// (event not handled since this just records the press in ImGui)
bool ImGUILayer::_on_mouse_pressed_event(MousePressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // add code for pressed mouse button
  io.AddMouseButtonEvent(e->get_button_code(), true);

  return false;
}

// pass released mouse button to ImGui
// (event not handled since this just records the release in ImGui)
bool ImGUILayer::_on_mouse_released_event(MouseReleasedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // add code for released mouse button
  io.AddMouseButtonEvent(e->get_button_code(), false);

  return false;
}

// pass new mouse position to ImGui
// (event not handled since this just records the move in ImGui)
bool ImGUILayer::_on_mouse_moved_event(MouseMovedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();
  float new_x_pos = static_cast<float>(e->get_x_pos());
  float new_y_pos = static_cast<float>(e->get_y_pos());
  io.AddMousePosEvent(new_x_pos, new_y_pos);

  return false;
}

// pass new mouse scroll position (vertical AND horizontal) to ImGui
// (event not handled since this just records the scroll in ImGui)
bool ImGUILayer::_on_mouse_scrolled_event(MouseScrolledEvent *e) {
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
bool ImGUILayer::_on_key_pressed_event(KeyPressedEvent *e) {
  ImGuiIO &io = ImGui::GetIO();

  // check if any key modifiers have been pressed
  __update_keys_modfiers(io, _window_data.window);

  // translate key code (maybe temporary, see function description)
  int key_code = __translate_untranslated_key(e->get_key_code(),
                                              e->get_scan_code());

  // convert keycode to correct ImGuiKey variant
  ImGuiKey imgui_key = __convert_key_to_imgui_key(key_code);

  // add pressed key to ImGui
  io.AddKeyEvent(imgui_key, true);

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

  // check if any key modifiers have been pressed
  __update_keys_modfiers(io, _window_data.window);

  // translate key code (maybe temporary, see function description)
  int key_code = __translate_untranslated_key(e->get_key_code(),
                                              e->get_scan_code());

  // convert keycode to correct ImGuiKey variant
  ImGuiKey imgui_key = __convert_key_to_imgui_key(key_code);

  // add released key to ImGui
  io.AddKeyEvent(imgui_key, false);

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
  io.AddFocusEvent(e->get_focus() != 0);

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
