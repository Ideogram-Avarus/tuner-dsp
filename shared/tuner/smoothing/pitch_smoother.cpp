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
        static double prev = 0.0;

        if (prev == 0.0)
        {
            prev = newFreq;
            return newFreq;
        }

        double smoothed =
            smoothingFactor * newFreq +
            (1.0 - smoothingFactor) * prev;

        prev = smoothed;

        return smoothed;
    }

}