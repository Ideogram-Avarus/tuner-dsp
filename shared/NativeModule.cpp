#include "NativeModule.hpp"

#include <jni.h>

namespace tuner_native {

NativeModule::NativeModule(int sampleRate)
    : engine_(sampleRate) {}

void NativeModule::processFrame(const float* samples, int size) {
  engine_.processFrame(samples, size);
}

tuner::TunerResult NativeModule::getLatestResult() const {
  return engine_.getLatestResult();
}

void NativeModule::reset() {
  engine_.reset();
}

} // namespace tuner_native

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_mytuner_specs_NativeTunerModule_initNative(JNIEnv* env, jclass, jint sampleRate) {
  auto* instance = new tuner_native::NativeModule(static_cast<int>(sampleRate));
  return reinterpret_cast<jlong>(instance);
}

JNIEXPORT void JNICALL
Java_com_mytuner_specs_NativeTunerModule_processFrameNative(JNIEnv* env, jclass, jlong handle, jfloatArray frameArray) {
  auto* instance = reinterpret_cast<tuner_native::NativeModule*>(handle);
  if (!instance || frameArray == nullptr) {
    return;
  }

  jsize length = env->GetArrayLength(frameArray);
  jfloat* data = env->GetFloatArrayElements(frameArray, nullptr);

  if (data != nullptr && length > 0) {
    instance->processFrame(reinterpret_cast<const float*>(data), static_cast<int>(length));
  }

  env->ReleaseFloatArrayElements(frameArray, data, JNI_ABORT);
}

JNIEXPORT jobject JNICALL
Java_com_mytuner_specs_NativeTunerModule_getLatestResultNative(JNIEnv* env, jclass, jlong handle) {
  auto* instance = reinterpret_cast<tuner_native::NativeModule*>(handle);
  if (!instance) {
    return nullptr;
  }

  tuner::TunerResult result = instance->getLatestResult();

  jclass mapClass = env->FindClass("com/facebook/react/bridge/WritableNativeMap");
  if (mapClass == nullptr) {
    return nullptr;
  }

  jmethodID mapCtor = env->GetMethodID(mapClass, "<init>", "()V");
  jobject mapObj = env->NewObject(mapClass, mapCtor);

  jmethodID putBoolean = env->GetMethodID(mapClass, "putBoolean", "(Ljava/lang/String;Z)V");
  jmethodID putDouble = env->GetMethodID(mapClass, "putDouble", "(Ljava/lang/String;D)V");
  jmethodID putInt = env->GetMethodID(mapClass, "putInt", "(Ljava/lang/String;I)V");

  jstring hasPitchKey = env->NewStringUTF("hasPitch");
  jstring frequencyKey = env->NewStringUTF("frequency");
  jstring midiNoteKey = env->NewStringUTF("midiNote");
  jstring centsKey = env->NewStringUTF("cents");
  jstring amplitudeKey = env->NewStringUTF("amplitude");

  env->CallVoidMethod(mapObj, putBoolean, hasPitchKey, static_cast<jboolean>(result.hasPitch));
  env->CallVoidMethod(mapObj, putDouble, frequencyKey, static_cast<jdouble>(result.frequency));
  env->CallVoidMethod(mapObj, putInt, midiNoteKey, static_cast<jint>(result.midiNote));
  env->CallVoidMethod(mapObj, putDouble, centsKey, static_cast<jdouble>(result.cents));
  env->CallVoidMethod(mapObj, putDouble, amplitudeKey, static_cast<jdouble>(result.amplitude));

  env->DeleteLocalRef(hasPitchKey);
  env->DeleteLocalRef(frequencyKey);
  env->DeleteLocalRef(midiNoteKey);
  env->DeleteLocalRef(centsKey);
  env->DeleteLocalRef(amplitudeKey);

  return mapObj;
}

JNIEXPORT void JNICALL
Java_com_mytuner_specs_NativeTunerModule_destroyNative(JNIEnv*, jclass, jlong handle) {
  auto* instance = reinterpret_cast<tuner_native::NativeModule*>(handle);
  delete instance;
}

} // extern "C"
