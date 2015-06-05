/*
 * _coder_Process_NewPPGData_api.c
 *
 * Code generation for function 'Process_NewPPGData'
 *
 */

/* Include files */
#include "_coder_Process_NewPPGData_api.h"

/* Function Declarations */
static real32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *RawSensorSum, const char_T *identifier);
static real32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static uint8_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *NumberOfLEDPulses, const char_T *identifier);
static uint8_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *PPG_struct,
  const char_T *identifier, struct0_T *y);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y);
static uint16_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4]);
static int8_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[5]);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Filt_struct,
  const char_T *identifier, struct1_T *y);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T *y);
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[9]);
static const mxArray *emlrt_marshallOut(const struct0_T *u);
static const mxArray *b_emlrt_marshallOut(const uint8_T u);
static const mxArray *c_emlrt_marshallOut(const real32_T u);
static const mxArray *d_emlrt_marshallOut(const uint16_T u);
static const mxArray *e_emlrt_marshallOut(const real32_T u[4]);
static const mxArray *f_emlrt_marshallOut(const int8_T u);
static const mxArray *g_emlrt_marshallOut(const real32_T u[5]);
static const mxArray *h_emlrt_marshallOut(const struct1_T *u);
static const mxArray *i_emlrt_marshallOut(const real32_T u[9]);
static real32_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *acc_sample, const char_T *identifier))[3];
static real32_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3];
static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *turn_on,
  const char_T *identifier);
static boolean_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static real32_T r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static uint8_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static uint16_T t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4]);
static int8_T v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[5]);
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[9]);
static real32_T (*y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static boolean_T ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);

/* Function Definitions */
void Process_NewPPGData_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void Process_NewPPGData_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void Process_NewPPGData_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Process_NewPPGData_xil_terminate();
}

void Process_NewPPGData_api(const mxArray * const prhs[4], const mxArray *plhs[2])
{
  real32_T RawSensorSum;
  uint8_T NumberOfLEDPulses;
  struct0_T PPG_struct;
  struct1_T Filt_struct;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  RawSensorSum = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "RawSensorSum");
  NumberOfLEDPulses = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]),
    "NumberOfLEDPulses");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "PPG_struct", &PPG_struct);
  k_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "Filt_struct", &Filt_struct);

  /* Invoke the target function */
  Process_NewPPGData(RawSensorSum, NumberOfLEDPulses, &PPG_struct, &Filt_struct);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&PPG_struct);
  plhs[1] = h_emlrt_marshallOut(&Filt_struct);
}

static real32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *RawSensorSum, const char_T *identifier)
{
  real32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(RawSensorSum), &thisId);
  emlrtDestroyArray(&RawSensorSum);
  return y;
}

static real32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *NumberOfLEDPulses, const char_T *identifier)
{
  uint8_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(NumberOfLEDPulses), &thisId);
  emlrtDestroyArray(&NumberOfLEDPulses);
  return y;
}

