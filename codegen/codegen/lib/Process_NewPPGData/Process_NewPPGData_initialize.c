/*
 * Process_NewPPGData_initialize.c
 *
 * Code generation for function 'Process_NewPPGData_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "Process_NewPPGData_initialize.h"

/* Function Definitions */
void Process_NewPPGData_initialize(void)
{
  rt_InitInfAndNaN(8U);
  p_data_not_empty_init();
}

/* End of code generation (Process_NewPPGData_initialize.c) */
