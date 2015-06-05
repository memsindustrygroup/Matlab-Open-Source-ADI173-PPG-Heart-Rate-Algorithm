function [Filt_struct] = filterloopBPF07_30_50Hz(in, Filt_struct) 
%#codegen

% declarations for codegen:
% Filt_struct.xv = (static single) 9x1 array
% Filt_struct.yv = (static single) 9x1 array

% Filter description
% filtertype =	Butterworth
% passtype	 =	Bandpass
% order      =	4
% samplerate =  50
% corner1	 =  0.7 (42 BPM)
% corner2	 =  3   (180 BPM)

%k_GAIN = single(3.283451003e+02);

Filt_struct.xv(1) = Filt_struct.xv(2); 
Filt_struct.xv(2) = Filt_struct.xv(3); 
Filt_struct.xv(3) = Filt_struct.xv(4); 
Filt_struct.xv(4) = Filt_struct.xv(5);
Filt_struct.xv(5) = Filt_struct.xv(6); 
Filt_struct.xv(6) = Filt_struct.xv(7); 
Filt_struct.xv(7) = Filt_struct.xv(8); 
Filt_struct.xv(8) = Filt_struct.xv(9); 
Filt_struct.xv(9) = in / Filt_struct.k_BPF_GAIN;

Filt_struct.yv(1) = Filt_struct.yv(2); 
Filt_struct.yv(2) = Filt_struct.yv(3); 
Filt_struct.yv(3) = Filt_struct.yv(4); 
Filt_struct.yv(4) = Filt_struct.yv(5);
Filt_struct.yv(5) = Filt_struct.yv(6); 
Filt_struct.yv(6) = Filt_struct.yv(7); 
Filt_struct.yv(7) = Filt_struct.yv(8); 
Filt_struct.yv(8) = Filt_struct.yv(9); 

Filt_struct.yv(9) =   (Filt_struct.xv(1) + Filt_struct.xv(9)) - 4 ...
     * (Filt_struct.xv(3) + Filt_struct.xv(7)) + 6 * Filt_struct.xv(5) ...
         + ( -0.4684303345 * Filt_struct.yv(1)) ...
         + (  4.0323702084 * Filt_struct.yv(2)) ...
         + ( -15.281819098 * Filt_struct.yv(3)) ...
         + ( 33.3003882100 * Filt_struct.yv(4)) ...
         + (-45.6331075540 * Filt_struct.yv(5)) ...
         + ( 40.2663931630 * Filt_struct.yv(6)) ...
         + (-22.3411132250 * Filt_struct.yv(7)) ...
         + (  7.1253177875 * Filt_struct.yv(8));

%Filter Output is Filt_struct.yv(9);
%
%http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.html

end %filterloopBPF07_30_50Hz(in)