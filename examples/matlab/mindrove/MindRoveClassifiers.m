classdef MindRoveClassifiers < int32
    % Store supported classifiers
    enumeration
        DEFAULT_CLASSIFIER(0)
        DYN_LIB_CLASSIFIER(1)
        ONNX_CLASSIFIER(2)
    end
end