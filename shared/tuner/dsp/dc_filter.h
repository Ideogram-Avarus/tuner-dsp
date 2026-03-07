#pragma once

#include <cstddef>

namespace tuner::dsp {

class DcFilter {
public:
    explicit DcFilter(float pole = 0.995f);

    void process(float* samples, std::size_t size);

    void reset();

private:
    float pole;

    float prevInput = 0.0f;
    float prevOutput = 0.0f;
};

}