import argparse
import logging
import os 

import pyqtgraph as pg
from pyqtgraph.Qt import QtGui, QtCore

import mindrove
from mindrove.board_shim import BoardShim, MindRoveInputParams, BoardIds
from mindrove.data_filter import DataFilter, FilterTypes, DetrendOperations

import numpy as np

class Graph:
    def __init__(self, board_shim : BoardShim):
        self.board_id = board_shim.get_board_id()
        self.board_shim = board_shim
        self.exg_channels = BoardShim.get_exg_channels(self.board_id)
        self.sampling_rate = BoardShim.get_sampling_rate(self.board_id)
        self.package_num = BoardShim.get_package_num_channel(self.board_id)
        self.update_speed_ms = 50
        self.window_size = 2
        self.num_points = self.window_size * self.sampling_rate +20

        self.inner_counter = 0
        self.max_counter = 20

        self.app = QtGui.QApplication([])
        self.win = pg.GraphicsWindow(title='Mindrove Plot',size=(800, 600))

        self._init_timeseries()

        self.main_data = np.zeros((30, 0))

        timer = QtCore.QTimer()
        timer.timeout.connect(self.update)
        timer.start(self.update_speed_ms)
        QtGui.QApplication.instance().exec_()

    def _init_timeseries(self):
        self.plots = list()
        self.curves = list()
        for i in range(len(self.exg_channels)):
            p = self.win.addPlot(row=i,col=0)
            p.showAxis('left', False)
            p.setMenuEnabled('left', False)
            p.showAxis('bottom', False)
            p.setMenuEnabled('bottom', False)
            if i == 0:
                p.setTitle('TimeSeries Plot')
            self.plots.append(p)
            curve = p.plot()
            self.curves.append(curve)

    def update(self):
        data = self.board_shim.get_current_board_data(self.num_points)

        if(data.shape[1] == 0):
            return
        
        autotriggers = data[31]
        print(f"AUTO TRIGGER: {autotriggers[autotriggers != 0.0]}")
        for count, channel in enumerate(self.exg_channels):
            # plot timeseries
            DataFilter.detrend(data[channel], DetrendOperations.CONSTANT.value)
            
            DataFilter.perform_bandpass(data[channel], self.sampling_rate, 51.0, 100.0, 2,
                                        FilterTypes.BUTTERWORTH.value, 0)
            self.curves[count].setData(data[channel].tolist())

        self.app.processEvents()
        

def main():

    BoardShim.enable_dev_board_logger()
    logging.basicConfig(level=logging.DEBUG)

    parser = argparse.ArgumentParser(description='MindRove SyncBox plotter example', epilog=f'Example of use: python {os.path.basename(__file__)} -m ssid1 ssid2 ssid3')
    parser.add_argument('-m', '--mac-addresses', type=str, nargs="+", help='List of maximum 4 device addresses separated by a space', required=True, default=[])
    args = parser.parse_args()


    SSIDS = args.mac_addresses

    assert len(SSIDS) <= 4, f"Only a maximum of 4 devices can be connected to the SyncBox currently. The current list of devices given is of length {len(SSIDS)} with values: {SSIDS}"

    print(f"Creating Board for the following devices: {SSIDS}")

    params = [MindRoveInputParams() for x in SSIDS]

    for i, param in enumerate(params):
        param.mac_address = SSIDS[i]
        
    board_shims = [BoardShim(BoardIds.MINDROVE_SYNCBOX_BOARD.value, param) for param in params]

    for board_shim in board_shims:
        board_shim.prepare_session()
        board_shim.start_stream()

    for board_shim in board_shims:
        try:
            #board_shim.config_board(mindrove.MindroveConfigMode.EEG_MODE)
            
            Graph(board_shim)
        except BaseException:
            logging.warning('Exception', exc_info=True)


if __name__ == '__main__':
    main()
