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


class NativeMyModule : public NativeMyModuleCxxSpec<NativeMyModule> {
public:
  NativeMyModule(std::shared_ptr<CallInvoker> jsInvoker);
  std::string reverseString(jsi::Runtime& rt, std::string input);
};

}