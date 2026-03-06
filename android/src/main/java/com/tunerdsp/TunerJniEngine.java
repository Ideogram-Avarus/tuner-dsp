package com.tunerdsp;

import androidx.annotation.Nullable;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.ReadableArray;

public class TunerJniEngine {
    static {
        System.loadLibrary("tuner");
    }

    private boolean engineCreated = false;
    
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
    
    public void processFrame(ReadableArray samples) {
        // if (buffer == null) {
        //     return;
        // }
        // float[] samples = new float[buffer.size()];
        // for (int i = 0; i < buffer.size(); i++) {
        //     samples[i] = (float) buffer.getDouble(i);  // Convert JS number to float
        // }
        // cxxProcessFrame(samples);
    }

    public WritableArray getLatestResult() {
        // double[] raw = cxxGetLatestResult();
        // WritableArray result = Arguments.createArray();
        // for (double val : raw) {
        //     result.pushDouble(val);
        // }
        // return result;
        WritableArray arr = Arguments.createArray();
        arr.pushDouble(1);
        arr.pushDouble(2);
        arr.pushDouble(3);
        arr.pushDouble(4);
        arr.pushDouble(5);
        return arr;
    }

    public void reset() {
        //cxxReset();
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