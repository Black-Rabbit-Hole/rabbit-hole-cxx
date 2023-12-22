//
// Created by noname on 12/20/2023.
//

#ifndef RH_JVMTI_H
#define RH_JVMTI_H

#include <string>
#include <jvmti.h>

#include "jclass.h"

class JNI {
public:
    static JNI from(JNIEnv*);

    [[nodiscard]] JClass find_class(const std::string&) const;

    jvmtiEnv* get_jvmti(JNIEnv*) const;

private:
    explicit JNI(JNIEnv* env);

    JNIEnv* env;
    jvmtiEnv* jvmti;
};


#endif //RH_JVMTI_H
