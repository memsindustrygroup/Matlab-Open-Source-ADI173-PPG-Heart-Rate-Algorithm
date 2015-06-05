function [PPG_struct] = PPG_algorithm(PPG_struct)
%#codegen

%% This function process Raw PPG sensor Data to determin a PulseRate  

%Constants
k_TimeStampsPerMin      = single(32000 * 60);   % Timestamp resolution is 31.25us (32KHz)
k_Max_Timestamp         = uint16(65535);        % for unwrapping overflowed Timestamps

%Local variables
Interpolated_zerotime       = single(0);
PPG_struct.PulseRate        = uint8(0);


FIXED_THRESHOLD = 1;

%%   P U L S E   D E T E C T O R   S T A T E   M A N A G E M E N T %
% There are 4 states, which are refered to in this code as "Quadrants" 
% These quadrants are assigned as such:
%    /\2     /\2     
% __/1 \_   /1 \_   _etc.
%       \3 /    \3 /  
%        \/4     \/4
if (PPG_struct.Quadrant == 1) 
	% This Quadrant began at the rising zero crossing of the signal 
	% This PPG_struct.Quadrant ends at the peak of the signal
    % when th peak is detected quadrant changes to Quadrant 2, 
    % Note that PulseRate associated with event this reported as belonging 
    % Quadrant 2, e.g. the Quadrant number is always 1 higher than the
    % associated PulseRate references for which it was computed.
	if (PPG_struct.FilteredDataInput > PPG_struct.Threshold) 
		if (PPG_struct.FilteredDataInput > PPG_struct.LocalHigh) 
			PPG_struct.LocalHigh = PPG_struct.FilteredDataInput;
		else 
			% % Peak Detected
            
			if (PPG_struct.PreviousTimestamp > PPG_struct.Timestamp)  % Fix wrap-around %
				PPG_struct.PreviousTimestamp = PPG_struct.PreviousTimestamp - k_Max_Timestamp;
            end
			
            % The current datapoint is already one datapoint behind the peak
            % datapoint therefore the previoustimestamp is used
			PPG_struct.PulseRate = uint8(k_TimeStampsPerMin / (single(PPG_struct.PreviousTimestamp) - PPG_struct.PreviousQTime(1)));
			
			PPG_struct.PreviousQTime(1) = single(PPG_struct.PreviousTimestamp); %Interpolated_zerotime;
			PPG_struct.Quadrant = uint8(2);  % progress to next PPG_struct.Quadrant state in waveform
		end
    elseif (PPG_struct.FilteredDataInput < single(0.0)) 
        % signal must be low is it crossed zero again, reducing threshold...
        if ~FIXED_THRESHOLD
            if (PPG_struct.Threshold > PPG_struct.Knob_Threshold_Goal)
                PPG_struct.Threshold = PPG_struct.Threshold / single(1.2);
            elseif (PPG_struct.Threshold > 10.0)
                PPG_struct.Threshold = PPG_struct.Threshold / single(1.02);
            end
        end
	else 
		PPG_struct.PreviousInputVal = PPG_struct.FilteredDataInput;
	end
end

if (PPG_struct.Quadrant == 2) 
	% The peak has been detected, this section looks for the zero crossing.
	% In this section PPG_struct.Quadrant changes from 2 to 3 when negative 
	% zero-crossing is detected. The calculated pulserate is reported as Q3
	% pulse rate

	if (PPG_struct.FilteredDataInput < single(0.0)) 
		PPG_struct.Quadrant = uint8(3);		    % PEAK DETECTED: move to next PPG_struct.Quadrant state
		if (PPG_struct.PreviousTimestamp > PPG_struct.Timestamp) 
			% Fix wrap-around %
			i0 = PPG_struct.PreviousTimestamp - k_Max_Timestamp;

			PPG_struct.PreviousTimestamp = i0;
		end

		Interpolated_zerotime = single(PPG_struct.PreviousTimestamp) +  (PPG_struct.PreviousInputVal/(PPG_struct.PreviousInputVal - PPG_struct.FilteredDataInput)) *  single(PPG_struct.Timestamp - PPG_struct.PreviousTimestamp);

		if (PPG_struct.PreviousQTime(2) > Interpolated_zerotime)  % Fix wrap-around %
			PPG_struct.PreviousQTime(2) = PPG_struct.PreviousQTime(2) - single(k_Max_Timestamp);
		end

		PPG_struct.PulseRate = uint8(k_TimeStampsPerMin/(Interpolated_zerotime - PPG_struct.PreviousQTime(2)));

		PPG_struct.PreviousQTime(2) = Interpolated_zerotime;
        
        if ~FIXED_THRESHOLD
            %  Filter new peak value into Threshold.
            %     If large positive jump then attenuate the change.
            if (PPG_struct.Knob_ThresholdTC > single(1.5) * PPG_struct.Threshold)
                f0 = PPG_struct.Knob_ThresholdTC/single(4.0);
            else
                f0 = PPG_struct.Knob_ThresholdTC;
            end
            
            PPG_struct.Threshold = PPG_struct.Threshold * (single(1.0) - f0) + ((PPG_struct.LocalHigh - PPG_struct.LocalLow)/single(4.0)) * f0;
        end
        PPG_struct.LocalLow = single(0.0);
        
    else
        PPG_struct.PreviousInputVal = PPG_struct.FilteredDataInput;
    end