static uint8_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  uint8_T y;
  y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *PPG_struct,
  const char_T *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  f_emlrt_marshallIn(sp, emlrtAlias(PPG_struct), &thisId, y);
  emlrtDestroyArray(&PPG_struct);
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[28] = { "Knob_Threshold_Goal",
    "Knob_ThresholdTC", "Knob_Qualified_Threshold", "Knob_MeanPulseRateTC",
    "Knob_MinPulseRate", "Knob_LightExposureGoal", "Knob_LightExposureGoal_H",
    "Knob_LightExposureGoal_L", "Knob_BiasUpdateInterval",
    "Knob_AdaptiveBiasGain", "Knob_MedianTaps", "PulseRate", "FilteredDataInput",
    "PreviousInputVal", "Quadrant", "PreviousQTime", "LocalHigh", "LocalLow",
    "Threshold", "Timestamp", "PreviousTimestamp", "IgnoreFirstPulses",
    "NumberOfLEDPulses", "PulseRateHistory", "PulseRatePointer",
    "MovingPRMemory", "LastQ1PulseRate", "MeanPulseRate" };

  thisId.fParent = parentId;
  emlrtCheckStructR2012b(sp, parentId, u, 28, fieldNames, 0U, 0);
  thisId.fIdentifier = "Knob_Threshold_Goal";
  y->Knob_Threshold_Goal = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "Knob_Threshold_Goal")), &thisId);
  thisId.fIdentifier = "Knob_ThresholdTC";
  y->Knob_ThresholdTC = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "Knob_ThresholdTC")), &thisId);
  thisId.fIdentifier = "Knob_Qualified_Threshold";
  y->Knob_Qualified_Threshold = g_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_Qualified_Threshold")), &thisId);
  thisId.fIdentifier = "Knob_MeanPulseRateTC";
  y->Knob_MeanPulseRateTC = b_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_MeanPulseRateTC")), &thisId);
  thisId.fIdentifier = "Knob_MinPulseRate";
  y->Knob_MinPulseRate = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "Knob_MinPulseRate")), &thisId);
  thisId.fIdentifier = "Knob_LightExposureGoal";
  y->Knob_LightExposureGoal = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_LightExposureGoal")), &thisId);
  thisId.fIdentifier = "Knob_LightExposureGoal_H";
  y->Knob_LightExposureGoal_H = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_LightExposureGoal_H")), &thisId);
  thisId.fIdentifier = "Knob_LightExposureGoal_L";
  y->Knob_LightExposureGoal_L = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_LightExposureGoal_L")), &thisId);
  thisId.fIdentifier = "Knob_BiasUpdateInterval";
  y->Knob_BiasUpdateInterval = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_BiasUpdateInterval")), &thisId);
  thisId.fIdentifier = "Knob_AdaptiveBiasGain";
  y->Knob_AdaptiveBiasGain = d_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "Knob_AdaptiveBiasGain")), &thisId);
  thisId.fIdentifier = "Knob_MedianTaps";
  y->Knob_MedianTaps = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "Knob_MedianTaps")), &thisId);
  thisId.fIdentifier = "PulseRate";
  y->PulseRate = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "PulseRate")), &thisId);
  thisId.fIdentifier = "FilteredDataInput";
  y->FilteredDataInput = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "FilteredDataInput")), &thisId);
  thisId.fIdentifier = "PreviousInputVal";
  y->PreviousInputVal = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "PreviousInputVal")), &thisId);
  thisId.fIdentifier = "Quadrant";
  y->Quadrant = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "Quadrant")), &thisId);
  thisId.fIdentifier = "PreviousQTime";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "PreviousQTime")), &thisId, y->PreviousQTime);
  thisId.fIdentifier = "LocalHigh";
  y->LocalHigh = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "LocalHigh")), &thisId);
  thisId.fIdentifier = "LocalLow";
  y->LocalLow = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "LocalLow")), &thisId);
  thisId.fIdentifier = "Threshold";
  y->Threshold = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "Threshold")), &thisId);
  thisId.fIdentifier = "Timestamp";
  y->Timestamp = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "Timestamp")), &thisId);
  thisId.fIdentifier = "PreviousTimestamp";
  y->PreviousTimestamp = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "PreviousTimestamp")), &thisId);
  thisId.fIdentifier = "IgnoreFirstPulses";
  y->IgnoreFirstPulses = i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "IgnoreFirstPulses")), &thisId);
  thisId.fIdentifier = "NumberOfLEDPulses";
  y->NumberOfLEDPulses = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a
    (sp, u, 0, "NumberOfLEDPulses")), &thisId);
  thisId.fIdentifier = "PulseRateHistory";
  j_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "PulseRateHistory")), &thisId, y->PulseRateHistory);
  thisId.fIdentifier = "PulseRatePointer";
  y->PulseRatePointer = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "PulseRatePointer")), &thisId);
  thisId.fIdentifier = "MovingPRMemory";
  y->MovingPRMemory = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "MovingPRMemory")), &thisId);
  thisId.fIdentifier = "LastQ1PulseRate";
  y->LastQ1PulseRate = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "LastQ1PulseRate")), &thisId);
  thisId.fIdentifier = "MeanPulseRate";
  y->MeanPulseRate = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u,
    0, "MeanPulseRate")), &thisId);
  emlrtDestroyArray(&u);
}

static uint16_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  uint16_T y;
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4])
{
  u_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int8_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  int8_T y;
  y = v_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[5])
{
  w_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Filt_struct,
  const char_T *identifier, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  l_emlrt_marshallIn(sp, emlrtAlias(Filt_struct), &thisId, y);
  emlrtDestroyArray(&Filt_struct);
}

static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[3] = { "xv", "yv", "k_BPF_GAIN" };

  thisId.fParent = parentId;
  emlrtCheckStructR2012b(sp, parentId, u, 3, fieldNames, 0U, 0);
  thisId.fIdentifier = "xv";
  m_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "xv")),
                     &thisId, y->xv);
  thisId.fIdentifier = "yv";
  m_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "yv")),
                     &thisId, y->yv);
  thisId.fIdentifier = "k_BPF_GAIN";
  y->k_BPF_GAIN = b_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "k_BPF_GAIN")), &thisId);
  emlrtDestroyArray(&u);
}

