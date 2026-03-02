


import com.facebook.react.turbomodule.core.interfaces.TurboModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

public abstract class NativeTunerSpec extends TurboModule {
    public NativeTunerSpec(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    public abstract void processFrame(double[] buffer);
    public abstract WritableMap getLatestResult();
}