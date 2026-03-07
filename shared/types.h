#pragma once


struct PitchResult
{
    bool valid;
    double pitch;
    double confidence;
};

struct TunerResult
{
    bool hasPitch;
    double frequency;
    int midiNote;
    double cents;
    double amplitude;
    double confidence;
};

struct TunerConfig
{
    double sampleRate;

    int windowSize; // Size of the data we will be analizing
    int hopSize; //
    
    double minFrequency;
    double maxFrequency;

    double yinThreshold;
    double minConfidence;

    double minRMS;
    double smoothingFactor;

    double noteHysteresisCents;

    bool enableInterpolation;
    bool enableHarmonicCorrection;

    bool removeDC;
};
