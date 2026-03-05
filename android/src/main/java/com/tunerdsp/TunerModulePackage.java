package com.tunerdsp;

import androidx.annotation.Nullable;

import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.TurboReactPackage;
import com.facebook.react.module.model.ReactModuleInfo;
import com.facebook.react.module.model.ReactModuleInfoProvider;

import java.util.HashMap;
import java.util.Map;

public class TunerModulePackage extends TurboReactPackage {

    @Override
    public @Nullable NativeModule getModule(String name, ReactApplicationContext context) {
        if (name.equals(TunerModule.NAME)) {
            return new TunerModule(context);
        }
        return null;
    }

    // @Override
    // public ReactModuleInfoProvider getReactModuleInfoProvider() {
    //     return () -> {
    //         Map<String, ReactModuleInfo> map = new HashMap<>();
    //         map.put(
    //             TunerModule.NAME,
    //             new ReactModuleInfo(
    //                 TunerModule.NAME,               // JS-visible name
    //                 TunerModule.class.getName(),    // Full Java class name (with package)
    //                 false,                          // canOverrideExistingModule
    //                 false,                          // needsEagerInit
    //                 false,                          // hasConstants? (change if you add getConstants())
    //                 false,                          // isCxxModule
    //                 true                            // isTurboModule = true
    //             )
    //         );
    //         return map;
    //     };
    // }
}