import { useEffect, } from "react";
import AudioRecord from "react-native-audio-record";
import { AUDIO_RECORDER_CONFIG } from "../constants";


export const useAudio = (
    hasPermission: boolean,
    requestMicPermission: () => Promise<boolean>,
    onData: (data: string) => void
) => {

    useEffect(() => {
        if (!hasPermission) return;

        console.log('Initializing AudioRecord');
        AudioRecord.init(AUDIO_RECORDER_CONFIG);
        AudioRecord.on("data", onData);
        
        return () => {
            AudioRecord.stop();
        };
    }, [hasPermission, onData]);

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