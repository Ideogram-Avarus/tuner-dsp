
import NativeTuner from './NativeTunerDsp';
import type { TunerResult } from './NativeTunerDsp';





export class TunerEngine {
    private Tuner: typeof NativeTuner;
    private _sampleRate: number | undefined;

    constructor(sampleRate?: number) {
        this.Tuner = NativeTuner;
        this._sampleRate = sampleRate;
    }

    public getLatestResult(): TunerResult {
        return this.Tuner.getLatestResult();
    }

    public processFrame(buffer: number[]): void {
        this.Tuner.processFrame(buffer);
    }
    
    public init(): void {
        this.Tuner.init(this._sampleRate);
    }

    get sampleRate(): number | undefined {
        return this._sampleRate;
    }
}