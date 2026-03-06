package com.tunerdsp;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.proguard.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.turbomodule.core.interfaces.TurboModule;


public class TunerDspModule extends NativeTunerDspSpec {

    public static final String NAME = "TunerDsp";

    private final TunerJniEngine engine = new TunerJniEngine();

    public TunerDspModule(ReactApplicationContext context) {
        super(context);
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
        engine.init(sampleRate);
    }

    @Override
    @ReactMethod
    @DoNotStrip
    public void processFrame(String buffer) {
        engine.processFrame(buffer);
    }


    @Override
    @ReactMethod(isBlockingSynchronousMethod = true)
    @DoNotStrip
    public WritableArray getLatestResult() {
        return engine.getLatestResult();
    }


    @Override
    @ReactMethod
    public void reset() {
        engine.reset();
    }

    @Override
    public void invalidate() {
        engine.destroyEngine();
    }
    
    @Override
    @ReactMethod
    public void destroy() {
        engine.destroyEngine();
    }
}