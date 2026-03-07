// Formula: Computes RMS amplitude
// RMS = sqrt(mean(x²))


#include "rms_detector.h"
#include <cmath>

namespace tuner::rms {

RmsDetector::RmsDetector(int windowSize)
{
}

double RmsDetector::process(const float* buffer, int size)
{
    double sum = 0.0;

    for (int i = 0; i < size; ++i)
    {
        double v = buffer[i];
        sum += v * v;
    }

    double mean = sum / size;

    return std::sqrt(mean);
}

}