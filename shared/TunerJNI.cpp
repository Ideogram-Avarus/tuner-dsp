#include "NativeTunerDsp.h"
#include <jni.h>

static NativeTunerDsp* gEngine = nullptr; // single engine

extern "C" {

// Create engine
JNIEXPORT void JNICALL
Java_com_example_myapp_NativeTuner_createEngine(JNIEnv* env, jobject thiz, jint sampleRate) {
    if (!gEngine) {
        gEngine = new NativeTunerDsp(sampleRate);
    }
}

// Destroy engine
JNIEXPORT void JNICALL
Java_com_example_myapp_NativeTuner_destroyEngine(JNIEnv* env, jobject thiz) {
    delete gEngine;
    gEngine = nullptr;
}

// Process frame
JNIEXPORT void JNICALL
Java_com_example_myapp_NativeTuner_processFrame(JNIEnv* env, jobject thiz, jfloatArray samples) {
    if (!gEngine) return;

    jsize len = env->GetArrayLength(samples);
    jfloat* data = env->GetFloatArrayElements(samples, nullptr);

    gEngine->cxxProcessFrame(data, len);

    env->ReleaseFloatArrayElements(samples, data, 0);
}

// Get latest result
JNIEXPORT jfloat JNICALL
Java_com_example_myapp_NativeTuner_getLatestResult(JNIEnv* env, jobject thiz) {
    if (!gEngine) return 0.0f;
    TunerResult res = gEngine->cxxGetLatestResult();
    return res.value; // adjust depending on your TunerResult struct
}

// Reset engine
JNIEXPORT void JNICALL
Java_com_example_myapp_NativeTuner_reset(JNIEnv* env, jobject thiz) {
    if (!gEngine) return;
    gEngine->cxxReset();
}

} // extern "C"