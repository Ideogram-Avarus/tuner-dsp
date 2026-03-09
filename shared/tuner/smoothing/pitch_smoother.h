#pragma once

namespace tuner::smoothing
{

    class PitchSmoother
    {
    public:
        PitchSmoother(double smoothingFactor);
        double process(double newFreq);
        void reset();

    private:
        double smoothingFactor;
        double prev = 0.0;
        bool hasPrev = false;
    };
}