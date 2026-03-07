#include "tuner_engine.h"
#include <cmath>


namespace tuner
{

    CxxTunerEngine::CxxTunerEngine(TunerConfig cfg)
        : config(cfg),
          internalBuffer(),
          analysisFrame(cfg.windowSize, 0.0),
          detector(cfg),
          smoother(cfg.smoothingFactor),
          rmsDetector(cfg.windowSize),
          window(static_cast<std::size_t>(cfg.windowSize))
    {
        reset();
    }

    void CxxTunerEngine::reset()
    {
        internalBuffer.clear();

        latest.hasPitch = false;
        latest.frequency = 0.0;
        latest.midiNote = 0;
        latest.cents = 0.0;
        latest.amplitude = 0.0;
        latest.confidence = 0.0;
    }

    TunerResult CxxTunerEngine::getLatestResult() const
    {
        return latest;
    }

    void CxxTunerEngine::processFrame(const float *samples, int size)
    {
        internalBuffer.insert(
            internalBuffer.end(),
            samples,
            samples + size);

        while (internalBuffer.size() >= config.windowSize)
        {
            processSamples();

            internalBuffer.erase(
                internalBuffer.begin(),
                internalBuffer.begin() + config.hopSize);
        }
    }

    void CxxTunerEngine::processSamples()
    {
        std::copy(
            internalBuffer.begin(),
            internalBuffer.begin() + config.windowSize,
            analysisFrame.begin()
        );

        // ---------- Preprocessing ----------

        if (config.removeDC)
            dcFilter.process(analysisFrame.data(), analysisFrame.size());

        window.apply(analysisFrame.data(), analysisFrame.size());

        double rms = rmsDetector.process(analysisFrame.data(), analysisFrame.size());

        if (rms < config.minRMS)
        {
            latest.hasPitch = false;
            return;
        }

        // ---------- Pitch detection ----------

        auto pitchResult = detector.detect(
            analysisFrame.data(),
            config.windowSize,
            config.yinThreshold,
            config.enableInterpolation);

        if (!pitchResult.valid || pitchResult.confidence < config.minConfidence)
        {
            latest = {};
            return;
        }

        double pitch = pitchResult.pitch;

        // ---------- Harmonic correction ----------

        if (config.enableHarmonicCorrection)
        {
            if (pitch > config.maxFrequency)
                pitch *= 0.5;

            if (pitch < config.minFrequency)
                pitch *= 2.0;
        }

        // ---------- Temporal smoothing ----------

        pitch = smoother.process(pitch);

        // ---------- Note calculation ----------

        int midi = static_cast<int>(std::round(
            69.0 + 12.0 * std::log2(pitch / 440.0)));

        double referenceFreq =
            440.0 * std::pow(2.0, (midi - 69) / 12.0);

        double cents =
            1200.0 * std::log2(pitch / referenceFreq);

        // ---------- Result ----------

        TunerResult result;

        result.hasPitch = true;
        result.frequency = pitch;
        result.midiNote = midi;
        result.cents = cents;
        result.amplitude = rms;
        result.confidence = pitchResult.confidence;

        latest = result;
    }

}
