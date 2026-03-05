#pragma once

#include <vector>
#include "pitch_detector.h"
#include "types.h"

namespace tuner {


class TunerEngine {
public:
    explicit TunerEngine(int sampleRate);

    void processFrame(const float* samples, int size);
    TunerResult getLatestResult() const;
    void reset();

private:
    int sampleRate;
    PitchDetector detector;
    std::vector<float> internalBuffer;
    TunerResult latest;
};

};