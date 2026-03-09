package com.tunerdsp;

import androidx.annotation.NonNull;

import com.facebook.proguard.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableArray;


public class TunerDspModule extends NativeTunerDspSpec {

    public static final String NAME = "TunerDsp";

    private final TunerJniEngine engine = new TunerJniEngine();
    private final MicrophoneManager microphoneManager;

    private boolean running = false;

    public TunerDspModule(ReactApplicationContext context) {
        super(context);
        microphoneManager = new MicrophoneManager(context);
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
    public void init(ReadableMap config) {
        engine.init(config, microphoneManager.getSampleRate());
    }

    @Override
    @ReactMethod
    @DoNotStrip
    public void start() {

        if (running) {
            return;
        }

        microphoneManager.start((data, length) -> {
            engine.processFrame(data, length);
        });

        running = true;
    }

    @Override
    @ReactMethod
    @DoNotStrip
    public void stop() {

        if (!running) {
            return;
        }

        microphoneManager.stop();
        running = false;
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
        stop();
        engine.destroyEngine();
    }
    
    @Override
    @ReactMethod
    public void destroy() {
        stop();
        engine.destroyEngine();
    }
}