#ifndef ENGINE_SRC_SERIALIZE_H_
#define ENGINE_SRC_SERIALIZE_H_

#include "boost/serialization/access.hpp"

#include "boost/serialization/split_member.hpp"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"

#include "boost/serialization/vector.hpp"
#include "boost/serialization/array.hpp"
#include "boost/serialization/utility.hpp"

#include "boost/serialization/shared_ptr.hpp"
#include "boost/serialization/unique_ptr.hpp"


// base case for parameter pack expansion
template<class Archive>
static void __serialize(Archive &ar) {}

// expand parameter pack and serialize every passed parameter
template<class Archive, typename T, typename ...Tr>
static void __serialize(Archive &ar, T &first, Tr &...rest) {
  ar & first;
  __serialize(ar, rest...);
}

// allows serialization of all passed parameters
// for any type this macro is called in
#define MAKE_SERIALIZEABLE(...) \
  friend boost::serialization::access;                      \
  template<class Archive>                                   \
  void serialize(Archive &ar, const unsigned int version) { \
    __serialize(ar, __VA_ARGS__);                           \
  }                                                         \

#endif  // ENGINE_SRC_SERIALIZE_H_
