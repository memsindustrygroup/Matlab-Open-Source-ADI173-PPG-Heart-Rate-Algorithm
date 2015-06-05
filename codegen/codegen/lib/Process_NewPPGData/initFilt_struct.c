/*
 * initFilt_struct.c
 *
 * Code generation for function 'initFilt_struct'
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
struct1_T initFilt_struct(void)
{
  struct1_T Filt_struct;
  int i;
  for (i = 0; i < 9; i++) {
    Filt_struct.xv[i] = 0.0F;
    Filt_struct.yv[i] = 0.0F;
  }

  /* out = yv(9); */
  Filt_struct.k_BPF_GAIN = 328.345093F;
  return Filt_struct;
}

/* End of code generation (initFilt_struct.c) */
