%% Process_PPG_LogFile.m 
clear;clc;


dataBaseDir = 'Test_Vectors/';


%% Load pedometer data (need to select test data files)
if 0
    Filename = 'SENtrode2015-05-06-18-18-07.csv';
    DataLogFilename = [dataBaseDir Filename];
else
[Filename,PathName] = uigetfile({'Data/;*.csv'},'Choose Log File');
DataLogFilename = [dataBaseDir Filename];
end

% datalog file prototype (index:field name)
%   1:Timestamp, 2:peripheral, 3:id,          4:GATT,        5:heartrate,	
%   6:ax,        7:ay,         8:az,          9:aTimestamp,	
%  10:SLOTA_PD1, 11:SLOTA_PD2, 12:SLOTA_PD3, 13:SLOTA_PD4,	14: rawTimestamp,	
%  15:led,	
%  16:SLOTB_PD1, 17:SLOTB_PD2, 18:SLOTB_PD3, 19:SLOTB_PD4,  20:rawTimestamp,
%  21:rawPulse,	 22:firmware

% NOTE on wrapped vs. unwrapped Sensor Timestamps and AppTimestamps
% The Process_NewPPGData function can deal with unwrapped timestamps.
%   It unwraps values only as needed (to compare to a previous value for
%   pulse rate calculation)
% In this Matlab code, for further anaysis and comparison to reference 
%  sensors the SensorTimestamp domain will be used over the application 
%  timestamp, which is known to be inconsistant.



%% Setup data structures
PPG_struct = initPPG_struct();
%Filt_struct = initFilt_struct();
Filt_struct = initFilt_struct50();



%% read input file
%M = csvread(DataLogFilename,1,0); % with offset for header row
%M_Len = size(M,1);
%T = readtable(DataLogFilename);

fileID = fopen(DataLogFilename);
OneRow = fgetl(fileID);
Index = 1;LineNumber = 1; FirstError = 1;
fprintf('Reading...\n');
BadLines = 0;

while ~feof(fileID)                % Corrupt Rows of data where found to be common
    OneRow = fgetl(fileID);          % this step necessary to weed them out
    if length(strfind(OneRow,',')) == 21   % Allow only if proper num of delimiters
        M = textscan(OneRow,'%f%s%s%s%d%f%f%f%d%d%d%d%d%d%d%d%d%d%d%d%d%d','Delimiter',',');
        if Index==1, T_Zero = double(M{1});end
