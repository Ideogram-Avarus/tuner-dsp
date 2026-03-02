#include "NativeModule.hpp"

#include <jni.h>

namespace tuner_native {

NativeModule::NativeModule(int sampleRate)
    : engine_(sampleRate) {}

void NativeModule::processFrame(const float* samples, int size) {
  engine_.processFrame(samples, size);
}

TunerResult NativeModule::getLatestResult() const {
  return engine_.getLatestResult();
}

void NativeModule::reset() {
  engine_.reset();
}

}


