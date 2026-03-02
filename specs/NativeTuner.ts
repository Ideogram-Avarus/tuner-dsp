import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
}

export interface Spec extends TurboModule {
  processFrame(buffer: number[]): void;
  getLatestResult(): TunerResult;
}

const NativeTuner = TurboModuleRegistry.getEnforcing<Spec>('TunerEngine');

export default NativeTuner;
