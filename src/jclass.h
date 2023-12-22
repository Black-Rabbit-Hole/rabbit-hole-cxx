#ifndef JCLASS_H
#define JCLASS_H

#include <jni.h>
#include <string>

#include "jmethod.h"

struct JClass {
    explicit JClass(JNIEnv* env, const std::string& name): env(env) {
        this->jclass = env->FindClass(name.c_str());
    }

    [[nodiscard]] jobject new_object() const;

    [[nodiscard]] jclass row_class() const;

    template<class Return, class... Arguments>
    JMethod<false, Return, Arguments...> get_method(const std::string& name) const {
        return JMethod<false, Return, Arguments...>(env, jclass, name);
    }

    template<class Return, class... Arguments>
    JMethod<true, Return, Arguments...> get_static_method(const std::string& name) const {
        return JMethod<true, Return, Arguments...>(env, jclass, name);
    }

private:
    JNIEnv* env;
    jclass jclass;
};


#endif //JCLASS_H
