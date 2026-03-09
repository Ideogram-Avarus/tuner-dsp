#include "NativeTunerDsp.h"
#include <jni.h>

using namespace native_side;

static NativeTunerDsp* gEngine = nullptr; 

extern "C" {

// Create engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_TunerJniEngine_cxxCreateEngine(
    JNIEnv* env, 
    jobject thiz,
    jint sampleRate,
    jint windowSize,
    jint hopSize,

    jdouble minFrequency,
    jdouble maxFrequency,

    jdouble yinThreshold,
    jdouble minConfidence,

    jdouble minRMS,
    jdouble smoothingFactor,

    jdouble noteHysteresisCents,

    jboolean enableInterpolation,
    jboolean enableHarmonicCorrection,
    jboolean removeDC
) {
    if (gEngine) return;
    
    TunerConfig config;

    config.sampleRate = sampleRate;
    config.windowSize = windowSize;
    config.hopSize = hopSize;

    config.minFrequency = minFrequency;
    config.maxFrequency = maxFrequency;

    config.yinThreshold = yinThreshold;
    config.minConfidence = minConfidence;

    config.minRMS = minRMS;
    config.smoothingFactor = smoothingFactor;

    config.noteHysteresisCents = noteHysteresisCents;

    config.enableInterpolation = enableInterpolation;
    config.enableHarmonicCorrection = enableHarmonicCorrection;
    config.removeDC = removeDC;

    gEngine = new NativeTunerDsp(config);
}

// Destroy engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_TunerJniEngine_cxxDestroyEngine(JNIEnv* env, jobject thiz) {
    delete gEngine;
    gEngine = nullptr;
}

// Process frame
JNIEXPORT void JNICALL
Java_com_tunerdsp_TunerJniEngine_cxxProcessFrame(JNIEnv* env, jobject thiz, jfloatArray samples, jint length) {
    if (!gEngine) return;

    const jsize len = env->GetArrayLength(samples);
    const jsize safeLen = (length < len) ? length : len;
    if (safeLen <= 0) return;

    jfloat* data = env->GetFloatArrayElements(samples, nullptr);
    gEngine->cxxProcessFrame(data, static_cast<int>(safeLen));
    env->ReleaseFloatArrayElements(samples, data, 0);
}

// Get latest result
JNIEXPORT jdoubleArray JNICALL
Java_com_tunerdsp_TunerJniEngine_cxxGetLatestResult(JNIEnv* env, jobject thiz) {
    if (!gEngine) return nullptr;

    TunerResult res = gEngine->cxxGetLatestResult();

    jdoubleArray arr = env->NewDoubleArray(6);
    if (!arr) return nullptr;

    jdouble tmp[6] = {
        res.hasPitch ? 1.0 : 0.0,
        res.frequency,
        res.cents,
        (double)res.midiNote,
        res.amplitude,
        res.confidence
    };

    env->SetDoubleArrayRegion(arr, 0, 6, tmp);
    return arr;
}

// Reset engine
JNIEXPORT void JNICALL
Java_com_tunerdsp_TunerJniEngine_cxxReset(JNIEnv* env, jobject thiz) {
    if (!gEngine) return;
    gEngine->cxxReset();
}

} // extern "C"