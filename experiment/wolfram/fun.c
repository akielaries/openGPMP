#include "math.h"

#include "WolframRTL.h"

static WolframCompileLibrary_Functions funStructCompile;

static mbool initialize = 1;

#include "fun.h"

DLLEXPORT int Initialize_fun(WolframLibraryData libData) {
    if (initialize) {
        funStructCompile = libData->compileLibraryFunctions;
        initialize       = 0;
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
