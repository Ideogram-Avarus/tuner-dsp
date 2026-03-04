package com.tunerdsp;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.turbomodule.core.interfaces.TurboModule;
import androidx.annotation.NonNull;

public class TunerModule extends ReactContextBaseJavaModule implements TurboModule {
    static {
        System.loadLibrary("tunerdsp"); // loads libtunerdsp.so
    }

    public TunerModule(ReactApplicationContext context) {
        super(context);
        createEngine(44100); // example sample rate
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
    // JNI wrapper methods
    // -----------------------
    private native void createEngine(int sampleRate);
    private native void destroyEngine();
    private native void cxxProcessFrame(float[] samples);
    private native float cxxGetLatestResult();

    // -----------------------
    // JS-facing methods
    // -----------------------
    public float getLatestResult() {
        return cxxGetLatestResult();
    }

    public void processFrame(float[] samples) {
        cxxProcessFrame(samples);
    }
}