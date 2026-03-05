#include "NativeTunerDsp.h"
#include <jni.h>

using namespace native_side;

static NativeTunerDsp* gEngine = nullptr; 

extern "C" {

// Create engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_NativeTuner_createEngine(JNIEnv* env, jobject thiz, jint sampleRate) {
    if (!gEngine) {
        gEngine = new NativeTunerDsp(sampleRate);
    }
}

// Destroy engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_NativeTuner_destroyEngine(JNIEnv* env, jobject thiz) {
    delete gEngine;
    gEngine = nullptr;
}

// Process frame
JNIEXPORT void JNICALL
Java_com_tunerdsp_NativeTuner_cxxProcessFrame(JNIEnv* env, jobject thiz, jfloatArray samples) {
    if (!gEngine) return;

    jsize len = env->GetArrayLength(samples);
    jfloat* data = env->GetFloatArrayElements(samples, nullptr);

    gEngine->cxxProcessFrame(data, len);

    env->ReleaseFloatArrayElements(samples, data, 0);
}

// Get latest result
JNIEXPORT jdoubleArray JNICALL
Java_com_tunerdsp_NativeTuner_cxxGetLatestResult(JNIEnv* env, jobject thiz) {
    if (!gEngine) return nullptr;

    TunerResult res = gEngine->cxxGetLatestResult();

    jdoubleArray arr = env->NewDoubleArray(5);
    if (!arr) return nullptr;

    jdouble tmp[5] = {
        res.hasPitch ? 1.0 : 0.0,
        res.frequency,
        res.cents,
        (double)res.midiNote,
        res.amplitude
    };

    env->SetDoubleArrayRegion(arr, 0, 5, tmp);
    return arr;
}

// Reset engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_NativeTuner_cxxReset(JNIEnv* env, jobject thiz) {
    if (!gEngine) return;
    gEngine->cxxReset();
}

} // extern "C"