%        if Index==1, T_Zero = double(0);end
        
        % Parse csvread output array 'M' into meaningful variable names
        Timestamp(Index)          =   double(M{1}) - T_Zero; %1/1000 second inc
        Peripheral(Index)         =   M{2};
        ID(Index)                 =   M{3};
        if ~isempty(M{4}),			GATT(Index)               =   M{4};
        else                        GATT(Index)               =   '';end;
        if ~isempty(M{5}),			MeanHeartPulseRate(Index) =   uint8(M{5});
        else                        MeanHeartPulseRate(Index) =   uint8(0);end;
        if ~isempty(M{6}),			AX(Index)                 =   single(M{6});
        else                        AX(Index)                 =   single(0);end;
        if ~isempty(M{7}),			AY(Index)                 =   single(M{7});
        else                        AY(Index)                 =   single(0);end;
        if ~isempty(M{8}),			AZ(Index)                 =   single(M{8});
        else                        AZ(Index)                 =   single(0);end;
        if ~isempty(M{9}),			AccTimestamp(Index)       =   uint16(M{9});
        else                        AccTimestamp(Index)       =   uint16(0);end;       
        
        if AZ(Index)==0            
                AX(Index)= AX(Index-1);
                AY(Index)= AY(Index-1);
                AZ(Index)= AZ(Index-1);
                AccTimestamp(Index) =   uint16(0);
        end       
        
        if ~isempty(M{10}),			SlotA_PD1(Index)          =   uint16(M{10});
        else                        SlotA_PD1(Index)          =   uint16(0); end;
        if ~isempty(M{11}),			SlotA_PD2(Index)          =   uint16(M{11});
        else                        SlotA_PD2(Index)          =   uint16(0);end;
        if ~isempty(M{12}),			SlotA_PD3(Index)          =   uint16(M{12});
        else                        SlotA_PD3(Index)          =   uint16(0);end;
        if ~isempty(M{13}),			SlotA_PD4(Index)          =   uint16(M{13});
        else                        SlotA_PD4(Index)          =   uint16(0);end;
        if ~isempty(M{14}),			SlotA_Timestamp(Index)    =   uint32(M{14});
        else                        SlotA_Timestamp(Index)    =   2^16;end;
        if ~isempty(M{15}),			Status(Index)             =   uint8(M{15}); 
        else                        Status(Index)             =   uint8(0);end; 
        if ~isempty(M{16}),			SlotB_PD1(Index)          =   uint16(M{16});
        else                        SlotB_PD1(Index)          =   uint16(0);end;
        if ~isempty(M{17}),			SlotB_PD2(Index)          =   uint16(M{17});
        else                        SlotB_PD2(Index)          =   uint16(0);end;
        if ~isempty(M{18}),			SlotB_PD3(Index)          =   uint16(M{18});
        else                        SlotB_PD3(Index)          =   uint16(0);end;
        if ~isempty(M{19}),			SlotB_PD4(Index)          =   uint16(M{19});
        else                        SlotB_PD4(Index)          =   uint16(0);end;
        if ~isempty(M{20}),			SlotB_Timestamp(Index)    =   uint32(M{20});
        else                        SlotB_Timestamp(Index)    =   2^16;end;
        if ~isempty(M{21}),			Raw_PulseRate(Index)      =   uint8(M{21});
        else                        Raw_PulseRate(Index)      =   uint8(0);end;
        if ~isempty(M{22}),			Firmware_Level(Index)     =   uint8(M{22});
        else                        Firmware_Level(Index)     =   uint8(0);end;
        
        Index = Index + 1;
    else
        if FirstError
            fprintf('Error(s) found on the following Datalog line(s):');
        end
        fprintf('%d ',LineNumber+1);
        BadLines = BadLines + 1;
        FirstError = 0;
    end
    LineNumber = LineNumber + 1;
end
fclose(fileID);

M_Len = Index - 1;

%Extract Number of LED pulses from upper 3-bits of byte
NumberLEDPulses(1:M_Len)    =   mod(Status(1:M_Len),64);


% NOTE: MeanHeartPulseRate is the only NON-Raw data retrieved from the CSV
%       file. It is the mean pulse rate calculated by the firware in
%       SENtral. MeanPulseRate below should calculate identical value if
%       the two algorithms still match. PulseRate below is the local 
%       Matlab PPG algorithms' (called below) raw unfiltered pulse rate.
fprintf('\n\nDatafile: "%s"  has \n',DataLogFilename);
fprintf('%d Bad lines\n',BadLines);
fprintf('%d Good lines\n',M_Len);





%% Parse data fields into contiguous arrays


