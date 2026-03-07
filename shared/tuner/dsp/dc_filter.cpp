// Formula:
// y[n] = x[n] - x[n-1] + R * y[n-1]


#include "dc_filter.h"

namespace tuner::dsp {

DcFilter::DcFilter(float pole)
    : pole(pole)
{
}

void DcFilter::process(float* samples, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        float x = samples[i];

        float y = x - prevInput + pole * prevOutput;

        prevInput = x;
        prevOutput = y;

        samples[i] = y;
    }
}

void DcFilter::reset()
{
    prevInput = 0.0f;
    prevOutput = 0.0f;
}

}