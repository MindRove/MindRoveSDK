classdef BoardIDs < int32
    % Store all supported board ids
    enumeration
        PLAYBACK_FILE_BOARD(-3)
        STREAMING_BOARD(-2)
        SYNTHETIC_BOARD(-1)
        MINDROVE_WIFI_BOARD(0)
    end
end