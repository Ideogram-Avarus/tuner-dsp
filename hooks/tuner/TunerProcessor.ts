import { useCallback, useEffect, useRef } from "react";
import { TunerEngine } from "../../specs";
import type { TunerResult } from "../../specs";
import type { SampleRate } from "../types";

export const TunerProcessor = (sampleRate: SampleRate) => {
    const engineRef = useRef<any | null>(null);

    useEffect(() => {
        if (!TunerEngine) {
            throw new Error("TunerEngine is not installed");
        }
        console.log("Creating TunerEngine");
        engineRef.current = new TunerEngine();
        engineRef.current.init(sampleRate);
        console.log("TunerEngine Created");
        console.log(engineRef.current);
        return () => {
            engineRef.current.destroy();
            engineRef.current = null;
        };
    }, [sampleRate]);

    const processFrame = useCallback((data: string) => {
        engineRef.current.processFrame(data);
    }, [engineRef.current, sampleRate]);

    const getLatestResult = useCallback((): TunerResult | null => {
        return engineRef.current.getLatestResult();
    }, []);

    return {
        engineRef,
        processFrame,
        getLatestResult
    };
};