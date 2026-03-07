#pragma once

#include <vector>

#include "pitch/yin_detector.h"
#include "smoothing/pitch_smoother.h"
#include "dsp/dc_filter.h"
#include "dsp/window.h"
#include "rms/rms_detector.h"

#include "../types.h"

namespace tuner
{
    class CxxTunerEngine
    {
    public:
        explicit CxxTunerEngine(TunerConfig config);

        void processFrame(const float* samples, int size); //Acumulate audio buffer, call processSamples when buffer is full 
        void processSamples(); //Process samples and update latest
        TunerResult getLatestResult() const;
        void reset();


    private:
        TunerConfig config;
        TunerResult latest;


        std::vector<float> internalBuffer;
        std::vector<float> analysisFrame;

    
        dsp::DcFilter dcFilter;
        dsp::Window window;
        pitch::YinDetector detector;
        smoothing::PitchSmoother smoother;
        rms::RmsDetector rmsDetector;
    };
}