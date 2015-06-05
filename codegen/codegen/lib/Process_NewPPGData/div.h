/*
 * div.h
 *
 * Code generation for function 'div'
 *
 */

#ifndef __DIV_H__
#define __DIV_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Process_NewPPGData_types.h"

/* Function Declarations */
extern float b_div(float x, float y);
extern void c_div(const float x[3], float y, float z[3]);

#endif

/* End of code generation (div.h) */
