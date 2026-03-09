import NativeTuner from './NativeTunerDsp';
import type { TunerResult } from './types';
import type { TunerConfigSpecs } from './NativeTunerDsp';

export class TunerEngine {
    private Tuner: typeof NativeTuner;
    public config: TunerConfigSpecs;
    public isRunning: boolean = false;

    constructor(config: TunerConfigSpecs) {
        this.config = config;
        this.Tuner = NativeTuner;
    }

    public getLatestResult(): TunerResult {
        const result = this.Tuner.getLatestResult();
        if (result.length !== 6) throw new Error('Invalid result');
        const typed = result as [number, number, number, number, number, number];
        
        return {
            hasPitch: typed[0] === 1.0,
            frequency: typed[1],
            midiNote: typed[3],
            cents: typed[2],
            amplitude: typed[4],
            confidence: typed[5]
        }
    }

    public start(): void {
        this.Tuner.start();
        this.isRunning = true;
    }

    public stop(): void {
        this.Tuner.stop();
        this.isRunning = false;
    }
    
    public init(): void {
        this.Tuner.init(this.config);
    }

    public destroy(): void {
        this.Tuner.destroy();
    }
}