static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[9])
{
  x_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *emlrt_marshallOut(const struct0_T *u)
{
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_Threshold_Goal),
                "Knob_Threshold_Goal", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->Knob_ThresholdTC), "Knob_ThresholdTC",
                0);
  emlrtAddField(y, d_emlrt_marshallOut(u->Knob_Qualified_Threshold),
                "Knob_Qualified_Threshold", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->Knob_MeanPulseRateTC),
                "Knob_MeanPulseRateTC", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_MinPulseRate),
                "Knob_MinPulseRate", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_LightExposureGoal),
                "Knob_LightExposureGoal", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_LightExposureGoal_H),
                "Knob_LightExposureGoal_H", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_LightExposureGoal_L),
                "Knob_LightExposureGoal_L", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_BiasUpdateInterval),
                "Knob_BiasUpdateInterval", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_AdaptiveBiasGain),
                "Knob_AdaptiveBiasGain", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Knob_MedianTaps), "Knob_MedianTaps", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->PulseRate), "PulseRate", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->FilteredDataInput),
                "FilteredDataInput", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->PreviousInputVal), "PreviousInputVal",
                0);
  emlrtAddField(y, b_emlrt_marshallOut(u->Quadrant), "Quadrant", 0);
  emlrtAddField(y, e_emlrt_marshallOut(u->PreviousQTime), "PreviousQTime", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->LocalHigh), "LocalHigh", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->LocalLow), "LocalLow", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->Threshold), "Threshold", 0);
  emlrtAddField(y, d_emlrt_marshallOut(u->Timestamp), "Timestamp", 0);
  emlrtAddField(y, d_emlrt_marshallOut(u->PreviousTimestamp),
                "PreviousTimestamp", 0);
  emlrtAddField(y, f_emlrt_marshallOut(u->IgnoreFirstPulses),
                "IgnoreFirstPulses", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->NumberOfLEDPulses),
                "NumberOfLEDPulses", 0);
  emlrtAddField(y, g_emlrt_marshallOut(u->PulseRateHistory), "PulseRateHistory",
                0);
  emlrtAddField(y, b_emlrt_marshallOut(u->PulseRatePointer), "PulseRatePointer",
                0);
  emlrtAddField(y, c_emlrt_marshallOut(u->MovingPRMemory), "MovingPRMemory", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->LastQ1PulseRate), "LastQ1PulseRate", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->MeanPulseRate), "MeanPulseRate", 0);
  return y;
}

static const mxArray *b_emlrt_marshallOut(const uint8_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateNumericMatrix(1, 1, mxUINT8_CLASS, mxREAL);
  *(uint8_T *)mxGetData(m0) = u;
  emlrtAssign(&y, m0);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const real32_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)mxGetData(m1) = u;
  emlrtAssign(&y, m1);
  return y;
}

static const mxArray *d_emlrt_marshallOut(const uint16_T u)
{
  const mxArray *y;
  const mxArray *m2;
  y = NULL;
  m2 = emlrtCreateNumericMatrix(1, 1, mxUINT16_CLASS, mxREAL);
  *(uint16_T *)mxGetData(m2) = u;
  emlrtAssign(&y, m2);
  return y;
}

static const mxArray *e_emlrt_marshallOut(const real32_T u[4])
{
  const mxArray *y;
  static const int32_T iv0[1] = { 4 };

  const mxArray *m3;
  real32_T *pData;
  int32_T i;
  y = NULL;
  m3 = emlrtCreateNumericArray(1, iv0, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m3);
  for (i = 0; i < 4; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m3);
  return y;
}

static const mxArray *f_emlrt_marshallOut(const int8_T u)
{
  const mxArray *y;
  const mxArray *m4;
  y = NULL;
  m4 = emlrtCreateNumericMatrix(1, 1, mxINT8_CLASS, mxREAL);
  *(int8_T *)mxGetData(m4) = u;
  emlrtAssign(&y, m4);
  return y;
}

static const mxArray *g_emlrt_marshallOut(const real32_T u[5])
{
  const mxArray *y;
  static const int32_T iv1[2] = { 1, 5 };

  const mxArray *m5;
  real32_T *pData;
  int32_T i;
  y = NULL;
  m5 = emlrtCreateNumericArray(2, iv1, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m5);
  for (i = 0; i < 5; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m5);
  return y;
}

