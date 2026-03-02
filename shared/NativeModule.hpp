#pragma once

#include "include/tuner_engine.hpp"
#include "include/types.hpp"

namespace tuner_native {

class NativeModule {
public:
  explicit NativeModule(int sampleRate);

  void processFrame(const float* samples, int size);
  tuner::TunerResult getLatestResult() const;
  void reset();

private:
  tuner::TunerEngine engine_;
};

} // namespace tuner_native