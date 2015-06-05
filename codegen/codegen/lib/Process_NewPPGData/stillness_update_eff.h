/*
 * stillness_update_eff.h
 *
 * Code generation for function 'stillness_update_eff'
 *
 */

#ifndef __STILLNESS_UPDATE_EFF_H__
#define __STILLNESS_UPDATE_EFF_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Process_NewPPGData_types.h"

/* Function Declarations */
extern void p_data_not_empty_init(void);
extern unsigned char stillness_update_eff(const float acc_sample[3], boolean_T
  turn_on, unsigned char reset_flag);

#endif

/* End of code generation (stillness_update_eff.h) */
