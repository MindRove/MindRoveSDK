#include <iostream>
#include <stdlib.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "board_shim.h"
#include "data_filter.h"

using namespace std;


int main (int argc, char *argv[])
{
    BoardShim::enable_dev_board_logger ();

    struct MindRoveInputParams params;
    int res = 0;
    int board_id = (int)BoardIds::SYNTHETIC_BOARD;
    // use synthetic board for demo
    BoardShim *board = new BoardShim (board_id, params);

    try
    {
        board->prepare_session ();
        board->start_stream ();

#ifdef _WIN32
        Sleep (5000);
#else
        sleep (5);
#endif

        board->stop_stream ();
        MindRoveArray<double, 2> data = board->get_board_data ();
        board->release_session ();
        std::cout << "Original data:" << std::endl << data << std::endl;

        // apply filters
        std::vector<int> eeg_channels = BoardShim::get_eeg_channels (board_id);
        for (int i = 0; i < eeg_channels.size (); i++)
        {
            switch (i)
            {
                // for demo apply different methods to different channels
                case 0:
                    DataFilter::perform_rolling_filter (data.get_address (eeg_channels[i]),
                        data.get_size (1), 3, (int)AggOperations::MEDIAN);
                    break;
                case 1:
                    DataFilter::perform_rolling_filter (data.get_address (eeg_channels[i]),
                        data.get_size (1), 3, (int)AggOperations::MEAN);
                    break;
                default:
                    // if moving average and moving median dont work well for your signal you can
                    // try wavelet based denoising, feel free to try different wavelet functions and
                    // decomposition levels
                    DataFilter::perform_wavelet_denoising (data.get_address (eeg_channels[i]),
                        data.get_size (1), (int)WaveletTypes::BIOR3_9, 3,
                        (int)WaveletDenoisingTypes::SURESHRINK, (int)ThresholdTypes::HARD,
                        (int)WaveletExtensionTypes::SYMMETRIC,
                        (int)NoiseEstimationLevelTypes::FIRST_LEVEL);
                    break;
            }
        }
        std::cout << "Data after denoising:" << std::endl << data << std::endl;
    }
    catch (const MindRoveException &err)
    {
        BoardShim::log_message ((int)LogLevels::LEVEL_ERROR, err.what ());
        res = err.exit_code;
        if (board->is_prepared ())
        {
            board->release_session ();
        }
    }

    delete board;

    return res;
}
