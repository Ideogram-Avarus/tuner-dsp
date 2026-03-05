package com.tunerdsp;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableArray;
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
    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray getLatestResult() {
        return cxxGetLatestResult();
    }

    @Override
    @ReactMethod
    public void processFrame(float[] samples) {
        cxxProcessFrame(samples);
    }

    @Override
    @ReactMethod
    public void reset() {
        cxxReset();
    }
    
    @Override
    @ReactMethod
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