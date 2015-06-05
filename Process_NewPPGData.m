function [PPG_struct, Filt_struct] = Process_NewPPGData(RawSensorSum, NumberOfLEDPulses, PPG_struct, Filt_struct)
% This function processes new PPG data


% IF Bias point changes, which can be detected by noticing a change in the
% number of LED Pulses, then preset BPFilter taps to new datapoint
% This Filter reset is a quick recovery stategy
if (NumberOfLEDPulses ~= PPG_struct.NumberOfLEDPulses)
    y = RawSensorSum / Filt_struct.k_BPF_GAIN;
    for i = 1:9
        Filt_struct.xv(i) = y;
        Filt_struct.yv(i) = single(0.0);
    end
    PPG_struct.IgnoreFirstPulses = int8(4); % notify the pulse rate filter
end
PPG_struct.NumberOfLEDPulses = NumberOfLEDPulses;

%Bandpass filter: Cutoff freqs = 0.7 and 3.0 Hz with an data rate of 50Hz
[Filt_struct] = filterloopBPF07_30_50Hz(RawSensorSum, Filt_struct); 

% extract BPF output value 
PPG_struct.FilteredDataInput = Filt_struct.yv(9);

% run signal through PPG algorithm
[PPG_struct] = PPG_algorithm(PPG_struct);     

% Filter an resulting Pulse Rate Value
[PPG_struct] = PulseRateFilter(PPG_struct);

if PPG_struct.IgnoreFirstPulses > 0
    PPG_struct.IgnoreFirstPulses = PPG_struct.IgnoreFirstPulses - 1;
end


