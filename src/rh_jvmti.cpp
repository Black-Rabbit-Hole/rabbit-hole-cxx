#include "rh_jvmti.h"

JNI JNI::from(JNIEnv* env) {
    return JNI(env);
}

JNI::JNI(JNIEnv* env) : env(env), jvmti(nullptr) {
    JavaVM* jvm;
    env->GetJavaVM(&jvm);
    jvmtiEnv* jvmti;
    jvm->GetEnv(reinterpret_cast<void **>(&jvmti), JVMTI_VERSION_1_0);
}

JClass JNI::find_class(const std::string& name) const {
    return JClass(env, name);
}

jvmtiEnv* JNI::get_jvmti(JNIEnv* env) const {
    return jvmti;
}
