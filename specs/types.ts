

export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
  confidence: number;
}

export type { TunerConfigSpecs } from './NativeTunerDsp';
