/*
 * Process_NewPPGData_types.h
 *
 * Code generation for function 'Process_NewPPGData'
 *
 */

#ifndef __PROCESS_NEWPPGDATA_TYPES_H__
#define __PROCESS_NEWPPGDATA_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct
{
    unsigned char Knob_Threshold_Goal;
    float Knob_ThresholdTC;
    unsigned short Knob_Qualified_Threshold;
    float Knob_MeanPulseRateTC;
    unsigned char Knob_MinPulseRate;
    unsigned char Knob_LightExposureGoal;
    unsigned char Knob_LightExposureGoal_H;
    unsigned char Knob_LightExposureGoal_L;
    unsigned char Knob_BiasUpdateInterval;
    unsigned char Knob_AdaptiveBiasGain;
    unsigned char Knob_MedianTaps;
    unsigned char PulseRate;
    float FilteredDataInput;
    float PreviousInputVal;
    unsigned char Quadrant;
    float PreviousQTime[4];
    float LocalHigh;
    float LocalLow;
    float Threshold;
    unsigned short Timestamp;
    unsigned short PreviousTimestamp;
    signed char IgnoreFirstPulses;
    unsigned char NumberOfLEDPulses;
    float PulseRateHistory[5];
    unsigned char PulseRatePointer;
    float MovingPRMemory;
    unsigned char LastQ1PulseRate;
    float MeanPulseRate;
} struct0_T;
#endif /*typedef_struct0_T*/
#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct
{
    float xv[9];
    float yv[9];
    float k_BPF_GAIN;
} struct1_T;
#endif /*typedef_struct1_T*/

#endif
/* End of code generation (Process_NewPPGData_types.h) */
