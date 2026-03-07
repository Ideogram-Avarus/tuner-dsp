// Formula: Han Window
// w[n] = 0.5 * (1 - cos(2πn/(N-1)))

#include "window.h"
#include <cmath>

namespace tuner::dsp
{

    Window::Window(std::size_t size)
        : weights(size)
    {
        const double twoPi = 2.0 * 3.14159265358979323846;

        for (std::size_t n = 0; n < size; ++n)
        {
            weights[n] = static_cast<float>(
                0.5 * (1.0 - std::cos(twoPi * n / (size - 1))));
        }
    }

    void Window::apply(float *samples, std::size_t size) const
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            samples[i] *= weights[i];
        }
    }

    std::size_t Window::size() const
    {
        return weights.size();
    }

}