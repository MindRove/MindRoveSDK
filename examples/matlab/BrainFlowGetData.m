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
board_shim.prepare_session();
a = board_shim.config_board('~6');
board_shim.start_stream(45000, '');
pause(5);
board_shim.stop_stream();
data = board_shim.get_current_board_data(10, preset);
disp(data);
board_shim.release_session();