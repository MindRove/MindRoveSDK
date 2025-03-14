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
board_shim.start_stream(45000, '');
pause(2)
board_shim.stop_stream()
data = board_shim.get_current_board_data(20, preset);
board_shim.release_session();

DataFilter.write_file(data, 'data.csv', 'w');
restored_data = DataFilter.read_file('data.csv');