fprintf('Parsing SlotA data....\n');
%collect only valid Green LED "Slot A" data intocontiguous arrays
Index = 1; count = 1;Wraps = 0;
while Index < M_Len
    while  (Index < M_Len) && ((SlotA_Timestamp(Index) == 0) && (SlotA_PD1(Index) == 0))...
        || ((count > 1) && (SlotA_Timestamp(Index) == p_SlotA_Timestamp(count-1)))
             Index = Index + 1;
    end
    if Index < M_Len   
        p_AppTimestamp(count)       =  Timestamp(Index);
        p_SlotA_Timestamp(count)    =  uint16(SlotA_Timestamp(Index));    
        p_SlotA_PD1(count)          =  SlotA_PD1(Index);
        p_SlotA_PD2(count)          =  SlotA_PD2(Index);
        p_SlotA_PD3(count)          =  SlotA_PD3(Index);
        p_SlotA_PD4(count)          =  SlotA_PD4(Index);
        p_NumberLEDPulses(count)    =  NumberLEDPulses(Index);
        p_MeanHeartPulseRate(count) =  MeanHeartPulseRate(Index);
        
        if (count > 1)
            if (uint32(p_SlotA_Timestamp(count))+ Wraps*2^16) < p_SensorTimestamp(count-1)
                Wraps = Wraps + 1;
            end
        end
        p_SensorTimestamp(count) = uint32(p_SlotA_Timestamp(count)) + Wraps*2^16;

        % get Raw Pulse rate, which is attached to the next line 
        if strcmp(Peripheral{Index}(1:3),'PPG')
             p_Raw_PulseRate(count) = Raw_PulseRate(Index); % line are combined
        else    
            if (Index < M_Len)
                if (SlotB_Timestamp(Index+1) ~= 0)
                    p_Raw_PulseRate(count) =  Raw_PulseRate(Index+1);
                else
                    p_Raw_PulseRate(count) =  0; 
                end
            else
                p_Raw_PulseRate(count)     =  0; % EOF
            end
        end
        count = count + 1;
        Index = Index + 1;
    end
end
p_Len = count - 1;





fprintf('Parsing SlotB data....\n');
%collect only valid IR LED "Slot B" data into contiguous arrays
Index = 1; count = 1;Wraps = 0;
while Index < M_Len
    while (Index < M_Len) && ((SlotB_Timestamp(Index) == 0) && (SlotB_PD1(Index) == 0))
            Index = Index + 1;
    end
    if Index < M_Len    
        pb_AppTimestamp(count)       =  Timestamp(Index);
        pb_SlotB_Timestamp(count)    =  uint16(SlotB_Timestamp(Index));    
        pb_SlotB_PD1(count)          =  SlotB_PD1(Index);
        pb_SlotB_PD2(count)          =  SlotB_PD2(Index);
        pb_SlotB_PD3(count)          =  SlotB_PD3(Index);
        pb_SlotB_PD4(count)          =  SlotB_PD4(Index);

        if (count > 1)
            if (uint32(pb_SlotB_Timestamp(count))+ Wraps*2^16) < pb_SensorTimestamp(count-1)
                Wraps = Wraps + 1;
            end
        end
        pb_SensorTimestamp(count) = uint32(pb_SlotB_Timestamp(count)) + Wraps*2^16;
        
        
        count = count + 1;
        Index = Index + 1;
    end
end
pb_Len = count - 1;




if 1

%Parse The Reference Heart Rates into  contiguous arrays
fprintf('Parsing Refernce Heart Rate Sensor data....\n');

%Determin number of peripherals (refernce HPR sensors) used in this log
Index = 1; NumberOfRefs = 0;
clear RefPeripherals;
while Index < M_Len
    if ~strcmp(Peripheral(Index),'BlueNRG')
        if NumberOfRefs > 0
            Test = 1;
            for i = 1:NumberOfRefs
                if strcmp(Peripheral(Index),RefPeripherals(i))
                    Test = 0;
                end
            end
               
            if Test == 1
                NumberOfRefs = NumberOfRefs + 1;
                RefPeripherals(NumberOfRefs) = Peripheral(Index);
            end

        else
            NumberOfRefs = 1;
            RefPeripherals(NumberOfRefs) = Peripheral(Index);
        end
    end
    Index = Index + 1;
