package com.tunerdsp;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.turbomodule.core.interfaces.TurboModule;
import androidx.annotation.NonNull;

public class TunerModule extends ReactContextBaseJavaModule implements TurboModule {

    public static final String NAME = "TunerDsp";
    private boolean engineCreated = false;

    static {
        System.loadLibrary("tuner"); // loads libtunerdsp.so
    }

    public TunerModule(ReactApplicationContext context) {
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
    public void init() {
        if (!engineCreated) {
            init(44100);
            engineCreated = true;
        }
    }

    public void init(int sampleRate) {
        if (!engineCreated) {
            createEngine(sampleRate);
            engineCreated = true;
        }
    }

    public float getLatestResult() {
        return cxxGetLatestResult();
    }

    public void processFrame(float[] samples) {
        cxxProcessFrame(samples);
    }
    

    // -----------------------
    // JNI wrapper methods
    // -----------------------
    private native void createEngine(int sampleRate);
    private native void destroyEngine();
    private native void cxxProcessFrame(float[] samples);
    private native float cxxGetLatestResult();
    private native void cxxReset();


}