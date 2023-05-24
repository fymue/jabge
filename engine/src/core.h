#ifndef ENGINE_SRC_CORE_H_
#define ENGINE_SRC_CORE_H_

// definitions of dynamic linking export/import
// declarations for different operating systems

#if defined(__GNUC__)
  //  GCC Linux
  #define EXPORT __attribute__((visibility("default")))
  #define IMPORT
#elif defined(_MSC_VER)
  //  Windows
  #define EXPORT __declspec(dllexport)
  #define IMPORT __declspec(dllimport)
#else
  #define EXPORT
  #define IMPORT
  #pragma warning Unknown dynamic link import/export instruction
#endif

// if the engine (aka the dynamic library) is supposed to be built,
// use export declaration, else use import declaration
#ifdef BUILD_ENGINE
  #define PUB_API EXPORT
#else
  #define PUB_API IMPORT
#endif

// shortcut for binding a function to and std::function argument
#define BIND_EVENT(func) std::bind(&func, this, std::placeholders::_1)

// assert statements

#include <iostream>

static void __engine_assert(bool check, const char *msg) {
  if (!check) {
    std::cerr << msg << "\n";;
    std::exit(1);
  }
}

static void __engine_basic_assert(bool check, const char *msg) {
  if (!check) {
    std::cerr << "Assertion \"" << msg << "\" failed!\n";
    std::exit(1);
  }
}

#ifdef NDEBUG
  #define ENGINE_ASSERT(check, msg)
  #define ENGINE_BASIC_ASSERT(check)
#else
  #define ENGINE_ASSERT(check, msg)   __engine_assert(check, msg)

  #define ENGINE_BASIC_ASSERT(check)  __engine_basic_assert(check, #check)
#endif

// OpenGL3 version for ImGui
#define ENGINE_GLSL_VERSION "#version 460"

#endif  // ENGINE_SRC_CORE_H_
