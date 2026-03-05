#include "tuner_engine.h"
#include <cmath>
#include <algorithm>

namespace tuner {

CxxTunerEngine::CxxTunerEngine(int sampleRate)
    : sampleRate(sampleRate),
      detector(sampleRate)
{
    reset();
}

void CxxTunerEngine::processFrame(const float* samples, int size)
{
    internalBuffer.insert(
        internalBuffer.end(),
        samples,
        samples + size
    );

    const int requiredSize = 4096;

    if (internalBuffer.size() < requiredSize)
        return;

    std::vector<float> window(
        internalBuffer.end() - requiredSize,
        internalBuffer.end()
    );

    double frequency = detector.detect(window);

    double sum = 0.0;
    for (float s : window)
        sum += s * s;

    double rms = std::sqrt(sum / window.size());

    if (frequency <= 0.0 || rms < 0.001) {
        latest.hasPitch = false;
        return;
    }

    double midiFloat = 69.0 + 12.0 * std::log2(frequency / 440.0);
    int midi = static_cast<int>(std::round(midiFloat));

    double cents = 100.0 * (midiFloat - midi);

    latest.hasPitch = true;
    latest.frequency = frequency;
    latest.midiNote = midi;
    latest.cents = cents;
    latest.amplitude = rms;

    const int maxBuffer = requiredSize * 2;

    if (internalBuffer.size() > maxBuffer) {
        internalBuffer.erase(
            internalBuffer.begin(),
            internalBuffer.end() - requiredSize
        );
    }
}

TunerResult CxxTunerEngine::getLatestResult() const
{
    return latest;
}

void CxxTunerEngine::reset()
{
    internalBuffer.clear();

    latest.hasPitch = false;
    latest.frequency = 0.0;
    latest.midiNote = 0;
    latest.cents = 0.0;
    latest.amplitude = 0.0;
}

}