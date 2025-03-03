% -------------------------------------------------------------------------
% Tested with MindRove SDK v5.1.4 on 03.03.2025
% -------------------------------------------------------------------------

% BoardShim.release_all_sessions();
% clear all;
% clc;

global user_break
user_break = false;

% Initialize board
BoardShim.set_log_file('mindrove.log');
BoardShim.enable_dev_board_logger();
params = MindRoveInputParams();
board_id = int32(BoardIds.MINDROVE_WIFI_BOARD);
board_shim = BoardShim(board_id, params);
board_shim.prepare_session();
board_shim.start_stream(45000, '');
preset = int32(MindRovePresets.DEFAULT_PRESET);

% Initialize figure, read and display initial data
figure('CloseRequestFcn',@my_closereq)
pause(3);
y = zeros(1000, 8);
x = linspace(1, 1000, 1000);
%x = linspace(1, size(y, 1), size(y, 1));
x = repmat(x, size(y, 2), 1)';
myplot = plot(x,y,'XDataSource','x','YDataSource','y', 'LineWidth', 1.5);
axis off;
set(gcf,'InvertHardCopy','off','Color','black');

% Read and display data in a loop
while user_break == false
    pause(0.01);
    y = read_data(board_shim, board_id, preset);
    refreshdata;
end

% Cleanup after the user closed the figure
close all force;
board_shim.stop_stream();
board_shim.release_session();

% Read data from board, filter and arrange them for display
function y = read_data(board_shim, board_id, preset)
    filter_order = 2;
    band_width = 12.5;
    
    sampling_rate = BoardShim.get_sampling_rate(board_id, preset);

    cutoff = 5;
    data = board_shim.get_current_board_data(2*sampling_rate + cutoff, preset);
    eeg_channels = BoardShim.get_eeg_channels(board_id, preset);
    eeg_data = data(eeg_channels, :)';

    for i = 0:1:length(eeg_channels) - 1
        eeg_data(:, i+1) = DataFilter.perform_highpass(eeg_data(:, i+1), sampling_rate, 0.5, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 50, filter_order, int32(FilterTypes.BUTTERWORTH), 0);      
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 100, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 150, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 200, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_highpass(eeg_data(:, i+1), sampling_rate, 0.5, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 50, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 100, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 150, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = DataFilter.perform_bandstop(eeg_data(:, i+1), sampling_rate, band_width, 200, filter_order, int32(FilterTypes.BUTTERWORTH), 0);
        eeg_data(:, i+1) = 10*(eeg_data(:, i+1) - mean(eeg_data(:, i+1)))/(max(eeg_data(:, i+1)) - min(eeg_data(:, i+1))) + i;
    end
    y = eeg_data(cutoff + 1:end, :);
end

% Informs the main loop the user has closed the figure
function my_closereq(src,event)
    global user_break
    user_break = true;
    delete(gcf);
end