static const mxArray *h_emlrt_marshallOut(const struct1_T *u)
{
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  emlrtAddField(y, i_emlrt_marshallOut(u->xv), "xv", 0);
  emlrtAddField(y, i_emlrt_marshallOut(u->yv), "yv", 0);
  emlrtAddField(y, c_emlrt_marshallOut(u->k_BPF_GAIN), "k_BPF_GAIN", 0);
  return y;
}

static const mxArray *i_emlrt_marshallOut(const real32_T u[9])
{
  const mxArray *y;
  static const int32_T iv2[1] = { 9 };

  const mxArray *m6;
  real32_T *pData;
  int32_T i;
  y = NULL;
  m6 = emlrtCreateNumericArray(1, iv2, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m6);
  for (i = 0; i < 9; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m6);
  return y;
}

void stillness_update_eff_api(const mxArray *prhs[3], const mxArray *plhs[1])
{
  real32_T (*acc_sample)[3];
  boolean_T turn_on;
  uint8_T reset_flag;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  acc_sample = n_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "acc_sample");
  turn_on = p_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "turn_on");
  reset_flag = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "reset_flag");

  /* Invoke the target function */
  reset_flag = stillness_update_eff(*acc_sample, turn_on, reset_flag);

  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(reset_flag);
}

static real32_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *acc_sample, const char_T *identifier))[3]
{
  real32_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = o_emlrt_marshallIn(sp, emlrtAlias(acc_sample), &thisId);
  emlrtDestroyArray(&acc_sample);
  return y;
}
  static real32_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  real32_T (*y)[3];
  y = y_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *turn_on,
  const char_T *identifier)
{
  boolean_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = q_emlrt_marshallIn(sp, emlrtAlias(turn_on), &thisId);
  emlrtDestroyArray(&turn_on);
  return y;
}

static boolean_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  boolean_T y;
  y = ab_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

void initPPG_struct_api(const mxArray *plhs[1])
{
  struct0_T PPG_struct;

  /* Invoke the target function */
  PPG_struct = initPPG_struct();

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&PPG_struct);
}

void initFilt_struct_api(const mxArray *plhs[1])
{
  struct1_T Filt_struct;

  /* Invoke the target function */
  Filt_struct = initFilt_struct();

  /* Marshall function outputs */
  plhs[0] = h_emlrt_marshallOut(&Filt_struct);
}

void PulseRateFilter_Experimental_api(const mxArray * const prhs[1], const
  mxArray *plhs[1])
{
  struct0_T PPG_struct;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "PPG_struct", &PPG_struct);

  /* Invoke the target function */
  PulseRateFilter_Experimental(&PPG_struct);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&PPG_struct);
}

static real32_T r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real32_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 0U, 0);
  ret = *(real32_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static uint8_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  uint8_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint8", false, 0U, 0);
  ret = *(uint8_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static uint16_T t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  uint16_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint16", false, 0U, 0);
  ret = *(uint16_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4])
{
  int32_T iv3[1];
  int32_T i0;
  iv3[0] = 4;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 1U, iv3);
  for (i0 = 0; i0 < 4; i0++) {
    ret[i0] = (*(real32_T (*)[4])mxGetData(src))[i0];
  }

  emlrtDestroyArray(&src);
}

static int8_T v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  int8_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "int8", false, 0U, 0);
  ret = *(int8_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[5])
{
  int32_T iv4[2];
  int32_T i1;
  for (i1 = 0; i1 < 2; i1++) {
    iv4[i1] = 1 + (i1 << 2);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 2U, iv4);
  for (i1 = 0; i1 < 5; i1++) {
    ret[i1] = (*(real32_T (*)[5])mxGetData(src))[i1];
  }

  emlrtDestroyArray(&src);
}

static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[9])
{
  int32_T iv5[1];
  int32_T i2;
  iv5[0] = 9;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 1U, iv5);
  for (i2 = 0; i2 < 9; i2++) {
    ret[i2] = (*(real32_T (*)[9])mxGetData(src))[i2];
  }

  emlrtDestroyArray(&src);
}

static real32_T (*y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real32_T (*ret)[3];
  int32_T iv6[2];
  int32_T i3;
  for (i3 = 0; i3 < 2; i3++) {
    iv6[i3] = 1 + (i3 << 1);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 2U, iv6);
  ret = (real32_T (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static boolean_T ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  boolean_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "logical", false, 0U, 0);
  ret = *mxGetLogicals(src);
  emlrtDestroyArray(&src);
  return ret;
}

/* End of code generation (_coder_Process_NewPPGData_api.c) */
