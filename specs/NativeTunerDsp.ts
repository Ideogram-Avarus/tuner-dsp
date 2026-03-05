import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';



export interface Spec extends TurboModule {
  processFrame(buffer: number[]): void;
  getLatestResult(): [number, number, number, number, number];
  init(sampleRate: number | undefined): void;
}

const NativeTuner = TurboModuleRegistry.getEnforcing<Spec>('TunerDsp');

export default NativeTuner;
