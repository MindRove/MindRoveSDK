classdef BoardIds < int32
    % Store all supported board ids
    enumeration
        NO_BOARD(-100)
        PLAYBACK_FILE_BOARD(-3)
        STREAMING_BOARD(-2)
        SYNTHETIC_BOARD(-1)
        MINDROVE_WIFI_BOARD(0)
        MINDROVE_SYNCBOX_BOARD(1)
    end
end