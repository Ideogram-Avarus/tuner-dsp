package com.tunerdsp;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.MediaRecorder;

public class MicrophoneManager {

    private final int sampleRate;
    private final int channelConfig = AudioFormat.CHANNEL_IN_MONO;
    private final int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
    
    private int bufferSize;
    private AudioRecord recorder;
    private volatile boolean running = false;

    public MicrophoneManager(Context context) {
        AudioManager audioManager =
            (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
            
        String rate = audioManager.getProperty(
            AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE
        );
        if (rate != null) {
            sampleRate = Integer.parseInt(rate);
        } else {
            sampleRate = 48000;
        }
        bufferSize = AudioRecord.getMinBufferSize(
            sampleRate,
            channelConfig,
            audioFormat
        );
    }

    private void captureLoop(AudioFrameCallback callback) {
        short[] buffer = new short[bufferSize];
        android.os.Process.setThreadPriority(
            android.os.Process.THREAD_PRIORITY_AUDIO
        );
        while (running) {
            AudioRecord r = recorder;
            if (r == null) {
                running = false;
                break;
            }
            int read = recorder.read(buffer, 0, buffer.length);
            if (read > 0 && callback != null) {
                callback.onAudioFrame(buffer, read);
            }
        }
    }

    public void start(AudioFrameCallback callback) {
        recorder = new AudioRecord(
            MediaRecorder.AudioSource.MIC,
            sampleRate,
            channelConfig,
            audioFormat,
            bufferSize
        );
        running = true;
        recorder.startRecording();
        Thread t = new Thread(() -> captureLoop(callback), "TunerMicThread");
        t.start();
    }

    public void stop() {
        running = false;
        if (recorder != null) {
            try {
                recorder.stop();
            } catch (IllegalStateException ignored) {}
            recorder.release();
            recorder = null;
        }
    }

    public int getSampleRate() {
        return sampleRate;
    }

    public int getBufferSize() {
        return bufferSize;
    }
    
}