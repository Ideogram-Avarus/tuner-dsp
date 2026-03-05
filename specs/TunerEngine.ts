
import { TurboModuleRegistry } from 'react-native';
import type { Spec } from './NativeTunerDsp';


export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
}

type RawTunerResult = [number, number, number, number, number];


export class TunerEngine {
    private Tuner: Spec | undefined | null;
    private _sampleRate: number | undefined;

    constructor(sampleRate?: number) {
        this._sampleRate = sampleRate;
    }

    public getNativeTuner(): void {
        this.Tuner = TurboModuleRegistry.get<Spec>('TunerDsp');
    }

    public getLatestResult(): TunerResult {
        if (!this.Tuner) throw new Error('No tuner');

        const result = this.Tuner.getLatestResult();
        if (result.length !== 5) throw new Error('Invalid result');
        const typed = result as RawTunerResult;
        
        return {
            hasPitch: typed[0] === 1.0,
            frequency: typed[1],
            midiNote: typed[3],
            cents: typed[2],
            amplitude: typed[4],
        }
    }

    public processFrame(buffer: number[]): void {
        if (!this.Tuner) throw new Error('No tuner');

        this.Tuner.processFrame(buffer);
    }
    
    public init(): void {
        if (!this.Tuner) throw new Error('No tuner');

        this.Tuner.init(this._sampleRate);
    }

    get sampleRate(): number | undefined {
        return this._sampleRate;
    }
}