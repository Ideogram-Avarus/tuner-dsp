
import NativeTuner from './NativeTunerDsp';
import type { TunerResult } from './NativeTunerDsp';





export class TunerEngine {
    static getLatestResult(): TunerResult {
        return NativeTuner.getLatestResult();
    }
    static processFrame(buffer: number[]): void {
        NativeTuner.processFrame(buffer);
    }
}