end
fprintf('%d Refernce Heart Rates Sensors used\n\n',NumberOfRefs);
% begin parsing
Index = 1; count = 1;
r_Len = zeros(NumberOfRefs,1);
for RefNum = 1:NumberOfRefs
    Index = 1; count = 1; ThesePointsAreUseless = 0;
    while (Index < M_Len)  && (ThesePointsAreUseless == 0) 
        while (Index < M_Len) && (~strcmp(Peripheral(Index),RefPeripherals(RefNum)))
            Index = Index + 1;
        end
        if Index < M_Len    % grab refernce heart rate for this peripheral
           j = 1;  %find closest sensor timestamp
            while (j < p_Len) && (Timestamp(Index) > p_AppTimestamp(j))
                j = j + 1;
            end
            if j < p_Len
                r_SensorTimestamp(RefNum,count)     = p_SensorTimestamp(j);
                r_AppTimestamp(RefNum,count)        = Timestamp(Index);
                r_RefHeartPulseRate(RefNum,count)   = MeanHeartPulseRate(Index);
                count = count + 1;
            else
               ThesePointsAreUseless = 1; 
            end

        end
        Index = Index + 1;
    end
    r_Len(RefNum) = count - 1;
end


end


%Parse Accelerometer data into contiguous arrays
fprintf('Parsing Accel Data....\n');
Index = 1; count = 1;Wraps = 0;
while Index < M_Len
    while (Index < M_Len) && (AccTimestamp(Index) == 0)
        Index = Index + 1;
    end
    if Index < M_Len    % grab refernce haeart rate for this peripheral
        a_AppTimestamp(count) =  Timestamp(Index);
        a_AX(count) = AX(Index);
        a_AY(count) = AY(Index);
        a_AZ(count) = AZ(Index);
        Accel(count)  =  norm([(AX(Index)) (AY(Index)) (AZ(Index))]);
        
        if (count > 1)
            if (uint32(AccTimestamp(Index)) + Wraps*2^16) < a_SensorTimestamp(count-1)
                Wraps = Wraps + 1;
            end
        end
        a_SensorTimestamp(count) = uint32(AccTimestamp(Index)) + Wraps*2^16;
        
        count = count + 1;
    end
    Index = Index + 1;
end
a_Len = count - 1;





%% begin processing signal

PreviousNumberOfLEDPulses   = uint8(0);
MovingPRMemory              = single(60);
PulseRateHistory            = zeros([5,1],'uint8');
PulseRatePointer            = uint8(1);


% These are New signals the PPG algorithm will use and create
FilteredDataInput           = zeros([p_Len,1],'single');
PreviousInputVal            = zeros([p_Len,1],'single');
Quadrant                    = zeros([p_Len,1],'uint8');
PreviousQTime               = zeros([p_Len,4],'single'); 
LocalHigh                   = zeros([p_Len,1],'single');
LocalLow                    = zeros([p_Len,1],'single');
Threshold                   = zeros([p_Len,1],'single');
%Timestamp                   = zeros([p_Len,1],'single');
PreviousTimestamp           = zeros([p_Len,1],'single');
RawSensorSum                = zeros([p_Len,1],'single');
MatlabPulseRate             = zeros([p_Len,1],'uint8'); 
MatlabMeanPulseRate         = zeros([p_Len,1],'single');
fprintf('%d Valid SlotA datapoints (~%0.0f Seconds)\n',p_Len,p_Len/25);
fprintf('processing SlotA signal for heart rate...\n');

%Init HRP value for Matlab calculation equal to the first sample from the
% SENtral hardware (log file), which has history befor logging started
PPG_struct.PulseRateHistory = zeros(1,5,'single')+single(p_MeanHeartPulseRate(1));
PPG_struct.MovingPRMemory = p_MeanHeartPulseRate(1);


