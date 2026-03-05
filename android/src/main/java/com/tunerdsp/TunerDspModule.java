package com.tunerdsp;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.yoga.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.turbomodule.core.interfaces.TurboModule;

import androidx.annotation.NonNull;

public class TunerDspModule extends NativeTunerDspSpec implements TurboModule {

    public static final String NAME = "TunerDsp";
    private boolean engineCreated = false;

    static {
        System.loadLibrary("tuner");
    }

    public TunerDspModule(ReactApplicationContext context) {
        super(context);
    }

    @Override
    public void invalidate() {
        destroyEngine();
    }

    @NonNull
    @Override
    public String getName() {
        return NAME;
    }

    
    // -----------------------
    // JS-facing methods
    // -----------------------
    @Override
    @ReactMethod
    @DoNotStrip
    public void init(@Nullable Double sampleRate) {
        int rate = (sampleRate != null) ? sampleRate.intValue() : 44100;
        if (!engineCreated) {
            createEngine(rate);
            engineCreated = true;
        }
    }

    @Override
    @ReactMethod
    @DoNotStrip
    public void processFrame(ReadableArray buffer) {
        if (buffer == null) return;
        float[] samples = new float[buffer.size()];
        for (int i = 0; i < buffer.size(); i++) {
            samples[i] = (float) buffer.getDouble(i);  // JS numbers → double → float
        }
        cxxProcessFrame(samples);
    }

    
    @Override
    @ReactMethod(isBlockingSynchronousMethod = true)
    @DoNotStrip
    public WritableArray getLatestResult() {
        double[] raw = cxxGetLatestResult();

        WritableArray result = Arguments.createArray();
        for (double val : raw) {
            result.pushDouble(val);
        }
        return result;
    }

    @Override
    @ReactMethod
    @DoNotStrip
    public void reset() {
        cxxReset();
    }
    
    @Override
    @ReactMethod
    @DoNotStrip
    public void destroy() {
        destroyEngine();
        engineCreated = false;
    }

    // -----------------------
    // JNI wrapper methods
    // -----------------------
    private native void createEngine(int sampleRate);
    private native void destroyEngine();
    private native void cxxProcessFrame(float[] samples);
    private native double[] cxxGetLatestResult();
    private native void cxxReset();



}