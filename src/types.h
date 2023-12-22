#ifndef TYPES_H
#define TYPES_H

#include <jni.h>
#include <type_traits>

template<class Object>
constexpr static bool is_java_type() {
    return std::is_same_v<Object, void> ||
           std::is_same_v<Object, jboolean> ||
           std::is_same_v<Object, jbyte> ||
           std::is_same_v<Object, jchar> ||
           std::is_same_v<Object, jshort> ||
           std::is_same_v<Object, jfloat> ||
           std::is_same_v<Object, jdouble> ||
           std::is_base_of_v<Object, jobject>;
}

#endif
