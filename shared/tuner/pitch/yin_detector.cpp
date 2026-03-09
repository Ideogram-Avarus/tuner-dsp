// YIN pitch detection (step-by-step):
// 1) Difference function d(tau): measures similarity between signal and
//    delayed signal for each lag tau. Lower values are better candidates.
// 2) CMND (cumulative mean normalized difference): normalizes d(tau) to make
//    thresholding robust across different amplitudes.
// 3) Absolute threshold: picks the first meaningful dip below threshold.
// 4) Optional parabolic interpolation: refines tau to sub-sample precision.
// 5) Convert lag to frequency with f0 = sampleRate / tau.
//
// This implementation is intentionally simple and tuned for real-time use.

#include "yin_detector.h"
#include <algorithm>
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

            if (runningSum <= 1e-12)
            {
                cmnd[tau] = 1.0;
            }
            else
            {
                cmnd[tau] =
                    diff[tau] * tau /
                    runningSum;
            }
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

        double tauRefined = static_cast<double>(tauEstimate);

        // --- Optional interpolation (parabolic refinement around CMND minimum) ---
        if (interpolation && tauEstimate > 1 && tauEstimate + 1 < half)
        {
            const double yPrev = cmnd[tauEstimate - 1];
            const double y0 = cmnd[tauEstimate];
            const double yNext = cmnd[tauEstimate + 1];
            const double denom = yPrev - 2.0 * y0 + yNext;

            if (std::abs(denom) > 1e-12)
            {
                double offset = 0.5 * (yPrev - yNext) / denom;
                offset = std::clamp(offset, -1.0, 1.0);
                tauRefined += offset;
            }
        }

        if (tauRefined <= 0.0)
            return result;

        // --- Frequency ---
        const double pitch = sampleRate / tauRefined;

        result.valid = true;
        result.pitch = pitch;
        result.confidence = std::clamp(1.0 - cmnd[tauEstimate], 0.0, 1.0);

        return result;
    }

    void YinDetector::reset()
    {
    }

}
