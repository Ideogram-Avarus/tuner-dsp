import { useTunerResults } from "./tuner/useTunerResults";
import type { TunerConfig } from "./types";
import { TunerProcessor } from "./tuner/TunerProcessor";
import { useAudio, usePermissions } from "./audio";
import { AUDIO_RECORDER_CONFIG } from "./constants";

export const useTuner = (
    config: TunerConfig = AUDIO_RECORDER_CONFIG
) => {
    const {
        requestMicPermission,
        hasPermission
    } = usePermissions();
    
    const {
        processFrame,
        getLatestResult
    } = TunerProcessor(
        config.sampleRate
    )

    const {
        start,
        stop
    } = useAudio(
        config,
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