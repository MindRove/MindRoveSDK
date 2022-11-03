BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIDs.MINDROVE_WIFI_BOARD), params);
sampling_rate = BoardShim.get_sampling_rate(int32(BoardIDs.MINDROVE_WIFI_BOARD));
board_shim.prepare_session();
board_shim.start_stream(45000, '');
pause(5);
board_shim.stop_stream();
nfft = DataFilter.get_nearest_power_of_two(sampling_rate);
data = board_shim.get_board_data(sampling_rate);
board_shim.release_session();

eeg_channels = BoardShim.get_eeg_channels(int32(BoardIDs.MINDROVE_WIFI_BOARD));
[avgs, stddevs] = DataFilter.get_avg_band_powers(data, eeg_channels, sampling_rate, true);
feature_vector = double([avgs, stddevs]);

concentration_params = MindRoveModelParams(int32(MindRoveMetrics.CONCENTRATION), int32(MindRoveClassifiers.REGRESSION));
concentration = MLModel(concentration_params);
concentration.prepare();
score = concentration.predict(feature_vector);
concentration.release();