#pragma once

#include "include/tuner_engine.hpp"
#include "include/types.hpp"
#include <AppSpecsJSI.h>
#include <memory>
#include <string>

namespace facebook::react {



class NativeTuner : public NativeMyModuleCxxSpec<NativeMyModule> {
public:
  explicit NativeTuner(int sampleRate);

  void processFrame(const float* samples, int size);
  TunerResult getLatestResult() const;
  void reset();

private:
  tuner::TunerEngine engine_;
};




}