
import NativeTuner from './NativeTunerDsp';


export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
}



export class TunerEngine {
    private Tuner: typeof NativeTuner;
    private _sampleRate: number | undefined;

    constructor(sampleRate?: number) {
        this.Tuner = NativeTuner;
        this._sampleRate = sampleRate;
    }

    public getLatestResult(): TunerResult {
        const result = this.Tuner.getLatestResult();
        return {
            hasPitch: result[0] === 1.0,
            frequency: result[1],
            midiNote: result[3],
            cents: result[2],
            amplitude: result[4],
        }
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