import { useTunerResults } from "./tuner/useTunerResults";
import { TunerProcessor } from "./tuner/TunerProcessor";
import { usePermissions } from "./audio";
import { DEFAULT_CONFIG } from "./configs";
import type { TunerEngineConfig } from "./types";

export const useTuner = (
    config: TunerEngineConfig = DEFAULT_CONFIG,
) => {
    const {
        requestMicPermission,
        hasPermission
    } = usePermissions();
    
    const {
        start,
        stop,
        isRunning,
        getLatestResult
    } = TunerProcessor(
        config.engineConfig
    )

    const {
        result
    } = useTunerResults(
        getLatestResult,
        50
    );

    return {
        isRunning,
        start,
        stop,
        result,
        hasPermission,
        requestMicPermission,
    }
}