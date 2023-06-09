#include "enginepch.h"
#include "linuxwindow.h"

#define GET_WINDOW_USER_PTR(window) \
static_cast<WindowData*>(glfwGetWindowUserPointer(window))

namespace engine {

static bool is_glfw_initialized = false;

// ### callback functions for every window/key/mouse event ###

static auto __resize_callback = [](GLFWwindow *window, int width, int height) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  data->width = width;
  data->height = height;

  // dispatch resize event
  WindowResizedEvent event(width, height);
  data->callback_fn(&event);
};

static auto __close_callback = [](GLFWwindow *window) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  // dispatch close event
  WindowClosedEvent event;
  data->callback_fn(&event);
};

static auto __focus_callback = [](GLFWwindow *window, int focus) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  // dispatch focus event
  WindowFocusedEvent event(focus);
  data->callback_fn(&event);
};

static auto __key_callback = [](GLFWwindow *window, int key_code,
                                int scan_code, int key_action, int mods) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  // determine key action and dispatch appropriate key event
  switch (key_action) {
    case GLFW_PRESS :
    {
      KeyPressedEvent event(key_code, scan_code, 0);
      data->callback_fn(&event);
      break;
    }
    case GLFW_REPEAT :
    {
      KeyPressedEvent event(key_code, scan_code, 1);
      data->callback_fn(&event);
      break;
    }
    case GLFW_RELEASE :
    {
      KeyReleasedEvent event(key_code, scan_code);
      data->callback_fn(&event);
      break;
    }
  }
};

static auto __char_callback =  [](GLFWwindow *window, unsigned int key_code) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  KeyTypedEvent event(static_cast<int>(key_code));
  data->callback_fn(&event);
};

static auto __mouse_button_callback = [](GLFWwindow *window, int button,
                                         int action, int mods) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  // determine key action and dispatch appropriate key event
  switch (action) {
    case GLFW_PRESS :
    {
      MousePressedEvent event(button);
      data->callback_fn(&event);
      break;
    }
    case GLFW_RELEASE :
    {
      MouseReleasedEvent event(button);
      data->callback_fn(&event);
      break;
    }
  }
};

static auto __move_callback = [](GLFWwindow *window,
                                 double x_pos, double y_pos) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");
  data->mouse_pos = Vec2(x_pos, y_pos);

  // dispatch (mouse) move event
  MouseMovedEvent event(x_pos, y_pos);
  data->callback_fn(&event);
};

static auto __scroll_callback = [](GLFWwindow *window,
                                   double x_offset, double y_offset) {
  WindowData *data = GET_WINDOW_USER_PTR(window);
  ENGINE_ASSERT(data, "Couldn't get window data from GLFW!");

  // dispatch scroll event
  MouseScrolledEvent event(x_offset, y_offset);
  data->callback_fn(&event);
};

static auto __error_callback = [](int err, const char *msg) {
  std::stringstream error_msg;
  error_msg << "GLFW error: \"" << msg << "\" (code: " << err << ")";
  ENGINE_LOG_ERROR(error_msg.str());
};

// #################################################

// create a new linux window based on the specified window
// properties and transfer ownership to the window to the caller
Window *Window::create(const WindowProperties &props) {
  return new LinuxWindow(props);
}

/*
 * initialize the linx window ased on the specified window properties;
 * this method initiliazes GLFW and creates a new GLFW window and provides
 * it with the window data of this window via GLFW's setWindowUserPointer
 * function;
 * this init method also sets all window-event-related callbacks
 */
void LinuxWindow::init(const WindowProperties &props) {
  _data.width = props.width;
  _data.height = props.height;
  _data.name = props.name;

  if (!is_glfw_initialized) {
    int success = glfwInit();
    ENGINE_ASSERT(success, "Window couldn't be initialized!");

    is_glfw_initialized = true;
    _window = glfwCreateWindow(_data.width, _data.height,
                               _data.name.c_str(), nullptr, nullptr);
    _data.window = _window;
    glfwMakeContextCurrent(_window);

    // pass custom data to window
    glfwSetWindowUserPointer(_window, &_data);
    set_vsync(true);

    int glad_init_success =
      gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress));
    ENGINE_ASSERT(glad_init_success, "Failed to initialize GLAD!");

    // input polling will detect inputs to this window
    _window_input = new LinuxWindowInput();
    Input::switch_input(_window_input);
  }

  // window callbacks
  glfwSetWindowSizeCallback(_window, __resize_callback);
  glfwSetWindowCloseCallback(_window, __close_callback);
  glfwSetWindowFocusCallback(_window, __focus_callback);

  // key callbacks
  glfwSetKeyCallback(_window, __key_callback);

  // char callback (which key was pressed?)
  glfwSetCharCallback(_window, __char_callback);

  // mouse callbacks
  glfwSetMouseButtonCallback(_window, __mouse_button_callback);
  glfwSetScrollCallback(_window, __scroll_callback);
  glfwSetCursorPosCallback(_window, __move_callback);

  // error callback
  glfwSetErrorCallback(__error_callback);
}

LinuxWindow::LinuxWindow(const WindowProperties &props) :
  _window(nullptr) {
  init(props);
}

LinuxWindow::~LinuxWindow() {
  glfwDestroyWindow(_window);
  delete _window_input;
}

// process all pending events and swap the buffers (every frame)
void LinuxWindow::on_update() {
  glfwPollEvents();
  glfwSwapBuffers(_window);
}

void LinuxWindow::set_vsync(bool on) {
  _data.vsync = on;

  if (on) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
}

bool LinuxWindow::is_vsync() const {
  return _data.vsync;
}

std::ostream &operator<<(std::ostream &stream, const LinuxWindow &window) {
  stream << "LinuxWindow (" << window._data.name << "): "
         << window._data.width << " x " << window._data.height;
  return stream;
}

}  // namespace engine
