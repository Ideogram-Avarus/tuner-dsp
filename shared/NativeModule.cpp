#include "NativeModule.hpp"

#include <jni.h>

namespace facebook::react {

NativeTuner::NativeTuner(int sampleRate)
    : engine_(sampleRate) {}

void NativeTuner::processFrame(const float* samples, int size) {
  engine_.processFrame(samples, size);
}

TunerResult NativeTuner::getLatestResult() const {
  return engine_.getLatestResult();
}

void NativeTuner::reset() {
  engine_.reset();
}

}


