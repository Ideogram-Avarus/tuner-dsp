import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';



export interface Spec extends TurboModule {
  processFrame(buffer: string): void;
  getLatestResult(): number[];
  init(sampleRate: number | undefined): void;
  reset(): void;
  destroy(): void;
}


const NativeTuner = TurboModuleRegistry.getEnforcing<Spec>('TunerDsp');

export default NativeTuner;
