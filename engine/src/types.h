#ifndef ENGINE_SRC_TYPES_H_
#define ENGINE_SRC_TYPES_H_

#include "core.h"

namespace engine {

template<typename T = float>
struct PUB_API Vec2 {
  T x, y;

  Vec2() :
    x(0), y(0) {}

  Vec2(T x, T y) :
    x(x), y(y) {}
};

template<typename T = float>
struct PUB_API Vec3 {
  T x, y, z;

  Vec3() :
    x(0), y(0), z(0) {}

  Vec3(T x, T y, T z) :
    x(x), y(y), z(z) {}
};

template<typename T = float>
struct PUB_API Vec4 {
  T w, x, y, z;

  Vec4() :
    w(0), x(0), y(0), z(0) {}

  Vec4(T w, T x, T y, T z) :
    w(w), x(x), y(y), z(z) {}
};

}  // namespace engine

#endif  // ENGINE_SRC_TYPES_H_
