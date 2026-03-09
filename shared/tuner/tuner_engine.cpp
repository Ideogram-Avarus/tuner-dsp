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

    void CxxTunerEngine::setLatest(const TunerResult& result)
    {
        std::lock_guard<std::mutex> lock(latestMutex);
        latest = result;
    }

    TunerResult CxxTunerEngine::getLatestResult() const
    {
        std::lock_guard<std::mutex> lock(latestMutex);
        return latest;
    }

    void CxxTunerEngine::reset()
    {
        internalBuffer.clear();
        bufferStart = 0;
        dcFilter.reset();
        detector.reset();
        smoother.reset();
        hasStableMidiNote = false;

        TunerResult result{};
        result.hasPitch = false;
        setLatest(result);
    }


    void CxxTunerEngine::processFrame(const float *samples, int size)
    {
        if (size <= 0)
            return;

        internalBuffer.insert(
            internalBuffer.end(),
            samples,
            samples + size);

        while (internalBuffer.size() - bufferStart >= static_cast<std::size_t>(config.windowSize))
        {
            processSamples();
            bufferStart += static_cast<std::size_t>(config.hopSize);
        }

        // Compact occasionally to avoid O(n) erase on every hop.
        // This keeps steady-state processing close to O(1) per frame append.
        if (bufferStart > 0 &&
            (bufferStart >= internalBuffer.size() / 2 ||
             bufferStart >= static_cast<std::size_t>(config.windowSize) * 4))
        {
            internalBuffer.erase(
                internalBuffer.begin(), 
                internalBuffer.begin() + bufferStart
            );
            bufferStart = 0;
        }
    }

    void CxxTunerEngine::processSamples()
    {
        const std::size_t start = bufferStart;

        std::copy(
            internalBuffer.begin() + static_cast<std::ptrdiff_t>(start),
            internalBuffer.begin() + static_cast<std::ptrdiff_t>(start + static_cast<std::size_t>(config.windowSize)),
            analysisFrame.begin());

        // ---------- Preprocessing ----------

        if (config.removeDC)
            dcFilter.process(analysisFrame.data(), analysisFrame.size());

        window.apply(analysisFrame.data(), analysisFrame.size());

        double rms = rmsDetector.process(analysisFrame.data(), analysisFrame.size());

        if (rms < config.minRMS)
        {
            hasStableMidiNote = false;
            TunerResult result{};
            result.hasPitch = false;
            setLatest(result);
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
            hasStableMidiNote = false;
            TunerResult result{};
            result.hasPitch = false;
            setLatest(result);
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

        auto freqFromMidi = [](int midi)
        {
            return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
        };

        auto midiFromFreq = [](double freq)
        {
            return static_cast<int>(
                std::lround(69.0 + 12.0 * std::log2(freq / 440.0)));
        };

        if (!hasStableMidiNote)
        {
            stableMidiNote = midiFromFreq(pitch);
            hasStableMidiNote = true;
        }

        double centsToStable =
            1200.0 * std::log2(pitch / freqFromMidi(stableMidiNote));

        while (centsToStable > config.noteHysteresisCents)
        {
            ++stableMidiNote;
            centsToStable =
                1200.0 * std::log2(pitch / freqFromMidi(stableMidiNote));
        }

        while (centsToStable < -config.noteHysteresisCents)
        {
            --stableMidiNote;
            centsToStable =
                1200.0 * std::log2(pitch / freqFromMidi(stableMidiNote));
        }

        const int midi = stableMidiNote;

        const double referenceFreq = freqFromMidi(midi);

        const double cents =
            1200.0 * std::log2(pitch / referenceFreq);

        // ---------- Result ----------

        TunerResult result;

        result.hasPitch = true;
        result.frequency = pitch;
        result.midiNote = midi;
        result.cents = cents;
        result.amplitude = rms;
        result.confidence = pitchResult.confidence;

        setLatest(result);
    }

}
