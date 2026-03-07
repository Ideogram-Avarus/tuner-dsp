import { useCallback, useEffect, useRef } from "react";
import { TunerEngine } from "../../specs";
import type { TunerConfigSpecs, TunerResult } from "../../specs";

export const TunerProcessor = (config: TunerConfigSpecs) => {
    const engineRef = useRef<any | null>(null);

    useEffect(() => {
        if (!TunerEngine) {
            throw new Error("TunerEngine is not installed");
        }
        console.log("Creating TunerEngine");
        engineRef.current = new TunerEngine(config);
        engineRef.current.init();
        console.log("TunerEngine Created");
        console.log(engineRef.current);
        return () => {
            engineRef.current.destroy();
            engineRef.current = null;
        };
    }, [config]);

    const processFrame = useCallback((data: string) => {
        engineRef.current.processFrame(data);
    }, [engineRef.current, config]);

    const getLatestResult = useCallback((): TunerResult | null => {
        return engineRef.current.getLatestResult();
    }, []);

    return {
        engineRef,
        processFrame,
        getLatestResult
    };
};