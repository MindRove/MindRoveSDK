#pragma once

enum class MindRoveExitCodes : int
{
    STATUS_OK = 0,
    PORT_ALREADY_OPEN_ERROR = 1,
    UNABLE_TO_OPEN_PORT_ERROR = 2,
    SET_PORT_ERROR = 3,
    BOARD_WRITE_ERROR = 4,
    INCOMMING_MSG_ERROR = 5,
    INITIAL_MSG_ERROR = 6,
    BOARD_NOT_READY_ERROR = 7,
    STREAM_ALREADY_RUN_ERROR = 8,
    INVALID_BUFFER_SIZE_ERROR = 9,
    STREAM_THREAD_ERROR = 10,
    STREAM_THREAD_IS_NOT_RUNNING = 11,
    EMPTY_BUFFER_ERROR = 12,
    INVALID_ARGUMENTS_ERROR = 13,
    UNSUPPORTED_BOARD_ERROR = 14,
    BOARD_NOT_CREATED_ERROR = 15,
    ANOTHER_BOARD_IS_CREATED_ERROR = 16,
    GENERAL_ERROR = 17,
    SYNC_TIMEOUT_ERROR = 18,
    JSON_NOT_FOUND_ERROR = 19,
    NO_SUCH_DATA_IN_JSON_ERROR = 20,
    CLASSIFIER_IS_NOT_PREPARED_ERROR = 21,
    ANOTHER_CLASSIFIER_IS_PREPARED_ERROR = 22,
    UNSUPPORTED_CLASSIFIER_AND_METRIC_COMBINATION_ERROR = 23
};

enum class BoardIds : int
{
    PLAYBACK_FILE_BOARD = -3,
    STREAMING_BOARD = -2,
    SYNTHETIC_BOARD = -1,
    MINDROVE_WIFI_BOARD = 0,
    // use it to iterate
    FIRST = PLAYBACK_FILE_BOARD,
    LAST = MINDROVE_WIFI_BOARD
};

enum class IpProtocolType : int
{
    NONE = 0,
    UDP = 1,
    TCP = 2
};

enum class FilterTypes : int
{
    BUTTERWORTH = 0,
    CHEBYSHEV_TYPE_1 = 1,
    BESSEL = 2
};

enum class AggOperations : int
{
    MEAN = 0,
    MEDIAN = 1,
    EACH = 2
};

enum class WindowFunctions : int
{
    NO_WINDOW = 0,
    HANNING = 1,
    HAMMING = 2,
    BLACKMAN_HARRIS = 3
};

enum class DetrendOperations : int
{
    NONE = 0,
    CONSTANT = 1,
    LINEAR = 2
};

enum class MindRoveMetrics : int
{
    RELAXATION = 0,
    CONCENTRATION = 1,
    USER_DEFINED = 2
};

enum class MindRoveClassifiers : int
{
    REGRESSION = 0,
    KNN = 1,
    SVM = 2,
    LDA = 3,
    DYN_LIB_CLASSIFIER = 4
};

/// LogLevels enum to store all possible log levels
enum class LogLevels : int
{
    LEVEL_TRACE = 0,    /// TRACE
    LEVEL_DEBUG = 1,    /// DEBUG
    LEVEL_INFO = 2,     /// INFO
    LEVEL_WARN = 3,     /// WARN
    LEVEL_ERROR = 4,    /// ERROR
    LEVEL_CRITICAL = 5, /// CRITICAL
    LEVEL_OFF = 6       // OFF
};

enum class NoiseTypes : int
{
    FIFTY = 0,
    SIXTY = 1
};
