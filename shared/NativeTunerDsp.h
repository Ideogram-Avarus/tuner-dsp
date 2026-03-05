#pragma once
#include "include/tuner_engine.h"
#include "include/types.h"

class NativeTunerDsp {
public:
    explicit NativeTunerDsp(int sampleRate);

    void cxxProcessFrame(const float* samples, int size);
    TunerResult cxxGetLatestResult() const;
    void cxxReset();

private:
    tuner::TunerEngine engine_;
};