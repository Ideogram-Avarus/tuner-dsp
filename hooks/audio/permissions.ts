import { useCallback, useEffect, useState } from "react";
import { PermissionsAndroid, Platform } from "react-native";

export const usePermissions = () => {
  const [hasPermission, setHasPermission] = useState(false);

  const requestMicPermission = useCallback(async (): Promise<boolean> => {
    if (Platform.OS === "android") {
      const granted = await PermissionsAndroid.request(
        PermissionsAndroid.PERMISSIONS.RECORD_AUDIO,
        {
          title: "Microphone Permission",
          message: "This app needs access to your microphone for pitch detection.",
          buttonPositive: "Allow",
          buttonNegative: "Deny",
        }
      );

      const allowed = granted === PermissionsAndroid.RESULTS.GRANTED;
      setHasPermission(allowed);
      return allowed;
    }

    setHasPermission(false);
    return false;
  }, []);

  useEffect(() => {
    requestMicPermission();
  }, [requestMicPermission]);

  return {
    hasPermission,
    requestMicPermission,
  };
};