#pragma once

namespace tuner::rms
{
    class RmsDetector
    {
    public:
        RmsDetector(int windowSize);
        double process(const float *buffer, int size);
    };
}