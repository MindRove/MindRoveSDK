using System;
using System.Threading;
using mindrove;

namespace boardconfig
{
    internal class Program
    {
        static BoardShim board_shim = null;
        static int sampling_rate = 500;
        static int counter_idx = 0;
        static int trigger_idx = 0;
        static int n_package = 0;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            try
            {
                BoardShim.enable_dev_board_logger();
                MindRoveInputParams input_params = new MindRoveInputParams();
                int board_id = (int)BoardIds.MINDROVE_WIFI_BOARD;
                board_shim = new BoardShim(board_id, input_params);
                board_shim.prepare_session();
                board_shim.start_stream();

                sampling_rate = BoardShim.get_sampling_rate(board_id);
                counter_idx = BoardShim.get_package_num_channel(board_id);
                trigger_idx = BoardShim.get_other_channels(board_id)[0];
                Console.WriteLine("Device ready");
            }
            catch (MindRoveError ex)
            {
                Console.WriteLine(ex);
            }

            if (board_shim != null)
            {
                // Enable EEG mode and read 5 seconds of EEG data
                board_shim.config_board(BoardShim.MindroveWifiConfigMode.EEG_MODE);
                Console.WriteLine("Device configured in EEG mode");
                Console.WriteLine("Read 5 seconds of EEG data");
                
                int n = 0;
                while (n < 5 * sampling_rate)
                {
                    double[,] data = board_shim.get_current_board_data(2);
                    if (data[counter_idx, 0] > n_package)
                    {
                        string str = "";
                        for (int i = 0; i < data.GetLength(1); i++)
                        {
                            for (int j = 0; j < data.GetLength(0); j++)
                                str = string.Concat(str, " ", data[j, i]);
                            str = string.Concat(str, "\n");
                        }
                        n_package = (int)data[counter_idx, 1];
                        Console.WriteLine(str);
                        n = n + 2;
                    }
                }

                // Enable impedance mode and read 5 seconds of data
                board_shim.config_board(BoardShim.MindroveWifiConfigMode.IMP_MODE);
                Console.WriteLine("Device configured in impedance mode");
                Console.WriteLine("Read 5 seconds of impedance data");

                n = 0;
                while (n < 5 * sampling_rate)
                {
                    double[,] data = board_shim.get_current_board_data(2);
                    if (data[counter_idx, 0] > n_package)
                    {
                        string str = "";
                        for (int i = 0; i < data.GetLength(1); i++)
                        {
                            for (int j = 0; j < data.GetLength(0); j++)
                                str = string.Concat(str, " ", data[j, i]);
                            str = string.Concat(str, "\n");
                        }
                        n_package = (int)data[counter_idx, 1];
                        Console.WriteLine(str);
                        n = n + 2;
                    }
                }

                // Enable EEG mode again and read 5 seconds of test signal
                board_shim.config_board(BoardShim.MindroveWifiConfigMode.EEG_MODE);
                board_shim.config_board(BoardShim.MindroveWifiConfigMode.TEST_SIGNAL);
                Console.WriteLine("Device configured in EEG mode");
                Console.WriteLine("Read 5 seconds of test signal");

                n = 0;
                while (n < 5 * sampling_rate)
                {
                    double[,] data = board_shim.get_current_board_data(2);
                    if (data[counter_idx, 0] > n_package)
                    {
                        string str = "";
                        for (int i = 0; i < data.GetLength(1); i++)
                        {
                            for (int j = 0; j < data.GetLength(0); j++)
                                str = string.Concat(str, " ", data[j, i]);
                            str = string.Concat(str, "\n");
                        }
                        n_package = (int)data[counter_idx, 1];
                        Console.WriteLine(str);
                        n = n + 2;
                    }
                }

                // Switch back to EEG measurement mode, send and receive trigger signals
                board_shim.config_board(BoardShim.MindroveWifiConfigMode.EEG_MODE);
                Console.WriteLine("Device configured in EEG mode");
                Thread.Sleep(100);  // Wait a little after switching modes

                board_shim.config_board(BoardShim.MindroveWifiConfigMode.BEEP);
                Console.WriteLine("BEEP sent");

                board_shim.config_board(BoardShim.MindroveWifiConfigMode.BOOP);
                Console.WriteLine("BOOP sent");

                bool beep_received = false;
                bool boop_received = false;
                while (!(beep_received && boop_received))
                {
                    double[,] data = board_shim.get_current_board_data(2);
                    if (data[counter_idx, 0] > n_package)
                    {
                        for (int i = 0; i < data.GetLength(1); i++)
                        {
                            if ((int)data[trigger_idx, i] == 1)
                            {   
                                beep_received = true;
                                Console.WriteLine("BEEP!");
                            }

                            if ((int)data[trigger_idx, i] == 2)
                            {
                                boop_received = true;
                                Console.WriteLine("BOOP!");
                            }
                        }
                        n_package = (int)data[counter_idx, 1];
                    }
                }

                try
                {
                    board_shim.release_session();
                }
                catch (MindRoveError e)
                {
                    Console.WriteLine(e);
                }
                Console.WriteLine("Brainflow streaming was stopped");
            }
            Console.ReadLine();
        }
    }
}
