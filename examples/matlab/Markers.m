BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIDs.MINDROVE_WIFI_BOARD), params);
sampling_rate = BoardShim.get_sampling_rate(int32(BoardIDs.MINDROVE_WIFI_BOARD));
board_shim.prepare_session();
a = board_shim.config_board('~6');
board_shim.start_stream(45000, '');
pause(2);
board_shim.insert_marker(1);
pause(2);
board_shim.stop_stream();
data = board_shim.get_board_data(sampling_rate);
disp(data);
board_shim.release_session();