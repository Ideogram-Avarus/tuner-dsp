package com.tunerdsp;

@FunctionalInterface
public interface AudioFrameCallback {
    void onAudioFrame(short[] data, int length);
}