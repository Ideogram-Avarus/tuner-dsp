

``` bash
Microphone
   ↓
Audio Buffer Accumulation
   ↓
Preprocessing
   • DC removal
   • windowing
   • optional band-pass
   ↓
Pitch Detection (YIN)
   ↓
Confidence evaluation
   ↓
Harmonic correction
   ↓
Temporal smoothing
   ↓
Note detection + hysteresis
   ↓
TunerResult

```


``` bash
shared/
    NativeTunerDsp.cpp
    NativeTunerDsp.h
    TunerJNI.cpp

    tuner/
        tuner_engine.cpp
        tuner_engine.h

        pitch/
            yin_detector.cpp
            yin_detector.h

        dsp/
            window.cpp
            window.h
            dc_filter.cpp
            dc_filter.h

        rms/
            rms_detector.cpp
            rms_detector.h

        smoothing/
            pitch_smoother.cpp
            pitch_smoother.h

```