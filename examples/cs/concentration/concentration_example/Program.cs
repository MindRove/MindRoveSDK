using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System;
using mindrove;

using Accord.Math;
using System.Text;

namespace mindrove_cs_test
{
    static class Program
    {

        static BoardShim board_shim = null;
        static MLModel concentration = null;
        static int sampling_rate = 250;
        static int[] eeg_channels = null;
        static int counter_idx = 0;

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

                board_shim.start_stream(); // use this for default options
                                           //board_shim.start_stream(450000, "file://file_stream.csv:w");

                //board_shim.config_board(BoardShim.MindroveWifiConfigMode.EEG_MODE);

                MindRoveModelParams concentration_params = new MindRoveModelParams((int)MindRoveMetrics.CONCENTRATION, (int)MindRoveClassifiers.REGRESSION);
                concentration = new MLModel(concentration_params);
                concentration.prepare();

                sampling_rate = BoardShim.get_sampling_rate(board_id);
                eeg_channels = BoardShim.get_eeg_channels(board_id);
                counter_idx = BoardShim.get_package_num_channel(board_id);

            }
            catch (MindRoveException ex)
            {
                Console.WriteLine(ex);

            }

            while (Update() >= 0)
            {

            }

            if (board_shim != null)
            {
                try
                {
                    board_shim.release_session();
                    concentration.release();
                }
                catch (MindRoveException e)
                {
                    Console.WriteLine(e);
                }
                Console.WriteLine("Streaming was stopped");
            }
            Console.ReadLine();
        }

        static int Update()
        {
            if ((board_shim == null) || (concentration == null))
            {
                Console.ReadLine();
                return -1;
            }
            int number_of_data_points = sampling_rate * 4; // 4 second window is recommended for concentration and relaxation calculations


            double[,] data = board_shim.get_current_board_data(number_of_data_points);
            
            if (data.GetRow(0).Length < number_of_data_points)
            {
                Console.Write("Only {0} of {1} required, still waiting ...            \r", data.GetRow(0).Length, number_of_data_points);
                // wait for more data
                return 0;
            }
            
            // prepare feature vector
            Tuple<double[], double[]> bands = DataFilter.get_avg_band_powers(data, eeg_channels, sampling_rate, true);
            double[] feature_vector = bands.Item1.Concatenate(bands.Item2);
            // calc and print concetration level
            // for synthetic board this value should be close to 1, because of sin waves ampls and freqs

            Console.WriteLine("Concentration: " + concentration.predict(feature_vector));


            return 0;
            
        }

    }
}
