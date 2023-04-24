#ifndef SRC_CORE_H_
#define SRC_CORE_H_

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

#endif  // SRC_CORE_H_