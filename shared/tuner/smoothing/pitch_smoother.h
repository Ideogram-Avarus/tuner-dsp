#pragma once

namespace tuner::smoothing
{

    class PitchSmoother
    {
    public:
        PitchSmoother(double smoothingFactor);
        double process(double newFreq);

    private:
        double smoothingFactor;
    };
}