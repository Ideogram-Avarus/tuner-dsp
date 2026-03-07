

export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
}

export type { TunerConfigSpecs } from './NativeTunerDsp';
