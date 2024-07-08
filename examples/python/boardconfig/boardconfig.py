import time
import mindrove
from mindrove.board_shim import BoardShim, MindRoveInputParams, BoardIds, MindRoveError

board_shim = None
try:
    BoardShim.enable_dev_board_logger()

    params = MindRoveInputParams()
    params.mac_address = "0b088c"
    board_id = BoardIds.MINDROVE_SYNCBOX_BOARD.value
    board_shim = BoardShim(board_id, params)
    board_shim.prepare_session()
    board_shim.start_stream(450000)

    sampling_rate = board_shim.get_sampling_rate(board_id)
    counter_idx = board_shim.get_package_num_channel(board_id)
    trigger_idx = board_shim.get_other_channels(board_id)[0]
    n_package = 0
    print("Device ready")
except MindRoveError:
    print(MindRoveError)
    exit()

if board_shim is not None:
    # Enable EEG mode and read 5 seconds of EEG data
    #"""
    board_shim.config_board(mindrove.MindroveConfigMode.EEG_MODE) # EEG_MODE 
    print("Device configured in EEG mode")
    print("Read 5 seconds of EEG data")
    
    time.sleep(2)
    #board_shim.release_session()
    
    n = 0
    while n < 5 * sampling_rate:
        data = board_shim.get_board_data(2)
        if data.shape[1] < 2:
            continue
        if data[counter_idx, 0] > n_package:
            s = ""
            for i in range(data.shape[1]):
                for j in range(data.shape[0]):
                    s = s + " " + str(data[j, i])
                s = s + "\n"
        n_package = data[counter_idx, 1]
        print(s)
        n = n + 2
    #"""
    # Enable impedance mode and read 5 seconds of data
    time.sleep(2)
    board_shim.config_board(mindrove.MindroveConfigMode.IMP_MODE)
    print("Device configured in impedance mode")
    print("Read 5 seconds of impedance data")

    time.sleep(2)
    n = 0
    while n < 10 * sampling_rate:
        data = board_shim.get_current_board_data(2)
        if data.shape[1] < 2:
            continue
        if data[counter_idx, 0] > n_package:
            s = ""
            for i in range(data.shape[1]):
                for j in range(data.shape[0]):
                    s = s + " " + str(data[j, i])
                s = s + "\n"
        n_package = data[counter_idx, 1]
        print("IMP"+s)
        n = n + 2

    # Enable EEG mode again and read 5 seconds of test signal
    board_shim.config_board(mindrove.MindroveConfigMode.EEG_MODE)
    board_shim.config_board(mindrove.MindroveConfigMode.TEST_MODE)
    print("Device configured in EEG mode")
    print("Read 5 seconds of test signal")

    n = 0
    while n < 0 * sampling_rate:
        data = board_shim.get_current_board_data(2)
        if data.shape[1] < 2:
            continue
        if data[counter_idx, 0] > n_package:
            s = ""
            for i in range(data.shape[1]):
                for j in range(data.shape[0]):
                    s = s + " " + str(data[j, i])
                s = s + "\n"
        n_package = data[counter_idx, 1]
        print(s)
        n = n + 2

    # Switch back to EEG measurement mode, send and receive trigger signals
    board_shim.config_board(mindrove.MindroveConfigMode.EEG_MODE)
    print("Device configured in EEG mode")
    time.sleep(0.1) # Wait a little after switching modes

    board_shim.config_board(mindrove.MindroveConfigMode.BEEP)
    print("BEEP sent")

    board_shim.config_board(mindrove.MindroveConfigMode.BOOP)
    print("BOOP sent")

    beep_received = False
    boop_received = False
    while not(beep_received and boop_received):
        data = board_shim.get_current_board_data(4)
        if data[counter_idx, 0] > n_package:
            for i in range(data.shape[1]):
                if data[trigger_idx, i] == 1:
                    beep_received = True
                    print("BEEP!")
                if data[trigger_idx, i] == 2:
                    boop_received = True
                    print("BOOP!")
                if data[trigger_idx, i] != 0:
                    print(data[trigger_idx, i])
        n_package = data[counter_idx, 1]
    try:
        board_shim.release_session()
    except MindRoveError:
        print(MindRoveError)
    print("Brainflow streaming was stopped")