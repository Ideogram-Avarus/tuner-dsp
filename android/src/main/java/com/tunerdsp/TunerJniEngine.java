package com.tunerdsp;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.ReadableMap;

public class TunerJniEngine {
    static {
        System.loadLibrary("tuner");
    }
    private boolean engineCreated = false;
    private float[] sampleBuffer = null;
    private static final float INT16_TO_FLOAT = 1.0f / 32768.0f;

    public void init(ReadableMap config, int sampleRate) {
        if (engineCreated) return;

        int windowSize = config.getInt("windowSize");
        int hopSize = config.getInt("hopSize");

        double minFrequency = config.getDouble("minFrequency");
        double maxFrequency = config.getDouble("maxFrequency");

        double yinThreshold = config.getDouble("yinThreshold");
        double minConfidence = config.getDouble("minConfidence");

        double minRMS = config.getDouble("minRMS");
        double smoothingFactor = config.getDouble("smoothingFactor");

        double noteHysteresisCents = config.getDouble("noteHysteresisCents");

        boolean enableInterpolation = config.getBoolean("enableInterpolation");
        boolean enableHarmonicCorrection = config.getBoolean("enableHarmonicCorrection");
        boolean removeDC = config.getBoolean("removeDC");

        cxxCreateEngine(
            sampleRate,
            windowSize,
            hopSize,
            minFrequency,
            maxFrequency,
            yinThreshold,
            minConfidence,
            minRMS,
            smoothingFactor,
            noteHysteresisCents,
            enableInterpolation,
            enableHarmonicCorrection,
            removeDC
        );

        engineCreated = true;
    }

    public void destroyEngine() {
        if (engineCreated) {
            cxxDestroyEngine();
            engineCreated = false;
        }
    }

    public void processFrame(short[] buffer, int length) {
        if (sampleBuffer == null || sampleBuffer.length < length) {
            sampleBuffer = new float[length];
        }
        for (int i = 0; i < length; i++) {
            sampleBuffer[i] = buffer[i] * INT16_TO_FLOAT;
        }
        cxxProcessFrame(sampleBuffer, length);
    }

    public WritableArray getLatestResult() {
        double[] raw = cxxGetLatestResult();
        WritableArray result = Arguments.createArray();
        if (raw == null) {
            // fallback when engine is unavailable
            for (int i = 0; i < 6; i++) {
                result.pushDouble(0);
            }
            return result;
        }

        for (double val : raw) {
            result.pushDouble(val);
        }
        
        return result;
    }

    public void reset() {
        cxxReset();
    }

    // -----------------------
    // Native methods
    // -----------------------

    private native void cxxCreateEngine(
            int sampleRate,
            int windowSize,
            int hopSize,
            double minFrequency,
            double maxFrequency,
            double yinThreshold,
            double minConfidence,
            double minRMS,
            double smoothingFactor,
            double noteHysteresisCents,
            boolean enableInterpolation,
            boolean enableHarmonicCorrection,
            boolean removeDC);

    private native void cxxDestroyEngine();

    private native void cxxProcessFrame(float[] samples, int length);

    private native double[] cxxGetLatestResult();

    private native void cxxReset();
}