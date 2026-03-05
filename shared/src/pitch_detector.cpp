#include "pitch_detector.h"
#include <cmath>
#include <limits>

namespace tuner
{

    PitchDetector::PitchDetector(int sampleRate)
        : sampleRate(sampleRate) {}

    double PitchDetector::difference(const std::vector<float> &buffer, int tau)
    {
        double sum = 0.0;
        int size = buffer.size();

        for (int i = 0; i < size - tau; i++)
        {
            double delta = buffer[i] - buffer[i + tau];
            sum += delta * delta;
        }

        return sum;
    }

    double PitchDetector::detect(const std::vector<float> &buffer)
    {
        const int size = buffer.size();

        if (size < 2)
            return -1;

        const int maxTau = size / 2;
        std::vector<double> diff(maxTau, 0.0);

        // Step 1: Difference function
        for (int tau = 1; tau < maxTau; tau++)
        {
            diff[tau] = difference(buffer, tau);
        }

        // Step 2: Cumulative mean normalized difference
        double runningSum = 0.0;
        std::vector<double> cmnd(maxTau, 0.0);
        cmnd[0] = 1;

        for (int tau = 1; tau < maxTau; tau++)
        {
            runningSum += diff[tau];
            if (runningSum == 0)
                cmnd[tau] = 1;
            else
                cmnd[tau] = diff[tau] * tau / runningSum;
        }

        // Step 3: Absolute threshold
        const double threshold = 0.15;
        int tauEstimate = -1;

        for (int tau = 2; tau < maxTau; tau++)
        {
            if (cmnd[tau] < threshold)
            {
                while (tau + 1 < maxTau && cmnd[tau + 1] < cmnd[tau])
                    tau++;
                tauEstimate = tau;
                break;
            }
        }

        if (tauEstimate == -1)
            return -1;

        // Step 4: Convert tau to frequency
        double frequency = static_cast<double>(sampleRate) / tauEstimate;

        return frequency;
    }

}