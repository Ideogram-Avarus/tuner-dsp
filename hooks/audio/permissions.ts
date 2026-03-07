import { useCallback, useEffect, useState } from "react";
import { PermissionsAndroid, Platform, Linking  } from "react-native";

export const usePermissions = () => {
  const [hasPermission, setHasPermission] = useState(false);

  const requestMicPermission = useCallback(async (): Promise<boolean> => {
    if (Platform.OS !== "android") return false;

    const result = await PermissionsAndroid.request(
      PermissionsAndroid.PERMISSIONS.RECORD_AUDIO!,
      {
        title: "Microphone Permission",
        message: "This app needs access to your microphone for pitch detection.",
        buttonPositive: "Allow",
        buttonNegative: "Deny",
      }
    );

    if (result === PermissionsAndroid.RESULTS.GRANTED) {
      setHasPermission(true);
      return true;
    }

    if (result === PermissionsAndroid.RESULTS.NEVER_ASK_AGAIN) {
      console.log("Permission permanently denied");
      Linking.openSettings();
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