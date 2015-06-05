/*
 * filterloopBPF07_30_26Hz.c
 *
 * Code generation for function 'filterloopBPF07_30_26Hz'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "filterloopBPF07_30_26Hz.h"
#include "rdivide.h"

/* Function Definitions */
void filterloopBPF07_30_26Hz(float in, struct1_T *Filt_struct)
{
  float y;

  /*  declarations for codegen: */
  /*  Filt_struct.xv = (static single) 9x1 array */
  /*  Filt_struct.yv = (static single) 9x1 array */
  /*  Filter description */
  /*  filtertype =	Butterworth */
  /*  passtype	 =	Bandpass */
  /*  order      =	4 */
  /*  samplerate = 26.3 */
  /*  corner1	 = .7  (42 BPM) */
  /*  corner2	 = 3   (180 BPM) */
  /* k_GAIN = single(3.283451003e+02); */
  Filt_struct->xv[0] = Filt_struct->xv[1];
  Filt_struct->xv[1] = Filt_struct->xv[2];
  Filt_struct->xv[2] = Filt_struct->xv[3];
  Filt_struct->xv[3] = Filt_struct->xv[4];
  Filt_struct->xv[4] = Filt_struct->xv[5];
  Filt_struct->xv[5] = Filt_struct->xv[6];
  Filt_struct->xv[6] = Filt_struct->xv[7];
  Filt_struct->xv[7] = Filt_struct->xv[8];
  y = rdivide(in, Filt_struct->k_BPF_GAIN);
  Filt_struct->xv[8] = rdivide(in, Filt_struct->k_BPF_GAIN);
  Filt_struct->yv[0] = Filt_struct->yv[1];
  Filt_struct->yv[1] = Filt_struct->yv[2];
  Filt_struct->yv[2] = Filt_struct->yv[3];
  Filt_struct->yv[3] = Filt_struct->yv[4];
  Filt_struct->yv[4] = Filt_struct->yv[5];
  Filt_struct->yv[5] = Filt_struct->yv[6];
  Filt_struct->yv[6] = Filt_struct->yv[7];
  Filt_struct->yv[7] = Filt_struct->yv[8];
  Filt_struct->yv[8] = ((((((((((Filt_struct->xv[0] + y) - 4.0F *
    (Filt_struct->xv[2] + Filt_struct->xv[6])) + 6.0F * Filt_struct->xv[4]) +
    -0.232791543F * Filt_struct->yv[0]) + 2.06102824F * Filt_struct->yv[1]) +
    -8.17670918F * Filt_struct->yv[2]) + 18.9728413F * Filt_struct->yv[3]) +
    -28.1580639F * Filt_struct->yv[4]) + 27.3690758F * Filt_struct->yv[5]) +
                        -17.0074482F * Filt_struct->yv[6]) + 6.17196F *
    Filt_struct->yv[7];

  /* Filter Output is Filt_struct.yv(9); */
  /*  */
  /* http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.htmlend */
  /* filterloopBPF07_30_26Hz(in) */
}

/* End of code generation (filterloopBPF07_30_26Hz.c) */
