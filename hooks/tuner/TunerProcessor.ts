import { useCallback, useEffect, useRef } from "react";
import { TunerEngine } from "../../specs";
import type { TunerConfigSpecs, TunerResult } from "../../specs";

export const TunerProcessor = (config: TunerConfigSpecs) => {
    const engineRef = useRef<TunerEngine | null>(null);

    const getLatestResult = useCallback((): TunerResult | null => {
        if (!engineRef.current) return null;
        return engineRef.current.getLatestResult();
    }, []);

    const start = useCallback(() => {
        if (!engineRef.current) return;
        engineRef.current.start();
    }, []);

    const stop = useCallback(() => {
        if (!engineRef.current) return;
        engineRef.current.stop();
    }, []);

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
            if (!engineRef.current) return;
            engineRef.current.destroy();
            engineRef.current = null;
        };
    }, [config]);

    return {
        start,
        stop,
        getLatestResult
    };
};