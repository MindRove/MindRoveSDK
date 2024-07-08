#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

// include it here to allow user include only this single file
#include "mindrove_constants.h"
#include "mindrove_exception.h"
#include "mindrove_model_params.h"
#include "ml_module.h"


/// Calculates different metrics from raw data
class MLModel
{
private:
    struct MindRoveModelParams params;
    std::string serialized_params;

public:
    MLModel (struct MindRoveModelParams params);
    ~MLModel ()
    {
    }

    /// redirect logger to a file
    static void set_log_file (std::string log_file);
    /// enable ML logger with LEVEL_INFO
    static void enable_ml_logger ();
    /// disable ML loggers
    static void disable_ml_logger ();
    /// enable ML logger with LEVEL_TRACE
    static void enable_dev_ml_logger ();
    /// set log level
    static void set_log_level (int log_level);
    /// write user defined string to MindRove logger
    static void log_message (int log_level, const char *format, ...);
    /// release all currently prepared classifiers
    static void release_all ();
    /// get mindrove version
    static std::string get_version ();

    /// initialize classifier, should be called first
    void prepare ();
    /// calculate metric from data
    std::vector<double> predict (double *data, int data_len);
    /// release classifier
    void release ();
};
