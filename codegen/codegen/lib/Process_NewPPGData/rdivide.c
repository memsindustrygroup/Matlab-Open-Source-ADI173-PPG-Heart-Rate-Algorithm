/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "rdivide.h"
#include "div.h"

/* Function Definitions */
void b_rdivide(const float x[3], float y, float z[3])
{
  c_div(x, y, z);
}

float rdivide(float x, float y)
{
  return b_div(x, y);
}

/* End of code generation (rdivide.c) */
