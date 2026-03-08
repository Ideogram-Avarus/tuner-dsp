import type { TunerConfigSpecs } from "../specs"
import type { TunerEngineConfig } from "./types"

export const NATIVE_TUNER_CONFIG: TunerConfigSpecs = {
  windowSize: 4096,
  hopSize: 512,
  minFrequency: 70,
  maxFrequency: 1200,
  yinThreshold: 0.15,
  minConfidence: 0.8,
  minRMS: 0.001,
  smoothingFactor: 0.2,
  noteHysteresisCents: 50,
  enableInterpolation: true,
  enableHarmonicCorrection: true,
  removeDC: true,
}


export const DEFAULT_CONFIG: TunerEngineConfig = {
  engineConfig: NATIVE_TUNER_CONFIG,
  startAtPermission: true
}