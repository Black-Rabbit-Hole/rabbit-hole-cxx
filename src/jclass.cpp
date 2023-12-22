#include "jclass.h"

jobject JClass::new_object() const {
    return env->AllocObject(jclass);
}

jclass JClass::row_class() const {
    return jclass;
}
