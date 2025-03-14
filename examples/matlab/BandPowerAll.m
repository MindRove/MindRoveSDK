% -------------------------------------------------------------------------
% Tested with MindRove SDK v5.1.4 on 03.03.2025
% -------------------------------------------------------------------------

% BoardShim.release_all_sessions();
% clear all;
% clc;

BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIds.MINDROVE_WIFI_BOARD), params);
preset = int32(MindRovePresets.DEFAULT_PRESET);
sampling_rate = BoardShim.get_sampling_rate(int32(BoardIds.MINDROVE_WIFI_BOARD), preset);
board_shim.prepare_session();
board_shim.start_stream(45000, '');
pause(10);
board_shim.stop_stream();
nfft = DataFilter.get_nearest_power_of_two(sampling_rate);
data = board_shim.get_board_data(sampling_rate, preset);
board_shim.release_session();

eeg_channels = BoardShim.get_eeg_channels(int32(BoardIds.MINDROVE_WIFI_BOARD), preset);
[avgs, stddevs] = DataFilter.get_avg_band_powers(data, eeg_channels, sampling_rate, true);
