/*
 * div.c
 *
 * Code generation for function 'div'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "div.h"

/* Function Definitions */
float b_div(float x, float y)
{
  return x / y;
}

void c_div(const float x[3], float y, float z[3])
{
  int i1;
  for (i1 = 0; i1 < 3; i1++) {
    z[i1] = x[i1] / y;
  }
}

/* End of code generation (div.c) */
