import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';



export interface Spec extends TurboModule {
  processFrame(buffer: number[]): void;
  getLatestResult(): number[];
  init(sampleRate: number | undefined): void;
}



