using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using mindrove;

using Accord.Math;
using System;

public class NewBehaviourScript : MonoBehaviour
{
    private BoardShim board_shim = null;
    private MLModel concentration = null;
    private int sampling_rate = 0;
    private int[] eeg_channels = null;

    // Start is called before the first frame update

    void Start()
    {
        try
        {
            //BoardShim.set_log_file("mindrove_log.txt");
            BoardShim.enable_dev_board_logger();

            MindRoveInputParams input_params = new MindRoveInputParams();
            
            int board_id = (int)BoardIds.MINDROVE_WIFI_BOARD;

            board_shim = new BoardShim(board_id, input_params);
            board_shim.prepare_session();

            //board_shim.start_stream(); 
            board_shim.start_stream(450000, "file://file_stream.csv:w");

            MindRoveModelParams concentration_params = new MindRoveModelParams((int)MindRoveMetrics.MINDFULNESS, (int)MindRoveClassifiers.DEFAULT_CLASSIFIER);
            concentration = new MLModel(concentration_params);
            concentration.prepare();
            sampling_rate = BoardShim.get_sampling_rate(board_id);
            eeg_channels = BoardShim.get_eeg_channels(board_id);

        }
        catch (Exception ex)
        {
            Debug.Log(ex);

        }

    }

    void Update()
    {
        if ((board_shim == null) || (concentration == null))
        {

            Debug.Log("Not initialized");
            return;
        }
        int number_of_data_points = sampling_rate * 4; // 4 second window is recommended for concentration and relaxation calculations
        double[,] data = board_shim.get_current_board_data(number_of_data_points);
        if (data.GetRow(0).Length < number_of_data_points)
        {
            // wait for more data
            Debug.Log("Not enough data, data available: "+(data.GetRow(0).Length).ToString());
            return;
        }
        // prepare feature vector
        Tuple<double[], double[]> bands = DataFilter.get_avg_band_powers(data, eeg_channels, sampling_rate, true);
        double[] feature_vector = bands.Item1.Concatenate(bands.Item2);
        // calc and print concetration level
        // for synthetic board this value should be close to 1, because of sin waves ampls and freqs
        Debug.Log("Concentration: " + concentration.predict(feature_vector));
        
    }

    private void OnDestroy()
    {
        if (board_shim != null)
        {
            try
            {
                board_shim.release_session();
                concentration.release();
            }
            catch (Exception e)
            {
                Debug.Log(e);
            }
            Debug.Log("Streaming was stopped");
        }
    }
}