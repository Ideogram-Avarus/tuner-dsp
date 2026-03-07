import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';
import type { TunerConfigSpecs } from './types';




export interface Spec extends TurboModule {
  processFrame(buffer: string): void;
  getLatestResult(): number[];
  init(
    config: TunerConfigSpecs
  ): void;
  reset(): void;
  destroy(): void;
}


const NativeTuner = TurboModuleRegistry.getEnforcing<Spec>('TunerDsp');

export default NativeTuner;
