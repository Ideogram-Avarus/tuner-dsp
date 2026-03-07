import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';


export type TunerConfigSpecs = {
    sampleRate: number,

    windowSize: number,
    hopSize: number,
    
    minFrequency: number,
    maxFrequency: number,

    yinThreshold: number,
    minConfidence: number,

    minRMS: number,
    smoothingFactor: number,

    noteHysteresisCents: number,

    enableInterpolation: boolean,
    enableHarmonicCorrection: boolean,

    removeDC: boolean
}

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
