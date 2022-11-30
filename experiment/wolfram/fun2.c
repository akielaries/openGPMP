int fun(WolframLibraryData libData, mreal A1, mreal *Res) {
  mreal R0_0;
  mreal R0_1;
  R0_0 = A1;
  R0_1 = R0_0 * R0_0;
  MArgument_setReal(Res, R0_1);
  return 0;
}
int fun2(WolframLibraryData libData, mreal A1, mreal *Res) {
  mreal R0_0;
  mreal R0_1;
  int err = 0;
  R0_0 = A1;
  if (I0_0 == 0) {
    if (R0_0 == 0) {
      err = 1;
      goto error_label;
    } else {
      R0_1 = 1;
    }
  } else {
    mint S0 = I0_0;
    mreal S1 = R0_0;
    mbool S2 = 0;
    if (S0 < 0) {
      S2 = 1;
      S0 = -S0;
    }
    R0_1 = 1;
    while (S0) {
      if (S0 & 1) {
        R0_1 = S1 * R0_1;
      }
      S1 = S1 * S1;
      S0 = S0 >> 1;
    }
    if (S2) {
      R0_1 = 1 / R0_1;
    }
  }
  MArgument_setReal(Res, R0_1);
error_label:
  return err;
}
