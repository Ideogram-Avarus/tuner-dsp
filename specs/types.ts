

export interface TunerResult {
  hasPitch: boolean;
  frequency: number;
  midiNote: number;
  cents: number;
  amplitude: number;
}

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