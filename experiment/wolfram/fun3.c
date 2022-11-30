#include "math.h"

#include "WolframRTL.h"

static WolframCompileLibrary_Functions funStructCompile;

static mint I1_0;

static mbool initialize = 1;

#include "fun.h"

DLLEXPORT int Initialize_fun(WolframLibraryData libData) {
  if (initialize) {
    funStructCompile = libData->compileLibraryFunctions;
    I1_0 = (mint)3;
    initialize = 0;
  }
  return 0;
}

DLLEXPORT void Uninitialize_fun(WolframLibraryData libData) {
  if (!initialize) {
    initialize = 1;
  }
}

DLLEXPORT int fun(WolframLibraryData libData, mreal A1, mreal *Res) {
  mreal R0_0;
  mreal R0_1;
  R0_0 = A1;
  R0_1 = R0_0 * R0_0;
  *Res = R0_1;
  funStructCompile->WolframLibraryData_cleanUp(libData, 1);
  return 0;
}

DLLEXPORT int fun1(WolframLibraryData libData, mreal A1, mreal *Res) {
  mreal R1_0;
  mreal R1_1;
  int err = 0;
  R1_0 = A1;
  if (I1_0 == 0) {
    if (R1_0 == 0) {
      err = 1;
      goto error_label;
    } else {
      R1_1 = 1;
    }
  } else {
    mint S0 = I1_0;
    mreal S1 = R1_0;
    mbool S2 = 0;
    if (S0 < 0) {
      S2 = 1;
      S0 = -S0;
    }
    R1_1 = 1;
    while (S0) {
      if (S0 & 1) {
        R1_1 = S1 * R1_1;
      }
      S1 = S1 * S1;
      S0 = S0 >> 1;
    }
    if (S2) {
      R1_1 = 1 / R1_1;
    }
  }
  *Res = R1_1;
error_label:
  funStructCompile->WolframLibraryData_cleanUp(libData, 1);
  return err;
}
