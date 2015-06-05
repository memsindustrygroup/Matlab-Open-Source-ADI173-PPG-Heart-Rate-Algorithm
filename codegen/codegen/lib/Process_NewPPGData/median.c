/*
 * median.c
 *
 * Code generation for function 'median'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Process_NewPPGData.h"
#include "PulseRateFilter_Experimental.h"
#include "initFilt_struct.h"
#include "initPPG_struct.h"
#include "stillness_update_eff.h"
#include "median.h"
#include "isnan.h"

/* Function Declarations */
static void eml_sort_idx(const float x[5], int idx[5]);
static float vectormedian(const float v[5]);

/* Function Definitions */
static void eml_sort_idx(const float x[5], int idx[5])
{
  int k;
  boolean_T p;
  signed char idx0[5];
  int i;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  for (k = 0; k < 5; k++) {
    idx[k] = k + 1;
  }

  for (k = 0; k < 3; k += 2) {
    if ((x[k] <= x[k + 1]) || b_isnan(x[k + 1])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
    } else {
      idx[k] = k + 2;
      idx[k + 1] = k + 1;
    }
  }

  for (i = 0; i < 5; i++) {
    idx0[i] = 1;
  }

  i = 2;
  while (i < 5) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 6; pEnd = qEnd + i) {
      b_p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > 6) {
        qEnd = 6;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if ((x[idx[b_p - 1] - 1] <= x[idx[q] - 1]) || b_isnan(x[idx[q] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          idx0[k] = (signed char)idx[b_p - 1];
          b_p++;
          if (b_p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              idx0[k] = (signed char)idx[q];
              q++;
            }
          }
        } else {
          idx0[k] = (signed char)idx[q];
          q++;
          if (q + 1 == qEnd) {
            while (b_p < pEnd) {
              k++;
              idx0[k] = (signed char)idx[b_p - 1];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx[(j + k) - 1] = idx0[k];
      }

      j = qEnd;
    }

    i = i2;
  }
}

static float vectormedian(const float v[5])
{
  float m;
  int idx[5];
  eml_sort_idx(v, idx);
  if (b_isnan(v[idx[4] - 1])) {
    m = v[idx[4] - 1];
  } else {
    m = v[idx[2] - 1];
  }

  return m;
}

float median(const float x[5])
{
  return vectormedian(x);
}

/* End of code generation (median.c) */