for Time = 1:p_Len;
        
    % sum the 4 raw photodiode values
    RawSensorSum(Time) =   single(p_SlotA_PD1(Time))...
                         + single(p_SlotA_PD2(Time))...
                         + single(p_SlotA_PD3(Time))...
                         + single(p_SlotA_PD4(Time));

    PPG_struct.Timestamp = p_SlotA_Timestamp(Time);


    
    
    
    [PPG_struct, Filt_struct] = Process_NewPPGData( ...
                                     RawSensorSum(Time),p_NumberLEDPulses(Time), ... 
                                     PPG_struct, Filt_struct);

    
                                 
    
    % store changes in array for later analysis
    FilteredDataInput(Time)  = PPG_struct.FilteredDataInput;
    PreviousInputVal(Time)   = PPG_struct.PreviousInputVal;
    Quadrant(Time)           = PPG_struct.Quadrant;
    PreviousQTime(Time,1:4)  = PPG_struct.PreviousQTime(1:4);
    LocalHigh(Time)          = PPG_struct.LocalHigh;
    LocalLow(Time)           = PPG_struct.LocalLow;
    Threshold(Time)          = PPG_struct.Threshold;
    PreviousTimestamp(Time)  = PPG_struct.PreviousTimestamp;
    MatlabPulseRate(Time)    = PPG_struct.PulseRate;
    MatlabMeanPulseRate(Time)= PPG_struct.MeanPulseRate;

    
    
end % of signal processing


%% Data Analaysis
fprintf('\nGenerating plots...\n');


figure(29);clf;
%Analyize data integrity. 
% This section detects lost (dropped) data packets by looking at the 
% consistancy of SlotA Timestamp deviations 
p_SensorTimestampDelta = zeros(1,p_Len-1,'double');
for i = 2:p_Len
        p_SensorTimestampDelta(i-1) = p_SensorTimestamp(i)- p_SensorTimestamp(i-1);
end
Factor = mode(p_SensorTimestampDelta);
plot(double(p_SensorTimestamp(2:end))/32000,...
    ones(1,p_Len-1)*median(p_SensorTimestampDelta)/Factor-1,...
    'g.','LineWidth',4);hold on;
plot(double(p_SensorTimestamp(2:end))/32000,p_SensorTimestampDelta/Factor-1,'b.','MarkerSize',12);
%ylim([0 5]);
txt = sprintf('Data Integrity Check Plot\n Number of Lost Data Packets Vs. Time. (mode=%f1.1Hz)\n %s',32000/Factor,Filename);
title(txt);
xlabel('seconds');
ylabel('Number of lost data packets');




%Plot Photodiode PPG Waveform
figure(30);clf;
plot(double(p_SensorTimestamp)/32000,p_SlotA_PD1,'b-','LineWidth',2);hold on;
plot(double(p_SensorTimestamp)/32000,p_SlotA_PD2,'r-');hold on;
plot(double(p_SensorTimestamp)/32000,p_SlotA_PD3,'b--');hold on;
plot(double(p_SensorTimestamp)/32000,p_SlotA_PD4,'r--');hold on;
plot(double(p_SensorTimestamp)/32000,RawSensorSum/4,'k--');
legend('PD1','PD2','PD3','PD4','Sum/4');
xlabel('seconds');
ylabel('ADC Value (counts)');
txt = sprintf('Raw Photodiode (PD) signals\n %s',Filename);
title(txt);




figure(31);clf;
plot(double(p_SensorTimestamp)/32000,FilteredDataInput, 'r');hold on;
plot(double(p_SensorTimestamp)/32000,Threshold,'g');hold on;
set(gca,'YGrid','on')
legend('FilteredDataInput','Threshold');
xlabel('seconds');
ylabel('(counts)');
txt = sprintf('Bandpass Filtered PPG Signals\n %s',Filename);
title(txt);





figure(32);clf;
plot(double(p_SensorTimestamp)/32000,p_NumberLEDPulses);
xlabel('seconds');ylabel('Number of LED Pulses');
legend('NumberLEDPulses');
ylim([0 10]);
txt = sprintf('LED Pulses\n %s',Filename);
title(txt);




%% calculate the error rate between Matlab and reference(sample by sample)
aa=find(p_SensorTimestamp>r_SensorTimestamp(1,1));

