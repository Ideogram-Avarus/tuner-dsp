


export const DefaultConfigs = {
  sampleRate: 48000,
  windowSize: 2048,
  hopSize: 512,

  minFrequency: 50,
  maxFrequency: 2000,

  yinThreshold: 0.15,
  minConfidence: 0.8,

  minRMS: 0.01,
  smoothingFactor: 0.2,

  noteHysteresisCents: 10,

  enableInterpolation: true,
  enableHarmonicCorrection: true,
  removeDC: true,
};