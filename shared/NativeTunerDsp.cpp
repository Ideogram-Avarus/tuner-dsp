#include "NativeTunerDsp.h"



namespace native_side {

    
NativeTunerDsp::NativeTunerDsp(TunerConfig config)
    : engine_(config) {}
    
    void NativeTunerDsp::cxxProcessFrame(const float* samples, int size) {
        engine_.processFrame(samples, size);
}

TunerResult NativeTunerDsp::cxxGetLatestResult() const {
    return engine_.getLatestResult();
}

void NativeTunerDsp::cxxReset() {
    engine_.reset();
}



}

