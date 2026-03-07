#pragma once

#include <vector>
#include <cstddef>

namespace tuner::dsp {

class Window {
public:
    explicit Window(std::size_t size);

    void apply(float* samples, std::size_t size) const;

    std::size_t size() const;

private:
    std::vector<float> weights;
};

}