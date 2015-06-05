function PPG_struct = PulseRateFilter(PPG_struct)
%-------------------------------------------------------
% This function qualifies and filters Raw pulse rate data
% If the new datapoint qualifies the value will go into a 5-element queue.
% The median value of this queue is then averaged with historical values

% The IgnoreFirstPulses is set to some number (5 at last revision) when a 
% transient occurs to aid in quick and reliable recovery. As on now, only 
% a number-of-LED-Pulses change causes this to happen. 
% When IgnoreFirstPulses>1 the Mean Value is frozen and the median filter 
% re-populates its buffer as this value counts down to 0 at each 
% consecutive rising zero crossing (quadrant 1) event.

% Qualifications:
% Save the Pulse Rate from Quadrant 1, which comes from the difference of
% two interpolated timestamps of two consecutive rising zero-crossings.
% Later, when Quadrant 2 phase arrives, Q1 Pulse Rate signal quality can  
% be judged because the peak-peak amplitude prior to and after the 
% zero-crossing becomes available.


%PreQualify All Pulse Rates. PPG_struct.Threshold is a moving mean value
if ((PPG_struct.PulseRate > PPG_struct.Knob_MinPulseRate) ...
 && (PPG_struct.Threshold > PPG_struct.Knob_Qualified_Threshold ))

    if (PPG_struct.Quadrant == 1)
        PPG_struct.LastQ1PulseRate = PPG_struct.PulseRate;
    end
    
    
    if (PPG_struct.Quadrant == 2)
        if (PPG_struct.IgnoreFirstPulses < 1)
            %Final Qualification is the min peak-peak amplitude requirement
           if     (PPG_struct.LocalHigh > PPG_struct.Knob_Qualified_Threshold )...
               && (PPG_struct.LocalLow < 0) 
           
                PPG_struct.PulseRateHistory(PPG_struct.PulseRatePointer) = PPG_struct.LastQ1PulseRate;

                if (PPG_struct.IgnoreFirstPulses == 0)
                        % on the first time back from a transient event use only
                        % median value to jump start the mean filter
                    PPG_struct.MovingPRMemory = single(median(PPG_struct.PulseRateHistory));
                        %Denote that the mean value has been re-initialized
                    PPG_struct.IgnoreFirstPulses = int8(-1); 
                else
                        % At all other times use history to mean filter the PR
                     PPG_struct.MovingPRMemory = PPG_struct.MovingPRMemory * (PPG_struct.Knob_MeanPulseRateTC)...
                        + (single(median(PPG_struct.PulseRateHistory)) * (1.0 - PPG_struct.Knob_MeanPulseRateTC));                   
                end
                
                temp =  PPG_struct.PulseRatePointer + 1;
                PPG_struct.PulseRatePointer = temp;
                if (PPG_struct.PulseRatePointer >  PPG_struct.Knob_MedianTaps)
                    PPG_struct.PulseRatePointer = uint8(1);
                end
            end
        else                
            if (PPG_struct.IgnoreFirstPulses < 5)
                    % Prime the buffer. Oldest data starting second lowest element
                PPG_struct.PulseRateHistory( 5 - PPG_struct.IgnoreFirstPulses + 1) = PPG_struct.PulseRate;
                PPG_struct.PulseRatePointer = uint8(1);                
            end            
        end % of (PPG_struct.IgnoreFirstPulses < 1)
    end   % of if Quadrant == 2
    
end % of PulseRate PreQualification
PPG_struct.MeanPulseRate = PPG_struct.MovingPRMemory;