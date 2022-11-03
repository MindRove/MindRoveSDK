BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIDs.MINDROVE_WIFI_BOARD), params);
sampling_rate = BoardShim.get_sampling_rate(int32(BoardIDs.MINDROVE_WIFI_BOARD));
board_shim.prepare_session();
board_shim.start_stream(45000, '');
pause(10);
nfft = DataFilter.get_nearest_power_of_two(sampling_rate);
data = board_shim.get_board_data(512);

board_shim.stop_stream();
board_shim.release_session();

eeg_channels = BoardShim.get_eeg_channels(int32(BoardIDs.MINDROVE_WIFI_BOARD));
eeg_channel = eeg_channels(2);
original_data = data(eeg_channel, :);
detrended = DataFilter.detrend(original_data, int32(DetrendOperations.LINEAR));
[ampls, freqs] = DataFilter.get_psd_welch(detrended, nfft, nfft / 2, sampling_rate, int32(WindowFunctions.HANNING));
band_power_alpha = DataFilter.get_band_power(ampls, freqs, 7.0, 13.0);
band_power_beta = DataFilter.get_band_power(ampls, freqs, 14.0, 30.0);
ratio = band_power_alpha / band_power_beta;