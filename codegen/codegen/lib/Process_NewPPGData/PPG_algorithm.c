/*
 * PPG_algorithm.c
 *
 * Code generation for function 'PPG_algorithm'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "PPG_algorithm.h"
#include "rdivide.h"

/* Function Declarations */
static float rt_roundf_snf(float u);

/* Function Definitions */
static float rt_roundf_snf(float u)
{
  float y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

void PPG_algorithm(struct0_T *PPG_struct)
{
  float f0;
  unsigned char u1;
  int q0;
  unsigned int qY;
  float Interpolated_zerotime;

  /* % This function process Raw PPG sensor Data to determin a PulseRate   */
  /*  */
  /*  This algorithm is compatible with  */
  /*              Version **   */
  /*       of the PPG embedded code */
  /*  Version 12 removed interpolation from peak detector quadrants 1 and 3. */
  /*            it was incorrect to use linear interp for peak detection. */
  /*  4/14/2015 No longer using Version numbers in the function name(filename) */
  /*             */
  /*  */
  /*  Structure used - For Reference - */
  /*  PPG_struct.PulseRate               = uint8(0); */
  /*  PPG_struct.FilteredDataInput       = single(0); */
  /*  PPG_struct.PreviousInputVal        = single(0); */
  /*  PPG_struct.Quadrant                = uint8(0); */
  /*  PPG_struct.PreviousQTime           = zeros([4,1],'single'); */
  /*  PPG_struct.LocalHigh               = single(0); */
  /*  PPG_struct.LocalLow                = single(0); */
  /*  PPG_struct.Threshold               = single(0); */
  /*  PPG_struct.Timestamp               = uint16(0); */
  /*  PPG_struct.PreviousTimestamp       = uint16(0); */
  /* Knobs */
  /* global Knob_Threshold_Goal Knob_ThresholdTC  */
  /* Constants */
  /*  Timestamp resolution is 31.25us (32KHz) */
  /*  for unwrapping overflowed Timestamps */
  /* Local variables */
  PPG_struct->PulseRate = 0;

  /* %   P U L S E   D E T E C T O R   S T A T E   M A N A G E M E N T % */
  if (PPG_struct->Quadrant == 1) {
    /*  This Quadrant began at the rising zero crossing of systolic pressure */
    /*  This PPG_struct.Quadrant ends at the peak systolic pressure */
    /*  when peak is detected quadrant changes to, and HPR reported as Q2 */
    if (PPG_struct->FilteredDataInput > PPG_struct->Threshold) {
      if (PPG_struct->FilteredDataInput > PPG_struct->LocalHigh) {
        PPG_struct->LocalHigh = PPG_struct->FilteredDataInput;
      } else {
        /*  % Peak Detected */
        if (PPG_struct->PreviousTimestamp > PPG_struct->Timestamp) {
          /*  Fix wrap-around % */
          PPG_struct->PreviousTimestamp = 0;
        }

        /*  The current datapoint is already one datapoint behind the peak */
        /*  datapoint therefore the previoustimestamp is used */
        f0 = rt_roundf_snf(rdivide(1.92E+6F, (float)
          PPG_struct->PreviousTimestamp - PPG_struct->PreviousQTime[0]));
        if (f0 < 256.0F) {
          if (f0 >= 0.0F) {
            u1 = (unsigned char)f0;
          } else {
            u1 = 0;
          }
        } else if (f0 >= 256.0F) {
          u1 = MAX_uint8_T;
        } else {
          u1 = 0;
        }

        PPG_struct->PulseRate = u1;
        PPG_struct->PreviousQTime[0] = PPG_struct->PreviousTimestamp;

        /* Interpolated_zerotime; */
        PPG_struct->Quadrant = 2;

        /*  progress to next PPG_struct.Quadrant state in waveform */
      }
    } else if (PPG_struct->FilteredDataInput < 0.0F) {
      /*  signal must be low is it crossed zero again, reducing threshold... */
      if (PPG_struct->Threshold > PPG_struct->Knob_Threshold_Goal) {
        PPG_struct->Threshold = rdivide(PPG_struct->Threshold, 1.2F);
      } else {
        if (PPG_struct->Threshold > 10.0F) {
          PPG_struct->Threshold = rdivide(PPG_struct->Threshold, 1.02F);
        }
      }
    } else {
      PPG_struct->PreviousInputVal = PPG_struct->FilteredDataInput;
    }
  }

  if (PPG_struct->Quadrant == 2) {
    /*  peak systolic pressure has been detected, this section looks for the zero crossing */
    /*  This PPG_struct.Quadrant cahnges from 2 to 3 when negative  */
    /*  zero-crossing is detected. The calculated pulserate is reported as Q3 */
    /*  pulse rate */
    if (PPG_struct->FilteredDataInput < 0.0F) {
      PPG_struct->Quadrant = 3;

      /*  PEAK DETECTED move to next PPG_struct.Quadrant state */
      if (PPG_struct->PreviousTimestamp > PPG_struct->Timestamp) {
        /*  Fix wrap-around % */
        PPG_struct->PreviousTimestamp = 0;
      }

      /* 		Interpolated_zerotime = single(PPG_struct.PreviousTimestamp) -  (PPG_struct.PreviousInputVal/(PPG_struct.FilteredDataInput - PPG_struct.PreviousInputVal)) *  single(PPG_struct.Timestamp - PPG_struct.PreviousTimestamp); */
      q0 = PPG_struct->Timestamp;
      qY = (unsigned int)q0 - PPG_struct->PreviousTimestamp;
      if (qY > (unsigned int)q0) {
        qY = 0U;
      }

      q0 = (int)qY;
      Interpolated_zerotime = (float)PPG_struct->PreviousTimestamp + rdivide
        (PPG_struct->PreviousInputVal, PPG_struct->PreviousInputVal -
         PPG_struct->FilteredDataInput) * (float)q0;
      if (PPG_struct->PreviousQTime[1] > Interpolated_zerotime) {
        /*  Fix wrap-around % */
        PPG_struct->PreviousQTime[1] -= 65535.0F;
      }

      f0 = rt_roundf_snf(rdivide(1.92E+6F, Interpolated_zerotime -
        PPG_struct->PreviousQTime[1]));
      if (f0 < 256.0F) {
        if (f0 >= 0.0F) {
          u1 = (unsigned char)f0;
        } else {
          u1 = 0;
        }
      } else if (f0 >= 256.0F) {
        u1 = MAX_uint8_T;
      } else {
        u1 = 0;
      }

      PPG_struct->PulseRate = u1;
      PPG_struct->PreviousQTime[1] = Interpolated_zerotime;

      /*   Filter new peak value into Threshold.  */
      /*      If large positive jump then attenuate the change. */
      if (PPG_struct->Knob_ThresholdTC > 1.5F * PPG_struct->Threshold) {
        f0 = rdivide(PPG_struct->Knob_ThresholdTC, 4.0F);
      } else {
        f0 = PPG_struct->Knob_ThresholdTC;
      }

      PPG_struct->Threshold = PPG_struct->Threshold * (1.0F - f0) + rdivide
        (PPG_struct->LocalHigh - PPG_struct->LocalLow, 4.0F) * f0;
      PPG_struct->LocalLow = 0.0F;
    } else {
      PPG_struct->PreviousInputVal = PPG_struct->FilteredDataInput;
    }
  }

  if (PPG_struct->Quadrant == 3) {
    if (PPG_struct->FilteredDataInput < -PPG_struct->Threshold) {
      if (PPG_struct->FilteredDataInput < PPG_struct->LocalLow) {
        PPG_struct->LocalLow = PPG_struct->FilteredDataInput;
      } else {
        /*  Valley detected */
        PPG_struct->Quadrant = 4;

        /*  negative-slope zero cross followed by negative threshold crossing has been achieved - move to state 4 */
        if (PPG_struct->PreviousTimestamp > PPG_struct->Timestamp) {
          /*  Fix wrap-around % */
          PPG_struct->PreviousTimestamp = 0;
        }

        f0 = rt_roundf_snf(rdivide(1.92E+6F, (float)
          PPG_struct->PreviousTimestamp - PPG_struct->PreviousQTime[2]));
        if (f0 < 256.0F) {
          if (f0 >= 0.0F) {
            u1 = (unsigned char)f0;
          } else {
            u1 = 0;
          }
        } else if (f0 >= 256.0F) {
          u1 = MAX_uint8_T;
        } else {
          u1 = 0;
        }

        PPG_struct->PulseRate = u1;
        PPG_struct->PreviousQTime[2] = PPG_struct->PreviousTimestamp;

        /* Interpolated_zerotime; */
      }
    } else if (PPG_struct->FilteredDataInput > 0.0F) {
      /* signal must be low is it crossed zero again, reducing */
      /* threshold... */
      if (PPG_struct->Threshold > PPG_struct->Knob_Threshold_Goal) {
        PPG_struct->Threshold = rdivide(PPG_struct->Threshold, 1.2F);
      } else {
        if (PPG_struct->Threshold > 10.0F) {
          PPG_struct->Threshold = rdivide(PPG_struct->Threshold, 1.02F);
        }
      }
    } else {
      PPG_struct->PreviousInputVal = PPG_struct->FilteredDataInput;
    }
  }

  if (PPG_struct->Quadrant == 4) {
    if (PPG_struct->FilteredDataInput > 0.0F) {
      PPG_struct->Quadrant = 1;
      if (PPG_struct->PreviousTimestamp > PPG_struct->Timestamp) {
        /*  Fix wrap-around % */
        PPG_struct->PreviousTimestamp = 0;
      }

      q0 = PPG_struct->Timestamp;
      qY = (unsigned int)q0 - PPG_struct->PreviousTimestamp;
      if (qY > (unsigned int)q0) {
        qY = 0U;
      }

      q0 = (int)qY;
      Interpolated_zerotime = (float)PPG_struct->PreviousTimestamp + rdivide
        (PPG_struct->PreviousInputVal, PPG_struct->PreviousInputVal -
         PPG_struct->FilteredDataInput) * (float)q0;
      if (PPG_struct->PreviousQTime[3] > Interpolated_zerotime) {
        /*  Fix wrap-around % */
        PPG_struct->PreviousQTime[3] -= 65535.0F;
      }

      f0 = rt_roundf_snf(rdivide(1.92E+6F, Interpolated_zerotime -
        PPG_struct->PreviousQTime[3]));
      if (f0 < 256.0F) {
        if (f0 >= 0.0F) {
          u1 = (unsigned char)f0;
        } else {
          u1 = 0;
        }
      } else if (f0 >= 256.0F) {
        u1 = MAX_uint8_T;
      } else {
        u1 = 0;
      }

      PPG_struct->PulseRate = u1;
      PPG_struct->PreviousQTime[3] = Interpolated_zerotime;

      /*   Filter new peak value into Threshold.  */
      /*      If large positive jump then attenuate the change. */
      if (PPG_struct->Knob_ThresholdTC > 1.5F * PPG_struct->Threshold) {
        f0 = rdivide(PPG_struct->Knob_ThresholdTC, 4.0F);
      } else {
        f0 = PPG_struct->Knob_ThresholdTC;
      }

      PPG_struct->Threshold = PPG_struct->Threshold * (1.0F - f0) + rdivide
        (PPG_struct->LocalHigh - PPG_struct->LocalLow, 4.0F) * f0;
      PPG_struct->LocalHigh = 0.0F;
    } else {
      PPG_struct->PreviousInputVal = PPG_struct->FilteredDataInput;
    }
  }

  PPG_struct->PreviousTimestamp = PPG_struct->Timestamp;

  /*  of function */
}

/* End of code generation (PPG_algorithm.c) */
