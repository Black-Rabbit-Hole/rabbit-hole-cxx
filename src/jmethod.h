#ifndef METHOD_H
#define METHOD_H

#include <jni.h>
#include <string>

#include "types.h"

template<bool IsStatic, class Return, class... Arguments>
struct JMethod {
};

template<class Return, class... Arguments>
struct JMethod<true, Return, Arguments...> {
    static_assert(is_java_type<Return>);

    explicit JMethod(JNIEnv* env, jclass jclass, const std::string& name): env(env), jmethod_id(nullptr) {
        this->jmethod_id = env->GetStaticMethodID(jclass, name.c_str(), "(Ljava/lang/Object;)Z");
        this->jclass = jclass;
    }

    constexpr Return operator()(Arguments... args) {
        if constexpr (std::is_same_v<void, Return>) {
            return env->CallStaticVoidMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jchar, Return>) {
            return env->CallStaticCharMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jbyte, Return>) {
            return env->CallStaticByteMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jshort, Return>) {
            return env->CallStaticShortMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jfloat, Return>) {
            return env->CallStaticFloatMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jdouble, Return>) {
            return env->CallStaticDoubleMethod(jclass, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jboolean, Return>) {
            return env->CallStaticBooleanMethod(jclass, jmethod_id, args...);
        } else {
            return env->CallStaticObjectMethod(jclass, jmethod_id, args...);
        }
    }

private:
    JNIEnv* env;
    jclass jclass;
    jmethodID jmethod_id;
};

template<class Return, class... Arguments>
struct JMethod<false, Return, Arguments...> {
    static_assert(is_java_type<Return>);

    explicit JMethod(JNIEnv* env, jclass jclass, const std::string& name): env(env), jmethod_id(nullptr) {
        this->jmethod_id = env->GetStaticMethodID(jclass, name.c_str(), "(Ljava/lang/Object;)Z");
    }

    constexpr Return operator()(jobject obj, Arguments... args) {
        if constexpr (std::is_same_v<void, Return>) {
            return env->CallVoidMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jchar, Return>) {
            return env->CallCharMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jbyte, Return>) {
            return env->CallByteMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jshort, Return>) {
            return env->CallShortMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jfloat, Return>) {
            return env->CallFloatMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jdouble, Return>) {
            return env->CallDoubleMethod(obj, jmethod_id, args...);
        } else if constexpr (std::is_same_v<jboolean, Return>) {
            return env->CallBooleanMethod(obj, jmethod_id, args...);
        } else {
            return env->CallObjectMethod(obj, jmethod_id, args...);
        }
    }

private:
    JNIEnv* env;
    jmethodID jmethod_id;
};

#endif //METHOD_H