end

if (PPG_struct.Quadrant == 3) 
	if (PPG_struct.FilteredDataInput < -PPG_struct.Threshold) 
		if (PPG_struct.FilteredDataInput < PPG_struct.LocalLow) 
			PPG_struct.LocalLow = PPG_struct.FilteredDataInput;
		else 
			% Valley detected
            
            PPG_struct.Quadrant = uint8(4);		% negative-slope zero cross followed by negative threshold crossing has been achieved - move to state 4
			            
			if (PPG_struct.PreviousTimestamp > PPG_struct.Timestamp) % Fix wrap-around %
				PPG_struct.PreviousTimestamp = PPG_struct.PreviousTimestamp - k_Max_Timestamp;
			end

			PPG_struct.PulseRate = uint8(k_TimeStampsPerMin/(single(PPG_struct.PreviousTimestamp) - PPG_struct.PreviousQTime(3)));
			PPG_struct.PreviousQTime(3) = single(PPG_struct.PreviousTimestamp); %Interpolated_zerotime;
        end
    elseif (PPG_struct.FilteredDataInput > single(0.0))
        if ~FIXED_THRESHOLD
            %signal must be low is it crossed zero again, reducing
            %threshold...
            if (PPG_struct.Threshold > PPG_struct.Knob_Threshold_Goal)
                PPG_struct.Threshold = PPG_struct.Threshold / single(1.2);
            elseif (PPG_struct.Threshold > single(10.0))
                PPG_struct.Threshold = PPG_struct.Threshold / single(1.02);
            end
        end
    else
        PPG_struct.PreviousInputVal = PPG_struct.FilteredDataInput;
    end
end

if (PPG_struct.Quadrant == 4) 
	if (PPG_struct.FilteredDataInput > single(0.0)) 
		PPG_struct.Quadrant = uint8(1);
	
		if (PPG_struct.PreviousTimestamp > PPG_struct.Timestamp) % Fix wrap-around %
			PPG_struct.PreviousTimestamp = PPG_struct.PreviousTimestamp - k_Max_Timestamp;
		end

		Interpolated_zerotime = single(PPG_struct.PreviousTimestamp) + (PPG_struct.PreviousInputVal/(PPG_struct.PreviousInputVal - PPG_struct.FilteredDataInput) * single(PPG_struct.Timestamp - PPG_struct.PreviousTimestamp));

		if (PPG_struct.PreviousQTime(4) > Interpolated_zerotime) 	% Fix wrap-around %
			PPG_struct.PreviousQTime(4) = PPG_struct.PreviousQTime(4) - single(k_Max_Timestamp);
		end

		PPG_struct.PulseRate = uint8(k_TimeStampsPerMin/(Interpolated_zerotime - PPG_struct.PreviousQTime(4)));
		PPG_struct.PreviousQTime(4) = Interpolated_zerotime;


		%  Filter new peak value into Threshold. 
		%     If large positive jump then attenuate the change.
		if (PPG_struct.Knob_ThresholdTC > single(1.5) * PPG_struct.Threshold) 
			f0 = PPG_struct.Knob_ThresholdTC / single(4.0);
		else
			f0 = PPG_struct.Knob_ThresholdTC;
		end 
        if ~FIXED_THRESHOLD
            PPG_struct.Threshold = PPG_struct.Threshold * (single(1.0) - f0) + (PPG_struct.LocalHigh - PPG_struct.LocalLow)/single(4.0) * f0;
        end
		PPG_struct.LocalHigh = single(0.0);

	else 
		PPG_struct.PreviousInputVal = PPG_struct.FilteredDataInput;
	end
end

PPG_struct.PreviousTimestamp = PPG_struct.Timestamp;


end % of function