function [ PPG_struct ] = initPPG_struct()

% ------------------ KNOBS ------------------------------------    
    
    PPG_struct.Knob_Threshold_Goal      = uint8(5);         % Target threshold level
    PPG_struct.Knob_ThresholdTC         = single(0.15);     % Time const used in moving mean filter
    PPG_struct.Knob_Qualified_Threshold = uint16(7);        % Pulse amplitude qualification threshold for Pulse Rate Filter
    PPG_struct.Knob_MeanPulseRateTC     = single(0.85);     % Time Const of Mean Pulse Rate
                                                            
    PPG_struct.Knob_MinPulseRate        = uint8(20);        % for Pulse Rate qualification
    PPG_struct.Knob_LightExposureGoal   = uint8(90);
    PPG_struct.Knob_LightExposureGoal_H = uint8(99);
    PPG_struct.Knob_LightExposureGoal_L = uint8(45);

    PPG_struct.Knob_BiasUpdateInterval  = uint8(50);
    PPG_struct.Knob_AdaptiveBiasGain    = uint8(16);
    PPG_struct.Knob_MedianTaps          = uint8(5);
    
    
% ---------- PulseRate Calculations ----------------------   
    PPG_struct.PulseRate                = uint8(0);
    PPG_struct.FilteredDataInput        = single(0);
    PPG_struct.PreviousInputVal         = single(0);
    PPG_struct.Quadrant                 = uint8(1);
    PPG_struct.PreviousQTime            = zeros([4,1],'single');
    PPG_struct.LocalHigh                = single(0);
    PPG_struct.LocalLow                 = single(0);
    PPG_struct.Threshold                = single(10); 
    PPG_struct.Timestamp                = uint16(0);
    PPG_struct.PreviousTimestamp        = uint16(0);
    PPG_struct.IgnoreFirstPulses        = int8(6);
    PPG_struct.NumberOfLEDPulses        = uint8(0);
    
% ---------- PulseRate Filter Variables ----------------------

    PPG_struct.PulseRateHistory         = zeros(1,5,'single');
    PPG_struct.PulseRatePointer         = uint8(1);
    PPG_struct.MovingPRMemory           = single(0);
    PPG_struct.LastQ1PulseRate          = uint8(0);
    PPG_struct.MeanPulseRate            = single(0);
