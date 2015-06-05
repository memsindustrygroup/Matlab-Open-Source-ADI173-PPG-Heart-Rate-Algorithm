/*
 * PulseRateFilter.c
 *
 * Code generation for function 'PulseRateFilter'
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
#include "median.h"

/* Function Definitions */
void PulseRateFilter(struct0_T *PPG_struct)
{
  int i2;
  unsigned char temp;

  /* ------------------------------------------------------- */
  /*  This function qualifies and filters Raw pulse rate data */
  /*  If the new datapoint qualifiers the value goes into a 5-element queue */
  /*  The median value of this queue is then averaged with historical values */
  /*  The IgnoreFirstPulses is set to 5 when a transient occurs to aid quick */
  /*  and reliable recovery. As on now, only and number-of-LED-Pulses change */
  /*  cuases this to happen. When IgnoreFirstPulses>1 the Mean Value is frozen */
  /*  and the median filter re-prime as this value counts down to 0 after each  */
  /*  consecutive rising zero crossing (quadrant 1) */
  /*  Qualifications: */
  /*  Save the Pulse Rate from Quadrant 1, which comes from the defference of */
  /*  two interpolated timestamps of two consecutive rising zero-crossings. */
  /*  Later when Quadrant 2 phase arrives the Q1 Pulse Rate signal quality can   */
  /*  be better judged because the peak-peak amplitude prior to and after the  */
  /*  zero-crossing becomes available. */
  /* PreQualify All Pulse Rates. PPG_struct.Threshold is a moving mean value */
  if ((PPG_struct->PulseRate > PPG_struct->Knob_MinPulseRate) &&
      (PPG_struct->Threshold > PPG_struct->Knob_Qualified_Threshold)) {
    if (PPG_struct->Quadrant == 1) {
      PPG_struct->LastQ1PulseRate = PPG_struct->PulseRate;
    }

    if (PPG_struct->Quadrant == 2) {
      if (PPG_struct->IgnoreFirstPulses < 1) {
        /* Final Qualification is the min peak-peak amplitude requirement */
        if ((PPG_struct->LocalHigh > PPG_struct->Knob_Qualified_Threshold) &&
            (PPG_struct->LocalLow < 0.0F)) {
          PPG_struct->PulseRateHistory[PPG_struct->PulseRatePointer - 1] =
            PPG_struct->LastQ1PulseRate;
          if (PPG_struct->IgnoreFirstPulses == 0) {
            /*  on the first time back from a transient event use only */
            /*  median value to jump start the mean filter */
            PPG_struct->MovingPRMemory = median(PPG_struct->PulseRateHistory);

            /* Denote that the mean value has been re-initialized */
            PPG_struct->IgnoreFirstPulses = -1;
          } else {
            /*  At all other times use history to mean filter the PR */
            PPG_struct->MovingPRMemory = PPG_struct->MovingPRMemory *
              PPG_struct->Knob_MeanPulseRateTC + median
              (PPG_struct->PulseRateHistory) * (1.0F -
              PPG_struct->Knob_MeanPulseRateTC);
          }

          i2 = (int)(PPG_struct->PulseRatePointer + 1U);
          if ((unsigned int)i2 > 255U) {
            i2 = 255;
          }

          temp = (unsigned char)i2;
          i2 = (int)(PPG_struct->PulseRatePointer + 1U);
          if ((unsigned int)i2 > 255U) {
            i2 = 255;
          }

          PPG_struct->PulseRatePointer = (unsigned char)i2;
          if (temp > PPG_struct->Knob_MedianTaps) {
            PPG_struct->PulseRatePointer = 1;
          }
        }
      } else {
        if (PPG_struct->IgnoreFirstPulses < 5) {
          /*  Prime the buffer. Oldest data starting second lowest element */
          i2 = 5 - PPG_struct->IgnoreFirstPulses;
          if (i2 > 127) {
            i2 = 127;
          }

          i2++;
          if (i2 > 127) {
            i2 = 127;
          }

          PPG_struct->PulseRateHistory[i2 - 1] = PPG_struct->PulseRate;
          PPG_struct->PulseRatePointer = 1;
        }
      }

      /*  of (PPG_struct.IgnoreFirstPulses < 1) */
    }

    /*  of if Quadrant == 2 */
  }

  /*  of PulseRate PreQualification */
  PPG_struct->MeanPulseRate = PPG_struct->MovingPRMemory;
}

/* End of code generation (PulseRateFilter.c) */
