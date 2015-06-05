/*
 * Process_NewPPGData.c
 *
 * Code generation for function 'Process_NewPPGData'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "PulseRateFilter.h"
#include "PPG_algorithm.h"
#include "filterloopBPF07_30_26Hz.h"
#include "rdivide.h"

/* Function Definitions */
void Process_NewPPGData(float RawSensorSum, unsigned char NumberOfLEDPulses,
  struct0_T *PPG_struct, struct1_T *Filt_struct)
{
  float y;
  int i;

  /*  This function is to be called when there is new PPG data */
  /* IF Bias point changes, which can be detected by noticing a change in the */
  /*  number of LED Pulses, then preset BPFilter taps to new datapoint */
  /*  This Filter reset is a quick recovery stategy */
  if (NumberOfLEDPulses != PPG_struct->NumberOfLEDPulses) {
    y = rdivide(RawSensorSum, Filt_struct->k_BPF_GAIN);
    for (i = 0; i < 9; i++) {
      Filt_struct->xv[i] = y;
      Filt_struct->yv[i] = 0.0F;
    }

    PPG_struct->IgnoreFirstPulses = 4;

    /*  notify the pulse rate filter */
  }

  PPG_struct->NumberOfLEDPulses = NumberOfLEDPulses;
  filterloopBPF07_30_26Hz(RawSensorSum, Filt_struct);

  /* BPFilter incoming samples */
  PPG_struct->FilteredDataInput = Filt_struct->yv[8];

  /*  extract results */
  /* Process new datapoint */
  PPG_algorithm(PPG_struct);

  /*  run data through algorithm */
  /*  -Filter Pulse Rate Value (if there is a new one) -*********************** % */
  PulseRateFilter(PPG_struct);

  /* [PPG_struct] = PulseRateFilter_Experimental(PPG_struct); */
  if (PPG_struct->IgnoreFirstPulses > 0) {
    i = PPG_struct->IgnoreFirstPulses - 1;
    if (i < -128) {
      i = -128;
    }

    PPG_struct->IgnoreFirstPulses = (signed char)i;
  }
}

/* End of code generation (Process_NewPPGData.c) */
