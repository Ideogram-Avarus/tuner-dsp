// Formula: Implements exponential smoothing.
// y = α * new + (1-α) * prev

#include "pitch_smoother.h"

namespace tuner::smoothing
{

    PitchSmoother::PitchSmoother(double smoothingFactor)
        : smoothingFactor(smoothingFactor)
    {
    }

    double PitchSmoother::process(double newFreq)
    {
        if (prev == 0.0)
        {
            prev = newFreq;
            hasPrev = true;
            return newFreq;
        }

        const double smoothed =
            smoothingFactor * newFreq +
            (1.0 - smoothingFactor) * prev;

        prev = smoothed;
        return smoothed;
    }

    void PitchSmoother::reset() {
        prev = 0.0;
        hasPrev = false;
    }

}