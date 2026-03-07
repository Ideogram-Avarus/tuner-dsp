



export const SAMPLE_RATE = 44100

export const AUDIO_RECORDER_CONFIG = {
    sampleRate: SAMPLE_RATE,
    channels: 1,
    bitsPerSample: 16,
    audioSource: 6,
    wavFile: "ignore.wav",
}


export const NATIVE_TUNER_CONFIG = {
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
  windowType: "hann"
}