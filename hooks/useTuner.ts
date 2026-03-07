import { useTunerResults } from "./tuner/useTunerResults";
import { TunerProcessor } from "./tuner/TunerProcessor";
import { useAudio, usePermissions } from "./audio";
import { AUDIO_RECORDER_CONFIG, NATIVE_TUNER_CONFIG } from "./configs";
import type { TunerConfigSpecs } from "../specs";
import type { AudioRecorderConfig } from "./types";

export const useTuner = (
    TunerConfig: TunerConfigSpecs = NATIVE_TUNER_CONFIG,
    AudioConfig: AudioRecorderConfig = AUDIO_RECORDER_CONFIG
) => {
    const {
        requestMicPermission,
        hasPermission
    } = usePermissions();
    
    const {
        processFrame,
        getLatestResult
    } = TunerProcessor(
        TunerConfig
    )

    const {
        start,
        stop
    } = useAudio(
        AudioConfig,
        hasPermission,
        requestMicPermission, 
        processFrame
    )

    const {
        result
    } = useTunerResults(
        getLatestResult,
        50
    );

    return {
        start,
        stop,
        result,
        hasPermission,
        requestMicPermission,
    }
}