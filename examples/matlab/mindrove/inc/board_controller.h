#pragma once

#include "board_info_getter.h" // include it here for matlab
#include "shared_export.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // data acquisition methods
    SHARED_EXPORT int CALLING_CONVENTION prepare_session (
        int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION start_stream (int buffer_size, const char *streamer_params,
        int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION stop_stream (
        int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION release_session (
        int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int get_current_board_data (int num_samples, int preset, double *data_buf,
        int *returned_samples, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION get_board_data_count (
        int preset, int *result, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION get_board_data (int data_count, int preset,
        double *data_buf, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION config_board (const char *config, char *response,
        int *response_len, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION is_prepared (
        int *prepared, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION insert_marker (
        double marker_value, int preset, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION add_streamer (
        const char *streamer, int preset, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION delete_streamer (
        const char *streamer, int preset, int board_id, const char *json_mindrove_input_params);
    SHARED_EXPORT int CALLING_CONVENTION release_all_sessions ();

    // logging methods
    SHARED_EXPORT int CALLING_CONVENTION set_log_level_board_controller (int log_level);
    SHARED_EXPORT int CALLING_CONVENTION set_log_file_board_controller (const char *log_file);
    SHARED_EXPORT int CALLING_CONVENTION log_message_board_controller (
        int log_level, char *message);

    // platform types and methods
    typedef const struct JNINativeInterface *JNIEnv; // A handle to use Java's JNI
    SHARED_EXPORT int CALLING_CONVENTION java_set_jnienv (JNIEnv *java_jnienv);
    SHARED_EXPORT int CALLING_CONVENTION get_version_board_controller (
        char *version, int *num_chars, int max_chars);

#ifdef __cplusplus
}
#endif
