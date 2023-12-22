#include "rh_Searcher.h"

#include <functional>

#include "rh_jvmti.h"


static jvmtiIterationControl JNICALL
HeapObjectCallback(jlong class_tag, jlong size, jlong* tag_ptr, void* user_data) {
    *tag_ptr = 1;
    return JVMTI_ITERATION_CONTINUE;
}

JNIEXPORT jobject JNICALL Java_rh_Searcher_findAll(JNIEnv* env, jclass, jclass klass) {
    auto jni = JNI::from(env);
    auto llc = jni.find_class("java/util/LinkedList");
    auto collection = llc.new_object();
    auto addObjectToCollection = llc.get_method<jboolean, jobject>("add");

    auto jvmti = jni.get_jvmti(env);

    jvmtiCapabilities capabilities = {0};
    capabilities.can_tag_objects = 1;
    jvmti->AddCapabilities(&capabilities);

    jvmti->IterateOverInstancesOfClass(klass, JVMTI_HEAP_OBJECT_TAGGED,
                                       HeapObjectCallback, nullptr);

    jlong tag = 1;
    jint count;
    jobject* instances;

    jvmti->GetObjectsWithTags(1, &tag, &count, &instances, nullptr);

    for (int i = 0; i < count; i++) {
        addObjectToCollection(collection, instances[i]);
    }

    jvmti->Deallocate(reinterpret_cast<unsigned char *>(instances));

    return collection;
}

JNIEXPORT void JNICALL Java_rh_Searcher_printLn
(JNIEnv* env, jclass, jstring v) {
    printf("Works");
}
