#pragma once

#include <vector>
#include "../../types.h"

namespace tuner::pitch
{
    class YinDetector
    {
    public:
        YinDetector(TunerConfig& config);

        PitchResult detect(
            const float* buffer,
            int size,
            double threshold,
            bool interpolation
        );

        void reset();

    private:
        double sampleRate; 
        std::vector<double> diff;
        std::vector<double> cmnd;
    };
}