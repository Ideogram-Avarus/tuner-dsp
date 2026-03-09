import type { TunerResult } from "specs";



const CENTS_EPS = 0.1;
const FREQ_EPS = 0.01;
const AMP_EPS = 0.001;
const CONF_EPS = 0.001;

export function resultsDifferent(a: TunerResult, b: TunerResult) {
  if (a.hasPitch !== b.hasPitch) return true;
  if (a.midiNote !== b.midiNote) return true;

  if (Math.abs(a.cents - b.cents) > CENTS_EPS) return true;
  if (Math.abs(a.frequency - b.frequency) > FREQ_EPS) return true;
  if (Math.abs(a.amplitude - b.amplitude) > AMP_EPS) return true;
  if (Math.abs(a.confidence - b.confidence) > CONF_EPS) return true;

  return false;
}