/*
 * initPPG_struct.c
 *
 * Code generation for function 'initPPG_struct'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"

/* Function Definitions */
struct0_T initPPG_struct(void)
{
  struct0_T PPG_struct;
  int i;

  /*   UNTITLED Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  ------------------ KNOBS ------------------------------------     */
  PPG_struct.Knob_Threshold_Goal = 150;

  /*  Target threshold level */
  PPG_struct.Knob_ThresholdTC = 0.05F;

  /*  Time const used in moving mean filter */
  PPG_struct.Knob_Qualified_Threshold = 15;

  /*  Pulse amplitude qualification threshold for Pulse Rate Filter */
  PPG_struct.Knob_MeanPulseRateTC = 0.985F;
  PPG_struct.Knob_MinPulseRate = 20;

  /*  for Pulse Rate qualification */
  PPG_struct.Knob_LightExposureGoal = 180;
  PPG_struct.Knob_LightExposureGoal_H = 200;
  PPG_struct.Knob_LightExposureGoal_L = 90;
  PPG_struct.Knob_BiasUpdateInterval = 25;
  PPG_struct.Knob_AdaptiveBiasGain = 16;

  /* PPG_struct.Knob_ThreshGoalGain      = single(7.0); */
  PPG_struct.Knob_MedianTaps = 5;

  /*  ---------- PulseRate Calculations ----------------------    */
  PPG_struct.PulseRate = 0;
  PPG_struct.FilteredDataInput = 0.0F;
  PPG_struct.PreviousInputVal = 0.0F;
  PPG_struct.Quadrant = 1;
  for (i = 0; i < 4; i++) {
    PPG_struct.PreviousQTime[i] = 0.0F;
  }

  PPG_struct.LocalHigh = 0.0F;
  PPG_struct.LocalLow = 0.0F;
  PPG_struct.Threshold = 0.0F;
  PPG_struct.Timestamp = 0;
  PPG_struct.PreviousTimestamp = 0;
  PPG_struct.IgnoreFirstPulses = 6;
  PPG_struct.NumberOfLEDPulses = 0;

  /*  ---------- PulseRate Filter Variables ---------------------- */
  for (i = 0; i < 5; i++) {
    PPG_struct.PulseRateHistory[i] = 0.0F;
  }

  PPG_struct.PulseRatePointer = 1;
  PPG_struct.MovingPRMemory = 0.0F;
  PPG_struct.LastQ1PulseRate = 0;
  PPG_struct.MeanPulseRate = 0.0F;
  return PPG_struct;
}

/* End of code generation (initPPG_struct.c) */
