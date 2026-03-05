#include "NativeTunerDsp.h"



namespace native_side {

    
NativeTunerDsp::NativeTunerDsp(int sampleRate)
    : engine_(sampleRate) {}
    
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

