// Formula: Implements exponential smoothing.
// y = a * new + (1-a) * prev

#include "pitch_smoother.h"

namespace tuner::smoothing
{

    PitchSmoother::PitchSmoother(double smoothingFactor)
        : smoothingFactor(smoothingFactor)
    {
    }

    double PitchSmoother::process(double newFreq)
    {
        if (!hasPrev)
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

    void PitchSmoother::reset()
    {
        prev = 0.0;
        hasPrev = false;
    }

}
