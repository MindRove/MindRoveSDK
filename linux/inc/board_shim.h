#pragma once

#include <cstdarg>
#include <string>
#include <vector>

// include it here to allow user include only this single file
#include "board_controller.h"
#include "board_info_getter.h"
#include "mindrove_array.h"
#include "mindrove_constants.h"
#include "mindrove_exception.h"
#include "mindrove_input_params.h"

#include "json.hpp"

using json = nlohmann::json;

/// BoardShim class to communicate with a board
class BoardShim
{
    std::string serialized_params;
    struct MindRoveInputParams params;

public:
    // clang-format off
    /// disable MindRove loggers
    static void disable_board_logger ();
    /// enable MindRove logger with LEVEL_INFO
    static void enable_board_logger ();
    /// enable MindRove logger with LEVEL_TRACE
    static void enable_dev_board_logger ();
    /// redirect MindRove logger from stderr to file
    static void set_log_file (std::string log_file);
    /// use set_log_level only if you want to write your own log messages to MindRove logger
    static void set_log_level (int log_level);
    /// write user defined string to MindRove logger
    static void log_message (int log_level, const char *format, ...);

    /**
     * get board description as json
     * @param board_id board id of your device
     * @throw MindRoveException If board id is not valid exit code is UNSUPPORTED_BOARD_ERROR
     */
    static json get_board_descr (int board_id);
    /**
     * get sampling rate for this board
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_sampling_rate (int board_id);
    /**
     * get row index which holds package nums
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_package_num_channel (int board_id);
    /**
     * get row index which holds timestamps
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_timestamp_channel (int board_id);
    /**
     * get row index which holds markers
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_marker_channel (int board_id);
    /**
     * get row index which holds battery level info
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_battery_channel (int board_id);
    /**
     * get number of rows in returned from @ref get_board_data() 2d array
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static int get_num_rows (int board_id);
    /**
     * get device name
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::string get_device_name (int board_id);
    /**
     * get eeg channel names in 10-20 system for devices with fixed electrode locations
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<std::string> get_eeg_names (int board_id);
    /**
     * get row indices which hold EEG data, for some board we can not split EEG\EMG\...
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_eeg_channels (int board_id);
    /**
     * get row indices which hold EMG data, for some board we can not split EEG\EMG\...
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_emg_channels (int board_id);
    /**
     * get row indices which hold ECG data, for some board we can not split EEG\EMG\...
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_ecg_channels (int board_id);
    /**
     * get row indices which hold EOG data, for some board we can not split EEG\EMG\...
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_eog_channels (int board_id);
    /**
     * get row indices which hold EXG data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_exg_channels (int board_id);
    /**
     * get row indices which hold PPG data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_ppg_channels (int board_id);
    /**
     * get row indices which hold EDA data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_eda_channels (int board_id);
    /**
     * get row indices which hold accel data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_accel_channels (int board_id);
    /**
     * get row indices which hold analog data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_analog_channels (int board_id);
    /**
     * get row indices which hold gyro data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_gyro_channels (int board_id);
    /**
     * get row indices which hold other information
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_other_channels (int board_id);
    /**
     * get row indices which hold temperature data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_temperature_channels (int board_id);
    /**
     * get row indices which hold resistance data
     * @param board_id board id of your device
     * @throw MindRoveException If this board has no such data exit code is UNSUPPORTED_BOARD_ERROR
     */
    static std::vector<int> get_resistance_channels (int board_id);
    /// release all currently prepared session
    static void release_all_sessions ();
    /// get MindRove version
    static std::string get_version ();

    int board_id;

    BoardShim (int board_id, struct MindRoveInputParams params);
    ~BoardShim ()
    {
    }

    /// prepare Mindrove's streaming session, should be called first
    void prepare_session ();
    /**
     * start streaming thread and store data in ringbuffer
     * @param buffer_size size of internal ring buffer
     * @param streamer_params use it to pass data packages further or store them directly during streaming,
                    supported values: "file://%file_name%:w", "file://%file_name%:a", "streaming_board://%multicast_group_ip%:%port%"".
                    Range for multicast addresses is from "224.0.0.0" to "239.255.255.255"
     */
    void start_stream (int buffer_size = 450000, std::string streamer_params = "");
    /// check if session is ready or not
    bool is_prepared ();
    /// stop streaming thread, doesnt release other resources
    void stop_stream ();
    /// release streaming session
    void release_session ();
    /// get latest collected data, doesnt remove it from ringbuffer
    MindRoveArray<double, 2> get_current_board_data (int num_samples);
    /// Get board id, for some boards can be different than provided (playback, streaming)
    int get_board_id ();
    /// get number of packages in ringbuffer
    int get_board_data_count ();
    /// get all collected data and flush it from internal buffer
    MindRoveArray<double, 2> get_board_data ();
    /// get required amount of datapoints or less and flush it from internal buffer
    MindRoveArray<double, 2> get_board_data (int num_datapoints);
    /// send string to a board, use it carefully and only if you understand what you are doing
    std::string config_board (char *config);
    /// insert marker in data stream
    void insert_marker (double value);
    // clang-format on
};
