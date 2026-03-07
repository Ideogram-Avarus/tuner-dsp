import { useEffect } from "react";
import AudioRecord from "react-native-audio-record";
import type { AudioRecorderConfig } from "../types";

export const useAudio = (
    audio_recorder_config: AudioRecorderConfig,
    hasPermission: boolean,
    requestMicPermission: () => Promise<boolean>,
    onData: (data: string) => void
) => {

    
    useEffect(() => {
        if (!hasPermission) return;
        console.log('Initializing AudioRecord');
        
        AudioRecord.init(audio_recorder_config);
        AudioRecord.on("data", onData);
        AudioRecord.start();
        return () => {
            AudioRecord.stop();
        };
    }, [hasPermission, onData, audio_recorder_config]);
    
    
    const start = async () => {
        let allowed = hasPermission;

        if (!allowed) {
            allowed = await requestMicPermission();
        }

        if (allowed) {
            AudioRecord.start();
        }
    };

    const stop = () => {
        AudioRecord.stop();
    };


    return {
        start,
        stop,
    }
}