import { useTunerResults } from "./tuner/useTunerResults";
import type { SampleRate } from "./types";
import { TunerProcessor } from "./tuner/TunerProcessor";
import { useAudio, usePermissions } from "./audio";
import { SAMPLE_RATE } from "./constants";


export const useTuner = (sampleRate: SampleRate = SAMPLE_RATE) => {
    const {
        requestMicPermission,
        hasPermission
    } = usePermissions();
    
    const {
        processFrame,
        getLatestResult
    } = TunerProcessor(
        sampleRate
    )

    const {
        start,
        stop
    } = useAudio(
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