package com.tunerdsp;

import androidx.annotation.Nullable;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableArray;

import android.util.Base64;

public class TunerJniEngine {
    static {
        System.loadLibrary("tuner");
    }
    private boolean engineCreated = false;
    private float[] sampleBuffer = null;
    private static final float INT16_TO_FLOAT = 1.0f / 32768.0f;

    public void init(@Nullable Double sampleRate) {
        int rate = (sampleRate != null) ? sampleRate.intValue() : 44100;
        if (!engineCreated) {
            cxxCreateEngine(rate);
            engineCreated = true;
        }
    }
    
    public void destroyEngine() {
        if (engineCreated) {
            cxxDestroyEngine();
            engineCreated = false;
        }
    }
    
    public void processFrame(String buffer) {
        if (buffer == null) return;

        byte[] bytes = Base64.decode(buffer, Base64.DEFAULT);
        int len = bytes.length / 2;

        if (sampleBuffer == null || sampleBuffer.length != len) {
            sampleBuffer = new float[len];
        }

        for (int i = 0; i < len; i++) {
            int lo = bytes[i * 2] & 0xff;
            int hi = bytes[i * 2 + 1] << 8;
            short s = (short)(hi | lo);
            sampleBuffer[i] = s * INT16_TO_FLOAT;
        }

        cxxProcessFrame(sampleBuffer);
    }

    public WritableArray getLatestResult() {
        double[] raw = cxxGetLatestResult();
        WritableArray result = Arguments.createArray();
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
    
    private native void cxxCreateEngine(int sampleRate);
    private native void cxxDestroyEngine();
    private native void cxxProcessFrame(float[] samples);
    private native double[] cxxGetLatestResult();
    private native void cxxReset();
}