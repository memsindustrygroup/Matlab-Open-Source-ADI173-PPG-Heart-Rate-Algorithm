%emlc CompileAlgorithm -eg {[0 0 0]',[0 0 0]',[0 0 0]',0}  -c -report -T rtw:lib


% Switch to current directory & restore default path
p = mfilename('fullpath');
[pathstr, name, ext] = fileparts(p)
cd(pathstr)
restoredefaultpath
% warning on

close all
clear all

commandwindow

fprintf('\nGenerating AutoCode...\n')
warning off


% load 'SPwrap_sample_data.mat'; % load sample data variables
addpath('em_overrides_direct'); % only add this path

%%% real time workshop config object
% rtwcfg = emlcoder.RTWConfig;
% rtwcfg = emlcoder.RTWConfig('ert'); % Engineering Laptop ert setting
cfg = coder.config('lib');
% cfg = coder.config('lib','ecoder',false);
% rtwcfg.ObjectivePriorities = 'Efficiency';
cfg.FilePartitionMethod = 'MapMFileToCFile'; % MapMFileToCFile or SingleFile
cfg.CCompilerOptimization = 'Off';
cfg.EnableVariableSizing = true;
cfg.InlineThreshold = int32(0);
cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM Cortex';
cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM Cortex';
cfg.HardwareImplementation.ProdLargestAtomicFloat = 'Float';
cfg.GenCodeOnly = true;

% set to tool chain configuration - to remove code gen warning
cfg.GenerateMakefile = true;
cfg.MakeCommand = 'make_rtw';
cfg.TemplateMakefile = 'default_tmf';
cfg.CCompilerOptimization = 'Off';

PPG_struct = initPPG_struct;
Filt_struct = initFilt_struct50;
RawSensorSum = single(0);
NumberOfLEDPulses = uint8(0);
Stillness_Output = uint8(0);
AccelData = zeros(1,3,'single');
ResetFlag = uint8(0);
turn_on = false;

codegen  Process_NewPPGData -args {RawSensorSum, NumberOfLEDPulses,PPG_struct, Filt_struct}...
         stillness_update_eff -args {AccelData, turn_on, ResetFlag} ...
         initPPG_struct ...
         initFilt_struct ...
         -config cfg -c -report

     
     
fprintf('\nCode Generation Complete!\n')



