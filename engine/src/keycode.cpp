#include "enginepch.h"
#include "keycode.h"

namespace engine {

void EngineKeyMap::_fill_imgui_keymap() {
  _imgui_keys[KEY_TAB] = ImGuiKey_Tab;
  _imgui_keys[KEY_ARROW_LEFT] = ImGuiKey_LeftArrow;
  _imgui_keys[KEY_ARROW_RIGHT] = ImGuiKey_RightArrow;
  _imgui_keys[KEY_ARROW_UP] = ImGuiKey_UpArrow;
  _imgui_keys[KEY_ARROW_DOWN] = ImGuiKey_DownArrow;
  _imgui_keys[KEY_PAGE_UP] = ImGuiKey_PageUp;
  _imgui_keys[KEY_PAGE_DOWN] = ImGuiKey_PageDown;
  _imgui_keys[KEY_HOME] = ImGuiKey_Home;
  _imgui_keys[KEY_END] = ImGuiKey_End;
  _imgui_keys[KEY_INSERT] = ImGuiKey_Insert;
  _imgui_keys[KEY_DELETE] = ImGuiKey_Delete;
  _imgui_keys[KEY_BACKSPACE] = ImGuiKey_Backspace;
  _imgui_keys[KEY_SPACE] = ImGuiKey_Space;
  _imgui_keys[KEY_ENTER] = ImGuiKey_Enter;
  _imgui_keys[KEY_ESCAPE] = ImGuiKey_Escape;
  _imgui_keys[KEY_APOSTROPHE] = ImGuiKey_Apostrophe;
  _imgui_keys[KEY_COMMA] = ImGuiKey_Comma;
  _imgui_keys[KEY_MINUS] = ImGuiKey_Minus;
  _imgui_keys[KEY_PERIOD] = ImGuiKey_Period;
  _imgui_keys[KEY_SLASH] = ImGuiKey_Slash;
  _imgui_keys[KEY_SEMICOLON] = ImGuiKey_Semicolon;
  _imgui_keys[KEY_EQUAL] = ImGuiKey_Equal;
  _imgui_keys[KEY_LEFT_BRACKET] = ImGuiKey_LeftBracket;
  _imgui_keys[KEY_BACKSLASH] = ImGuiKey_Backslash;
  _imgui_keys[KEY_RIGHT_BRACKET] = ImGuiKey_RightBracket;
  _imgui_keys[KEY_GRAVE_ACCENT] = ImGuiKey_GraveAccent;
  _imgui_keys[KEY_CAPS_LOCK] = ImGuiKey_CapsLock;
  _imgui_keys[KEY_SCROLL_LOCK] = ImGuiKey_ScrollLock;
  _imgui_keys[KEY_NUM_LOCK] = ImGuiKey_NumLock;
  _imgui_keys[KEY_PRINT_SCREEN] = ImGuiKey_PrintScreen;
  _imgui_keys[KEY_PAUSE] = ImGuiKey_Pause;
  _imgui_keys[KEY_KEYPAD_0] = ImGuiKey_Keypad0;
  _imgui_keys[KEY_KEYPAD_1] = ImGuiKey_Keypad1;
  _imgui_keys[KEY_KEYPAD_2] = ImGuiKey_Keypad2;
  _imgui_keys[KEY_KEYPAD_3] = ImGuiKey_Keypad3;
  _imgui_keys[KEY_KEYPAD_4] = ImGuiKey_Keypad4;
  _imgui_keys[KEY_KEYPAD_5] = ImGuiKey_Keypad5;
  _imgui_keys[KEY_KEYPAD_6] = ImGuiKey_Keypad6;
  _imgui_keys[KEY_KEYPAD_7] = ImGuiKey_Keypad7;
  _imgui_keys[KEY_KEYPAD_8] = ImGuiKey_Keypad8;
  _imgui_keys[KEY_KEYPAD_9] = ImGuiKey_Keypad9;
  _imgui_keys[KEY_KEYPAD_DECIMAL] = ImGuiKey_KeypadDecimal;
  _imgui_keys[KEY_KEYPAD_DIVIDE] = ImGuiKey_KeypadDivide;
  _imgui_keys[KEY_KEYPAD_MULTIPLY] = ImGuiKey_KeypadMultiply;
  _imgui_keys[KEY_KEYPAD_SUBTRACT] = ImGuiKey_KeypadSubtract;
  _imgui_keys[KEY_KEYPAD_ADD] = ImGuiKey_KeypadAdd;
  _imgui_keys[KEY_KEYPAD_ENTER] = ImGuiKey_KeypadEnter;
  _imgui_keys[KEY_KEYPAD_EQUAL] = ImGuiKey_KeypadEqual;
  _imgui_keys[KEY_LEFT_SHIFT] = ImGuiKey_LeftShift;
  _imgui_keys[KEY_LEFT_CONTROL] = ImGuiKey_LeftCtrl;
  _imgui_keys[KEY_LEFT_ALT] = ImGuiKey_LeftAlt;
  _imgui_keys[KEY_LEFT_SUPER] = ImGuiKey_LeftSuper;
  _imgui_keys[KEY_RIGHT_SHIFT] = ImGuiKey_RightShift;
  _imgui_keys[KEY_RIGHT_CONTROL] = ImGuiKey_RightCtrl;
  _imgui_keys[KEY_RIGHT_ALT] = ImGuiKey_RightAlt;
  _imgui_keys[KEY_RIGHT_SUPER] = ImGuiKey_RightSuper;
  _imgui_keys[KEY_MENU] = ImGuiKey_Menu;
  _imgui_keys[KEY_0] = ImGuiKey_0;
  _imgui_keys[KEY_1] = ImGuiKey_1;
  _imgui_keys[KEY_2] = ImGuiKey_2;
  _imgui_keys[KEY_3] = ImGuiKey_3;
  _imgui_keys[KEY_4] = ImGuiKey_4;
  _imgui_keys[KEY_5] = ImGuiKey_5;
  _imgui_keys[KEY_6] = ImGuiKey_6;
  _imgui_keys[KEY_7] = ImGuiKey_7;
  _imgui_keys[KEY_8] = ImGuiKey_8;
  _imgui_keys[KEY_9] = ImGuiKey_9;
  _imgui_keys[KEY_A] = ImGuiKey_A;
  _imgui_keys[KEY_B] = ImGuiKey_B;
  _imgui_keys[KEY_C] = ImGuiKey_C;
  _imgui_keys[KEY_D] = ImGuiKey_D;
  _imgui_keys[KEY_E] = ImGuiKey_E;
  _imgui_keys[KEY_F] = ImGuiKey_F;
  _imgui_keys[KEY_G] = ImGuiKey_G;
  _imgui_keys[KEY_H] = ImGuiKey_H;
  _imgui_keys[KEY_I] = ImGuiKey_I;
  _imgui_keys[KEY_J] = ImGuiKey_J;
  _imgui_keys[KEY_K] = ImGuiKey_K;
  _imgui_keys[KEY_L] = ImGuiKey_L;
  _imgui_keys[KEY_M] = ImGuiKey_M;
  _imgui_keys[KEY_N] = ImGuiKey_N;
  _imgui_keys[KEY_O] = ImGuiKey_O;
  _imgui_keys[KEY_P] = ImGuiKey_P;
  _imgui_keys[KEY_Q] = ImGuiKey_Q;
  _imgui_keys[KEY_R] = ImGuiKey_R;
  _imgui_keys[KEY_S] = ImGuiKey_S;
  _imgui_keys[KEY_T] = ImGuiKey_T;
  _imgui_keys[KEY_U] = ImGuiKey_U;
  _imgui_keys[KEY_V] = ImGuiKey_V;
  _imgui_keys[KEY_W] = ImGuiKey_W;
  _imgui_keys[KEY_X] = ImGuiKey_X;
  _imgui_keys[KEY_Y] = ImGuiKey_Y;
  _imgui_keys[KEY_Z] = ImGuiKey_Z;
  _imgui_keys[KEY_F1] = ImGuiKey_F1;
  _imgui_keys[KEY_F2] = ImGuiKey_F2;
  _imgui_keys[KEY_F3] = ImGuiKey_F3;
  _imgui_keys[KEY_F4] = ImGuiKey_F4;
  _imgui_keys[KEY_F5] = ImGuiKey_F5;
  _imgui_keys[KEY_F6] = ImGuiKey_F6;
  _imgui_keys[KEY_F7] = ImGuiKey_F7;
  _imgui_keys[KEY_F8] = ImGuiKey_F8;
  _imgui_keys[KEY_F9] = ImGuiKey_F9;
  _imgui_keys[KEY_F10] = ImGuiKey_F10;
  _imgui_keys[KEY_F11] = ImGuiKey_F11;
  _imgui_keys[KEY_F12] = ImGuiKey_F12;
  _imgui_keys[KEY_NONE] = ImGuiKey_None;
}

void EngineKeyMap::_fill_keymap() {
  _keys[GLFW_KEY_TAB] = KEY_TAB;
  _keys[GLFW_KEY_LEFT] = KEY_ARROW_LEFT;
  _keys[GLFW_KEY_RIGHT] = KEY_ARROW_RIGHT;
  _keys[GLFW_KEY_UP] = KEY_ARROW_UP;
  _keys[GLFW_KEY_DOWN] = KEY_ARROW_DOWN;
  _keys[GLFW_KEY_PAGE_UP] = KEY_PAGE_UP;
  _keys[GLFW_KEY_PAGE_DOWN] = KEY_PAGE_DOWN;
  _keys[GLFW_KEY_HOME] = KEY_HOME;
  _keys[GLFW_KEY_END] = KEY_END;
  _keys[GLFW_KEY_INSERT] = KEY_INSERT;
  _keys[GLFW_KEY_DELETE] = KEY_DELETE;
  _keys[GLFW_KEY_BACKSPACE] = KEY_BACKSPACE;
  _keys[GLFW_KEY_SPACE] = KEY_SPACE;
  _keys[GLFW_KEY_ENTER] = KEY_ENTER;
  _keys[GLFW_KEY_ESCAPE] = KEY_ESCAPE;
  _keys[GLFW_KEY_APOSTROPHE] = KEY_APOSTROPHE;
  _keys[GLFW_KEY_COMMA] = KEY_COMMA;
  _keys[GLFW_KEY_MINUS] = KEY_MINUS;
  _keys[GLFW_KEY_PERIOD] = KEY_PERIOD;
  _keys[GLFW_KEY_SLASH] = KEY_SLASH;
  _keys[GLFW_KEY_SEMICOLON] = KEY_SEMICOLON;
  _keys[GLFW_KEY_EQUAL] = KEY_EQUAL;
  _keys[GLFW_KEY_LEFT_BRACKET] = KEY_LEFT_BRACKET;
  _keys[GLFW_KEY_BACKSLASH] = KEY_BACKSLASH;
  _keys[GLFW_KEY_RIGHT_BRACKET] = KEY_RIGHT_BRACKET;
  _keys[GLFW_KEY_GRAVE_ACCENT] = KEY_GRAVE_ACCENT;
  _keys[GLFW_KEY_CAPS_LOCK] = KEY_CAPS_LOCK;
  _keys[GLFW_KEY_SCROLL_LOCK] = KEY_SCROLL_LOCK;
  _keys[GLFW_KEY_NUM_LOCK] = KEY_NUM_LOCK;
  _keys[GLFW_KEY_PRINT_SCREEN] = KEY_PRINT_SCREEN;
  _keys[GLFW_KEY_PAUSE] = KEY_PAUSE;
  _keys[GLFW_KEY_KP_0] = KEY_KEYPAD_0;
  _keys[GLFW_KEY_KP_1] = KEY_KEYPAD_1;
  _keys[GLFW_KEY_KP_2] = KEY_KEYPAD_2;
  _keys[GLFW_KEY_KP_3] = KEY_KEYPAD_3;
  _keys[GLFW_KEY_KP_4] = KEY_KEYPAD_4;
  _keys[GLFW_KEY_KP_5] = KEY_KEYPAD_5;
  _keys[GLFW_KEY_KP_6] = KEY_KEYPAD_6;
  _keys[GLFW_KEY_KP_7] = KEY_KEYPAD_7;
  _keys[GLFW_KEY_KP_8] = KEY_KEYPAD_8;
  _keys[GLFW_KEY_KP_9] = KEY_KEYPAD_9;
  _keys[GLFW_KEY_KP_DECIMAL] = KEY_KEYPAD_DECIMAL;
  _keys[GLFW_KEY_KP_DIVIDE] = KEY_KEYPAD_DIVIDE;
  _keys[GLFW_KEY_KP_MULTIPLY] = KEY_KEYPAD_MULTIPLY;
  _keys[GLFW_KEY_KP_SUBTRACT] = KEY_KEYPAD_SUBTRACT;
  _keys[GLFW_KEY_KP_ADD] = KEY_KEYPAD_ADD;
  _keys[GLFW_KEY_KP_ENTER] = KEY_KEYPAD_ENTER;
  _keys[GLFW_KEY_KP_EQUAL] = KEY_KEYPAD_EQUAL;
  _keys[GLFW_KEY_LEFT_SHIFT] = KEY_LEFT_SHIFT;
  _keys[GLFW_KEY_LEFT_CONTROL] = KEY_LEFT_CONTROL;
  _keys[GLFW_KEY_LEFT_ALT] = KEY_LEFT_ALT;
  _keys[GLFW_KEY_LEFT_SUPER] = KEY_LEFT_SUPER;
  _keys[GLFW_KEY_RIGHT_SHIFT] = KEY_RIGHT_SHIFT;
  _keys[GLFW_KEY_RIGHT_CONTROL] = KEY_RIGHT_CONTROL;
  _keys[GLFW_KEY_RIGHT_ALT] = KEY_RIGHT_ALT;
  _keys[GLFW_KEY_RIGHT_SUPER] = KEY_RIGHT_SUPER;
  _keys[GLFW_KEY_MENU] = KEY_MENU;
  _keys[GLFW_KEY_0] = KEY_0;
  _keys[GLFW_KEY_1] = KEY_1;
  _keys[GLFW_KEY_2] = KEY_2;
  _keys[GLFW_KEY_3] = KEY_3;
  _keys[GLFW_KEY_4] = KEY_4;
  _keys[GLFW_KEY_5] = KEY_5;
  _keys[GLFW_KEY_6] = KEY_6;
  _keys[GLFW_KEY_7] = KEY_7;
  _keys[GLFW_KEY_8] = KEY_8;
  _keys[GLFW_KEY_9] = KEY_9;
  _keys[GLFW_KEY_A] = KEY_A;
  _keys[GLFW_KEY_B] = KEY_B;
  _keys[GLFW_KEY_C] = KEY_C;
  _keys[GLFW_KEY_D] = KEY_D;
  _keys[GLFW_KEY_E] = KEY_E;
  _keys[GLFW_KEY_F] = KEY_F;
  _keys[GLFW_KEY_G] = KEY_G;
  _keys[GLFW_KEY_H] = KEY_H;
  _keys[GLFW_KEY_I] = KEY_I;
  _keys[GLFW_KEY_J] = KEY_J;
  _keys[GLFW_KEY_K] = KEY_K;
  _keys[GLFW_KEY_L] = KEY_L;
  _keys[GLFW_KEY_M] = KEY_M;
  _keys[GLFW_KEY_N] = KEY_N;
  _keys[GLFW_KEY_O] = KEY_O;
  _keys[GLFW_KEY_P] = KEY_P;
  _keys[GLFW_KEY_Q] = KEY_Q;
  _keys[GLFW_KEY_R] = KEY_R;
  _keys[GLFW_KEY_S] = KEY_S;
  _keys[GLFW_KEY_T] = KEY_T;
  _keys[GLFW_KEY_U] = KEY_U;
  _keys[GLFW_KEY_V] = KEY_V;
  _keys[GLFW_KEY_W] = KEY_W;
  _keys[GLFW_KEY_X] = KEY_X;
  _keys[GLFW_KEY_Y] = KEY_Y;
  _keys[GLFW_KEY_Z] = KEY_Z;
  _keys[GLFW_KEY_F1] = KEY_F1;
  _keys[GLFW_KEY_F2] = KEY_F2;
  _keys[GLFW_KEY_F3] = KEY_F3;
  _keys[GLFW_KEY_F4] = KEY_F4;
  _keys[GLFW_KEY_F5] = KEY_F5;
  _keys[GLFW_KEY_F6] = KEY_F6;
  _keys[GLFW_KEY_F7] = KEY_F7;
  _keys[GLFW_KEY_F8] = KEY_F8;
  _keys[GLFW_KEY_F9] = KEY_F9;
  _keys[GLFW_KEY_F10] = KEY_F10;
  _keys[GLFW_KEY_F11] = KEY_F11;
  _keys[GLFW_KEY_F12] = KEY_F12;
}

EngineKeyMap::EngineKeyMap() {
  _fill_imgui_keymap();
  _fill_keymap();
}

// create local/private EngineKeyMap object
// (keymap arrays get populated upon construction)
static EngineKeyMap __key_map;


inline ImGuiKey EngineKeyMap::get_imgui_key(EngineKey key_code) {
  return _imgui_keys[key_code];
}

inline EngineKey EngineKeyMap::get_engine_key(int key_code) {
  return _keys[key_code];
}

EngineKey convert_to_engine_key(int key_code) {
  return __key_map.get_engine_key(key_code);
}

ImGuiKey convert_to_imgui_key(EngineKey key_code) {
  return __key_map.get_imgui_key(key_code);
}

ImGuiKey convert_to_imgui_key(int key_code) {
  return __key_map.get_imgui_key(convert_to_engine_key(key_code));
}

}  // namespace engine
