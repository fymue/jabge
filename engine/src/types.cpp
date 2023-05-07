#include "enginepch.h"
#include "types.h"

namespace engine {

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec2<T> vec) {
  stream << "Vec2{" << vec.x << ", " << vec.y << "} ";
  return stream;
}

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec3<T> vec) {
  stream << "Vec3{" << vec.x << ", " << vec.y
         << ", " << vec.z << "} ";
  return stream;
}

template<typename T = float>
inline std::ostream &operator<<(std::ostream &stream, Vec4<T> vec) {
  stream << "Vec4{" << vec.w << ", " < vec.x
         << ", " << vec.y << ", " << vec.z << "} ";
  return stream;
}

}  // namespace engine
