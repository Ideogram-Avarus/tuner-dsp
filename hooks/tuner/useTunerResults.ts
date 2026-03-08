import { useEffect, useRef, useState } from "react";
import type { TunerResult } from "../../specs";

export const useTunerResults = (
    getLatestResult: () => TunerResult | null,
    interval: number
) => {
    const [result, setResult] = useState<TunerResult | null>(null);
    const lastResultRef = useRef<TunerResult | null>(null);

    useEffect(() => {
        const id = setInterval(() => {
            const next = getLatestResult();
            if (next === null) return;

            if (!next.hasPitch) {
                setResult(prev => {
                    if (!prev) return { ...next, hasPitch: false };
                    return { ...prev, hasPitch: false };
                });
                return
            }
            
            if (next !== lastResultRef.current) {
                    lastResultRef.current = next;
                    setResult(next);
            }
        }, interval);

        return () => clearInterval(id);
    }, [getLatestResult, interval]);

    return { result };
};