sensor_index=aa(1); ref_index=1; start_ind=1; end_ind=1;
Error_rate_Matlab_ref = zeros(size(r_SensorTimestamp));
Error_rate_Sentral_ref = zeros(size(r_SensorTimestamp));
for sensor_index= aa(1) :size(p_SensorTimestamp,2)
    
    if p_SensorTimestamp(sensor_index)<= r_SensorTimestamp(ref_index)
        
        sensor_index = sensor_index + 1;
    else
        end_ind = sensor_index;
        
        Error_rate_Matlab_ref(ref_index) = abs(mean(MatlabMeanPulseRate([start_ind end_ind]))-mean(r_RefHeartPulseRate(1,ref_index)));
        Error_rate_Sentral_ref(ref_index) = abs(mean(p_MeanHeartPulseRate([start_ind end_ind]))-mean(r_RefHeartPulseRate(1,ref_index)));
        
        ref_index = ref_index +1;
    end
    
    sensor_index = sensor_index + 1;
    start_ind = sensor_index;
    
    if ref_index > size(r_SensorTimestamp,2)
        break;
        end
end





figure(35);clf;
subplot(4,1,1);
DGrn =  [0 .65 0]; % Dark Green Color
LegendText = {};LegendCount = 0;
% Heart Pluse Rate from SENtrode/SENtral Hardware
    plot(double(p_SensorTimestamp)/32000,p_MeanHeartPulseRate,'r.','MarkerSize',18);hold on;   
    LegendCount = LegendCount + 1; LegendText{LegendCount} =  'SENtral';

% Heart Pluse Rate from Matlab (calculated in this script)
    plot(double(p_SensorTimestamp)/32000,MatlabMeanPulseRate,'b.','MarkerSize',18);hold on;
    LegendCount = LegendCount + 1; LegendText{LegendCount} =  'Matlab';

% Heart Pluse Rate from from Reference Sensor(s)
if RefNum > 0
    plot(single(r_SensorTimestamp(1,:))/32000,r_RefHeartPulseRate(1,:),'g.','MarkerSize',18);hold on;
    LegendCount = LegendCount + 1; LegendText{LegendCount} =  RefPeripherals{1};
    %txt = sprintf('Mean Error of Matlab calculated HPR= %1.1f(BPM)',mean(MatlabMeanPulseRate)-mean(r_RefHeartPulseRate(1,:)));
    txt1 = sprintf('Mean Error of Matlab calculated HPR= %1.1f(BPM)',mean(Error_rate_Matlab_ref));
    txt2 = sprintf('Mean Error of SENtral calculated HPR= %1.1f(BPM)',mean(Error_rate_Sentral_ref));    
    text(10,120,txt1);
    text(10,140,txt2);
end
if RefNum == 2
    plot(single(r_SensorTimestamp(2,:))/32000,r_RefHeartPulseRate(2,:),'.','MarkerFaceColor',DGrn,'MarkerEdgeColor',DGrn);hold on;
    LegendCount = LegendCount + 1; LegendText{LegendCount} =  RefPeripherals{2};
end

txt = sprintf('Heart Pulse Rates from all sources\n %s',Filename);
title(txt);
xlabel('seconds');
ylabel('Heart Pulse Rate (BPM)');
legend(LegendText, 'Location','best');

subplot(4,1,2);
plot(double(a_SensorTimestamp)/32000,Accel,'k-');
title('Relative Movement Detected by Accelerometer');
xlabel('seconds');
ylabel('3-Axis Root-Sum-Square (g-force)');



subplot(4,1,3);
plot(single(r_SensorTimestamp(1,:))/32000,Error_rate_Matlab_ref,'b'),title('Error Rate between Matlab and Reference');
xlabel('seconds');
ylabel('Error Rate (bpm)');

subplot(4,1,4);
plot(single(r_SensorTimestamp(1,:))/32000,Error_rate_Sentral_ref,'r'),title('Error Rate between SENtral and Reference');
xlabel('seconds');
ylabel('Error Rate (bpm)');


fprintf('-- DONE  --\n');
