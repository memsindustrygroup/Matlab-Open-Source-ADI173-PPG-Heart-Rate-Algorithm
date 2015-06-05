/*
 * _coder_Process_NewPPGData_api.h
 *
 * Code generation for function 'Process_NewPPGData'
 *
 */

#ifndef ___CODER_PROCESS_NEWPPGDATA_API_H__
#define ___CODER_PROCESS_NEWPPGDATA_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct
{
    real32_T xv[9];
    real32_T yv[9];
    real32_T k_BPF_GAIN;
} struct1_T;
#endif /*typedef_struct1_T*/
#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct
{
    uint8_T Knob_Threshold_Goal;
    real32_T Knob_ThresholdTC;
    uint16_T Knob_Qualified_Threshold;
    real32_T Knob_MeanPulseRateTC;
    uint8_T Knob_MinPulseRate;
    uint8_T Knob_LightExposureGoal;
    uint8_T Knob_LightExposureGoal_H;
    uint8_T Knob_LightExposureGoal_L;
    uint8_T Knob_BiasUpdateInterval;
    uint8_T Knob_AdaptiveBiasGain;
    uint8_T Knob_MedianTaps;
    uint8_T PulseRate;
    real32_T FilteredDataInput;
    real32_T PreviousInputVal;
    uint8_T Quadrant;
    real32_T PreviousQTime[4];
    real32_T LocalHigh;
    real32_T LocalLow;
    real32_T Threshold;
    uint16_T Timestamp;
    uint16_T PreviousTimestamp;
    int8_T IgnoreFirstPulses;
    uint8_T NumberOfLEDPulses;
    real32_T PulseRateHistory[5];
    uint8_T PulseRatePointer;
    real32_T MovingPRMemory;
    uint8_T LastQ1PulseRate;
    real32_T MeanPulseRate;
} struct0_T;
#endif /*typedef_struct0_T*/

/* Function Declarations */
extern void Process_NewPPGData_initialize(emlrtContext *aContext);
extern void Process_NewPPGData_terminate(void);
extern void Process_NewPPGData_atexit(void);
extern void Process_NewPPGData_api(const mxArray * const prhs[4], const mxArray *plhs[2]);
extern void stillness_update_eff_api(const mxArray *prhs[3], const mxArray *plhs[1]);
extern uint8_T stillness_update_eff(real32_T acc_sample[3], boolean_T turn_on, uint8_T reset_flag);
extern void initPPG_struct_api(const mxArray *plhs[1]);
extern struct0_T initPPG_struct(void);
extern void initFilt_struct_api(const mxArray *plhs[1]);
extern struct1_T initFilt_struct(void);
extern void PulseRateFilter_Experimental_api(const mxArray * const prhs[1], const mxArray *plhs[1]);
extern void Process_NewPPGData_xil_terminate(void);
extern void Process_NewPPGData(real32_T RawSensorSum, uint8_T NumberOfLEDPulses, struct0_T *PPG_struct, struct1_T *Filt_struct);
extern void PulseRateFilter_Experimental(struct0_T *PPG_struct);

#endif
/* End of code generation (_coder_Process_NewPPGData_api.h) */
