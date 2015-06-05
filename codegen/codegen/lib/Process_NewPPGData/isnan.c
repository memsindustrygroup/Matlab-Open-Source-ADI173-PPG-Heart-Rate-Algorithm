/*
 * isnan.c
 *
 * Code generation for function 'isnan'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "isnan.h"

/* Function Definitions */
boolean_T b_isnan(float x)
{
  return rtIsNaNF(x);
}

/* End of code generation (isnan.c) */
