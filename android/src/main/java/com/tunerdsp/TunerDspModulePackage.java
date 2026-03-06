package com.tunerdsp;

import androidx.annotation.Nullable;

import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.TurboReactPackage;
import com.facebook.react.module.model.ReactModuleInfo;
import com.facebook.react.module.model.ReactModuleInfoProvider;

import java.util.HashMap;
import java.util.Map;

public class TunerDspModulePackage extends TurboReactPackage {

    @Override
    public @Nullable NativeModule getModule(String name, ReactApplicationContext context) {
        android.util.Log.d("TunerDebug", "getModule called with name: " + name);
        if (name.equals(TunerDspModule.NAME)) {
            android.util.Log.d("TunerDebug", "Instantiating TunerDsp TurboModule");
            return new TunerDspModule(context);
        }
        return null;
    }

    @Override
    public ReactModuleInfoProvider getReactModuleInfoProvider() {
        return () -> {
            Map<String, ReactModuleInfo> map = new HashMap<>();
            map.put(
                TunerDspModule.NAME,
                new ReactModuleInfo(
                    TunerDspModule.NAME,               // JS-visible name
                    TunerDspModule.class.getName(),    // Full Java class name (with package)
                    false,                          // canOverrideExistingModule
                    true,                           // needsEagerInit
                    false,                          // isCxxModule
                    true                            // isTurboModule = true
                )
            );
            return map;
        };
    }
}