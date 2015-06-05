/*
 * stillness_update_eff.c
 *
 * Code generation for function 'stillness_update_eff'
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
#include "rdivide.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  unsigned char acc_n;
  float acc_mean[3];
  float acc_m2[3];
  unsigned char stillness;
  unsigned short stillness_count;
} struct_T;

#endif                                 /*typedef_struct_T*/

/* Variable Definitions */
static struct_T p_data;
static boolean_T p_data_not_empty;

/* Function Declarations */
static float eml_extremum(const float x[3]);

/* Function Definitions */
static float eml_extremum(const float x[3])
{
  float extremum;
  int ixstart;
  int ix;
  boolean_T exitg1;
  ixstart = 1;
  extremum = x[0];
  if (b_isnan(x[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 4)) {
      ixstart = ix;
      if (!b_isnan(x[ix - 1])) {
        extremum = x[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 3) {
    while (ixstart + 1 < 4) {
      if (x[ixstart] > extremum) {
        extremum = x[ixstart];
      }

      ixstart++;
    }
  }

  return extremum;
}

void p_data_not_empty_init(void)
{
  p_data_not_empty = false;
}

unsigned char stillness_update_eff(const float acc_sample[3], boolean_T turn_on,
  unsigned char reset_flag)
{
  unsigned char stillness_output;
  int i0;
  float delta[3];
  float fv0[3];
  float acc_variance;
  unsigned int u0;
  int i;

  /*  Joe's code efficient version */
  /* jm misc counting variable */
  /* jm frame_size = 15; */
  /* jm stillness_threshold = 0.007;  // thisis in M/s^s NOT g's!! */
  /*  preproc mult & division saves code space and time */
  /* jm changed stillness levels */
  /*      (assuming fs=50Hz) */
  /*      1 sample(0.01 seconds) : 0      (default state) */
  /*      15 samples(0.30 seconds) : 1    (based on frame size) */
  /*      100 samples(2.00 seconds) : 2   (first definable level) */
  /* jm   6000 samples(120.0 seconds) : 3 (second definable level) */
  if ((!p_data_not_empty) || (reset_flag != 0)) {
    /* jm        p_data.sample_index = 1; */
    p_data.acc_n = 0;
    p_data_not_empty = true;

    /* jm added uint8() */
    for (i0 = 0; i0 < 3; i0++) {
      p_data.acc_mean[i0] = 0.0F;
      p_data.acc_m2[i0] = 0.0F;
    }

    p_data.stillness = 0;

    /* jm added uint8() */
    p_data.stillness_count = 0;

    /* jt */
  }

  /* moving average and variance of accel */
  i0 = (int)(p_data.acc_n + 1U);
  if ((unsigned int)i0 > 255U) {
    i0 = 255;
  }

  p_data.acc_n = (unsigned char)i0;
  for (i0 = 0; i0 < 3; i0++) {
    delta[i0] = acc_sample[i0] - p_data.acc_mean[i0];
  }

  b_rdivide(delta, p_data.acc_n, fv0);
  for (i0 = 0; i0 < 3; i0++) {
    p_data.acc_mean[i0] += fv0[i0];
    p_data.acc_m2[i0] += delta[i0] * (acc_sample[i0] - p_data.acc_mean[i0]);
  }

  /* process frame */
  /* jm if(p_data.sample_index == frame_size) */
  if (p_data.acc_n == 15) {
    /* jm     p_data.sample_index = 1; */
    /* jm     acc_variance = max(p_data.acc_m2/(p_data.acc_n - 1)); */
    acc_variance = eml_extremum(p_data.acc_m2);

    /* reset moving average */
    p_data.acc_n = 0;
    for (i0 = 0; i0 < 3; i0++) {
      p_data.acc_mean[i0] = 0.0F;
      p_data.acc_m2[i0] = 0.0F;
    }

    if (acc_variance < 0.00328125013F) {
      p_data.stillness = 1;

      /* jm added uint8() */
    } else {
      p_data.stillness = 0;

      /* jm added uint8() */
    }

    /* jm    else */
    /* jm        p_data.sample_index = p_data.sample_index + 1; */
  }

  /*  jt count number of samples stillness observed */
  u0 = p_data.stillness_count + 1U;
  if (u0 > 65535U) {
    u0 = 65535U;
  }

  if (p_data.stillness != 0) {
    p_data.stillness_count = (unsigned short)u0;
  } else {
    p_data.stillness_count = 0;
  }

  /*  jt output data statues 0-3 based on how long it has been still and if */
  /*  the system is enabled via enable bit */
  if (turn_on && (p_data.stillness_count != 0)) {
    /* jm. sum function outputs a double (casting does not change the interim value)  */
    /* jm. stillness_output = uint8(sum(p_data.stillness_count > time_thresholds)) + uint8(1); */
    /* jm. this alt loop summer assures no generation of double-types. */
    stillness_output = 1;
    for (i = 0; i < 2; i++) {
      if (p_data.stillness_count > 85 + 5900 * i) {
        i0 = (int)(stillness_output + 1U);
        if ((unsigned int)i0 > 255U) {
          i0 = 255;
        }

        stillness_output = (unsigned char)i0;
      }
    }
  } else {
    stillness_output = 0;
  }

  return stillness_output;
}

/* End of code generation (stillness_update_eff.c) */
