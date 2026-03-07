// basic YIN implementation

#include "yin_detector.h"
#include <cmath>

namespace tuner::pitch
{

    YinDetector::YinDetector(TunerConfig &config)
        : sampleRate(config.sampleRate)
    {
        int half = config.windowSize / 2;
        diff.resize(half);
        cmnd.resize(half);
    }

    PitchResult YinDetector::detect(
        const float *buffer,
        int size,
        double threshold,
        bool interpolation)
    {
        PitchResult result{};
        result.valid = false;

        int half = size / 2;

        // --- Difference function ---

        for (int tau = 0; tau < half; ++tau)
        {
            double sum = 0.0;

            for (int i = 0; i < half; ++i)
            {
                double delta = buffer[i] - buffer[i + tau];
                sum += delta * delta;
            }

            diff[tau] = sum;
        }

        // --- Cumulative mean normalized difference ---

        cmnd[0] = 1.0;

        double runningSum = 0.0;

        for (int tau = 1; tau < half; ++tau)
        {
            runningSum += diff[tau];

            cmnd[tau] =
                diff[tau] * tau /
                runningSum;
        }

        // --- Absolute threshold ---

        int tauEstimate = -1;

        for (int tau = 2; tau < half; ++tau)
        {
            if (cmnd[tau] < threshold)
            {
                while (tau + 1 < half && cmnd[tau + 1] < cmnd[tau])
                    tau++;

                tauEstimate = tau;
                break;
            }
        }

        if (tauEstimate == -1)
            return result;

        // --- Frequency ---
        double pitch = sampleRate / tauEstimate;

        result.valid = true;
        result.pitch = pitch;
        result.confidence = 1.0 - cmnd[tauEstimate];

        return result;
    }

    void YinDetector::reset()
    {
    }

}