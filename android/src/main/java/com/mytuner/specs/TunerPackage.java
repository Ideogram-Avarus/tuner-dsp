package com.mytuner;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.mytuner.specs.NativeTunerModule;
import com.mytuner.specs.NativeTunerSpec;

import java.util.Collections;
import java.util.List;

public class TunerPackage implements ReactPackage {

  @Override
  public List<NativeModule> createNativeModules(
      ReactApplicationContext reactContext) {
    return Collections.emptyList(); // New Architecture
  }

  @Override
  public NativeModule getModule(
      String name,
      ReactApplicationContext reactContext) {

    if (name.equals(NativeTunerSpec.NAME)) {
      return new NativeTunerModule(reactContext);
    }

    return null;
  }
}