import argparse
import logging

import pyqtgraph as pg
from pyqtgraph.Qt import QtGui, QtCore

from mindrove.board_shim import BoardShim, MindRoveInputParams, BoardIds
from mindrove.data_filter import DataFilter, FilterTypes, DetrendOperations


class Graph:
    def __init__(self, board_shim):
        self.board_id = board_shim.get_board_id()
        self.board_shim = board_shim
        # Use PPG channels (e.g., SPO₂ and heart rate)
        self.ppg_channels = BoardShim.get_ppg_channels(self.board_id)
        self.sampling_rate = BoardShim.get_sampling_rate(self.board_id)
        self.update_speed_ms = 50
        self.window_size = 200
        self.num_points = self.window_size * self.sampling_rate

        self.app = QtGui.QApplication([])
        # Create main widget with horizontal layout
        self.main_widget = QtGui.QWidget()
        self.layout = QtGui.QHBoxLayout()
        self.main_widget.setLayout(self.layout)
        self.main_widget.setWindowTitle('Mindrove PPG Plot')

        # Graphics widget for plotting
        self.graph_widget = pg.GraphicsLayoutWidget()
        self.layout.addWidget(self.graph_widget)

        # Label widget to display the latest values
        self.text_label = QtGui.QLabel()
        self.text_label.setMinimumWidth(200)
        self.layout.addWidget(self.text_label)

        self._init_timeseries()

        self.main_widget.resize(1000, 600)
        self.main_widget.show()

        # Set up a timer for periodic updates
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.update)
        self.timer.start(self.update_speed_ms)
        QtGui.QApplication.instance().exec_()

    def _init_timeseries(self):
        self.plots = []
        self.curves = []
        # Create a plot for each PPG channel
        for i in range(len(self.ppg_channels)):
            p = self.graph_widget.addPlot(row=i, col=0)
            p.showAxis('left', False)
            p.setMenuEnabled('left', False)
            p.showAxis('bottom', False)
            p.setMenuEnabled('bottom', False)
            if i == 0:
                p.setTitle('Heart Rate (50-180)')
                p.setYRange(50, 180, padding=0)
            elif i == 1:
                p.setTitle('SPO₂ (90-100)')
                p.setYRange(90, 100, padding=0)
            else:
                p.setTitle(f'Channel {self.ppg_channels[i]}')
                
            self.plots.append(p)
            curve = p.plot()
            self.curves.append(curve)

    def update(self):
        data = self.board_shim.get_current_board_data(self.num_points)

        latest_values_text = "Latest PPG Values:\n"
        # Update each plot with new data and prepare the text with the latest sample

        heart_rate_channel = self.ppg_channels[0]
        spo2_channel = self.ppg_channels[1]

        latest_hr_val = data[heart_rate_channel][-1]
        latest_spo2_val = data[spo2_channel][-1]

        self.curves[0].setData(data[heart_rate_channel].tolist())
        self.curves[1].setData(data[spo2_channel].tolist())

        latest_values_text += f"Current heart rate: {latest_hr_val:.2f}\n"
        latest_values_text += f"Current SPO2 value: {latest_spo2_val:.2f}\n"
    
        self.text_label.setText(latest_values_text)
        self.app.processEvents()


def main():
    BoardShim.enable_dev_board_logger()
    logging.basicConfig(level=logging.DEBUG)

    params = MindRoveInputParams()

    board_shim = None
    try:
        board_shim = BoardShim(BoardIds.MINDROVE_WIFI_BOARD, params)
        board_shim.prepare_session()
        board_shim.start_stream()
        Graph(board_shim)
    except BaseException:
        logging.warning('Exception', exc_info=True)
    finally:
        logging.info('End')
        if board_shim is not None and board_shim.is_prepared():
            logging.info('Releasing session')
            board_shim.release_session()


if __name__ == '__main__':
    main()
