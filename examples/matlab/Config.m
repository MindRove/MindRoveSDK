% -------------------------------------------------------------------------
% Tested with MindRove SDK v5.1.4 on 31.03.2025
% -------------------------------------------------------------------------

% BoardShim.release_all_sessions();
% clear all;
% clc;

BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();

params = MindRoveInputParams();
board_shim = BoardShim(int32(BoardIds.MINDROVE_WIFI_BOARD), params);
preset = int32(MindRovePresets.DEFAULT_PRESET);
board_shim.prepare_session();
board_shim.config_board('EEG_MODE');
board_shim.start_stream(45000, '');
pause(2);
board_shim.config_board('IMP_MODE');
pause(2);
board_shim.config_board('TEST_MODE');
pause(2);
board_shim.config_board('EEG_MODE');
pause(2);
board_shim.config_board('BEEP');
pause(2);
board_shim.stop_stream();
data = board_shim.get_board_data(board_shim.get_board_data_count(preset), preset);
disp(data);
board_shim.release_session();