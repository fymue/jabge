#ifndef ENGINE_SRC_TYPES_H_
#define ENGINE_SRC_TYPES_H_

#include <cmath>

#include "core.h"
#include "serialize.h"

namespace engine {

template<typename T = float>
struct PUB_API Vec2 {
  T x, y;

  Vec2() :
    x(0), y(0) {}

  Vec2(T x, T y) :
    x(x), y(y) {}

  inline T dot(Vec2 other) const {
    return x * other.x + y * other.y;
  }

  inline T sum() const {
    return x + y;
  }

  inline T dist(Vec2 other) const {
    T x_dist = std::abs(other.x - x);
    T y_dist = std::abs(other.y - y);
    return std::sqrt(x_dist * x_dist + y_dist * y_dist);
  }

  inline T len() const {
    return std::sqrt(x * x + y * y);
  }

  // convert vector to unit vector
  inline Vec2 norm() const {
    T length = len();
    return Vec2(x / length, y / length);
  }

  MAKE_SERIALIZEABLE(x, y)
};

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec2<T> vec);

template<typename T = float>
struct PUB_API Vec3 {
  T x, y, z;

  Vec3() :
    x(0), y(0), z(0) {}

  Vec3(T x, T y, T z) :
    x(x), y(y), z(z) {}

  inline T dot(Vec3 other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  inline T sum() const {
    return x + y + z;
  }

  inline T dist(Vec3 other) const {
    T x_dist = std::abs(other.x - x);
    T y_dist = std::abs(other.y - y);
    T z_dist = std::abs(other.z - z);
    return std::sqrt(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);
  }

  inline T len() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  // convert vector to unit vector
  inline Vec3 norm() const {
    T length = len();
    return Vec3(x / length, y / length, z / length);
  }

  MAKE_SERIALIZEABLE(x, y, z)
};

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec3<T> vec);

template<typename T = float>
struct PUB_API Vec4 {
  T w, x, y, z;

  Vec4() :
    w(0), x(0), y(0), z(0) {}

  Vec4(T w, T x, T y, T z) :
    w(w), x(x), y(y), z(z) {}

  inline T dot(Vec4 other) const {
    return w * other.w + x * other.x + y * other.y + z * other.z;
  }
  inline T sum() const {
    w + x + y + z;
  }

  inline T dist(Vec4 other) const {
    T w_dist = std::abs(other.w - w);
    T x_dist = std::abs(other.x - x);
    T y_dist = std::abs(other.y - y);
    T z_dist = std::abs(other.z - z);
    return std::sqrt(w_dist * w_dist + x_dist * x_dist +
                     y_dist * y_dist + z_dist * z_dist);
  }

  inline T len() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
  }

  // convert vector to unit vector
  inline Vec4 norm() const {
    T length = len();
    return Vec4(w / length, x / length, y / length, z / length);
  }

  MAKE_SERIALIZEABLE(w, x, y, z)
};

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec4<T> vec);

}  // namespace engine

#endif  // ENGINE_SRC_TYPES_H_
