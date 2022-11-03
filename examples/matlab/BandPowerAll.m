BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIDs.MINDROVE_WIFI_BOARD), params);
sampling_rate = BoardShim.get_sampling_rate(int32(BoardIDs.MINDROVE_WIFI_BOARD));
board_shim.prepare_session();
board_shim.start_stream(45000, '');
pause(10);
board_shim.stop_stream();
nfft = DataFilter.get_nearest_power_of_two(sampling_rate);
data = board_shim.get_board_data(sampling_rate);
board_shim.release_session();

eeg_channels = BoardShim.get_eeg_channels(int32(BoardIDs.MINDROVE_WIFI_BOARD));
[avgs, stddevs] = DataFilter.get_avg_band_powers(data, eeg_channels, sampling_rate, true);