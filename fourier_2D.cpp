/*
Copyright (c) 2004-2007, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

// working with fixed sizes for simplicity in this tutorial
const int W = 128; //the width of the image
const int H = 128; //the height of the image

double fRe[H][W][3], fIm[H][W][3], fAmp[H][W][3]; //the signal's real part, imaginary part, and amplitude
double FRe[H][W][3], FIm[H][W][3], FAmp[H][W][3]; //the FT's real part, imaginary part and amplitude
double fRe2[H][W][3], fIm2[H][W][3], fAmp2[H][W][3]; //will become the signal again after IDFT of the spectrum
double FRe2[H][W][3], FIm2[H][W][3], FAmp2[H][W][3]; //filtered spectrum

double pi = 3.1415926535897932384626433832795;

void draw(int xpos, int yPos, int w, int h, const double *g, bool shift, bool neg128);
void DFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm);
void FFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm);
void calculateAmp(int w, int h, double *ga, const double *gRe, const double *gIm);

int main(int /*argc*/, char */*argv*/[])
{
  screen(3 * W,4 * H + 8, 0,"2D FFT and Filters");
  std::vector<ColorRGB> img;
  unsigned long dummyw, dummyh;
  if(loadImage(img, dummyw, dummyh, "pics/test.png"))
  {
    print("image pics/test.png not found");
    redraw();
    sleep();
    cls();
  }
  //set signal to the image
  for(int y = 0; y < H; y++)
  for(int x = 0; x < W; x++)
  {
    fRe[y][x][0] = img[W * y + x].r;
    fRe[y][x][1] = img[W * y + x].g;
    fRe[y][x][2] = img[W * y + x].b;
  }

  int ytrans=8; //translate everything a bit down to put the text on top

  //set new FT buffers
  for(int x = 0; x < W; x++)
  for(int y = 0; y < H; y++)
  for(int c = 0; c < 3; c++)
  {
    FRe2[y][x][c] = FRe[y][x][c];
    FIm2[y][x][c] = FIm[y][x][c];
  }

  bool changed = 1, endloop = 0;
  while(!endloop)
  {
    if(done()) end();
    readKeys();
    if(keyPressed(SDLK_z) || changed) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[y][x][c];} changed = 1;} //no effect
    if(keyPressed(SDLK_a)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = 255 - fRe[y][x][c];} changed = 1;} //negative
    if(keyPressed(SDLK_b)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[y][x][c]/2;} changed = 1;} //half amplitude
    if(keyPressed(SDLK_c)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x % 4 == 0) || (y%4 == 0)) {fRe2[y][x][c] = 0;} else{fRe2[y][x][c] = fRe[y][x][c];}} changed = 1;} //grid
    if(keyPressed(SDLK_d)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x % 8 == 0) || (y%8 == 0)) {fRe2[y][x][c] = 0;} else{fRe2[y][x][c] = fRe[y][x][c];}} changed = 1;} //grid
    if(keyPressed(SDLK_e)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x % 16 == 0) || (y%16 == 0)) {fRe2[y][x][c] = 0;} else{fRe2[y][x][c] = fRe[y][x][c];}} changed = 1;} //grid
    if(keyPressed(SDLK_f)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x % 32==0) || (y%32==0)) {fRe2[y][x][c] = 0;} else{fRe2[y][x][c] = fRe[y][x][c];}} changed = 1;} //grid
    if(keyPressed(SDLK_g)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = 128 + 128 * sin(3.1415*x / 8.0);} changed = 1;} //grid
    if(keyPressed(SDLK_h)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = 128 + 128 * sin(3.1415*y / 8.0);} changed = 1;} //grid
    if(keyPressed(SDLK_i)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = 128 + 128 * sin(3.1415*(x + y) / 8.0);} changed = 1;} //grid
    if(keyPressed(SDLK_j)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) {fRe2[y][x][0] = 128 + 128 * sin(3.1415*x / 8.0); fRe2[y][x][1] = 128 + 128 * sin(3.1415*y / 8.0); fRe2[y][x][2] = 128 + 128 * sin(3.1415*(x + y) / 8.0);} changed = 1;} //grid
    if(keyPressed(SDLK_k)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[(x+W/8) % W][(y+H/8) % H][c];} changed = 1;} //translate image
    if(keyPressed(SDLK_l)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[(x+W/4) % W][(y+H/4) % H][c];} changed = 1;} //translate image
    if(keyPressed(SDLK_m)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[(x+W / 2) % W][(y+H / 2) % H][c];} changed = 1;} //translate image
    if(keyPressed(SDLK_n)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fRe2[y][x][c] = fRe[(x + y) % W][y][c];} changed = 1;} //skew image
    if(keyPressed(SDLK_o)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < W / 2 + 4&& x > W / 2 - 4) && (y < H / 2 + 4 && y > H / 2 - 4)) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //square
    if(keyPressed(SDLK_p)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < W / 2 + 8&& x > W / 2 - 8) && (y < H / 2 + 8 && y > H / 2 - 8)) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //square
    if(keyPressed(SDLK_q)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < W / 2 + 16 && x > W / 2 - 16) && (y < H / 2 + 16 && y > H / 2 - 16)) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //square
    if(keyPressed(SDLK_r)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < W / 2 + 32 && x > W / 2 - 32) && (y < H / 2 + 32 && y > H / 2 - 32)) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //square
    if(keyPressed(SDLK_s)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x + y <(W+H)/2) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //triangle
    if(keyPressed(SDLK_t)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x - W / 2) * (x - W / 2) + (y - H / 2) * (y - H / 2) < 64 || (W - (x - W / 2)) * (W - (x - W / 2)) + (H - (y - H / 2)) * (H - (y - H / 2)) < 64 || (x - W / 2) * (x - W / 2) + (H - (y - H / 2)) * (H - (y - H / 2)) < 64 || (W - (x - W / 2)) *(W - (x - W / 2)) + (y - H / 2) *(y - H / 2) < 64) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //circle
    if(keyPressed(SDLK_u)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x - W / 2) * (x - W / 2) + (y - H / 2) * (y - H / 2) < 512 || (W - (x - W / 2)) * (W - (x - W / 2)) + (H - (y - H / 2)) *(H - (y - H / 2)) < 512 || (x - W / 2) * (x - W / 2) + (H - (y - H / 2)) * (H - (y - H / 2)) < 512 || (W - (x - W / 2)) *(W - (x - W / 2)) + (y - H / 2) * (y - H / 2) < 512) {fRe2[y][x][c] = 255;} else{fRe2[y][x][c] = 0;}} changed = 1;} //circle
    if(keyPressed(SDLK_v)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x - W / 2) * (x - W / 2) + (y - H / 2) * (y - H / 2) < 64 || (W - (x - W / 2)) * (W - (x - W / 2)) + (H - (y - H / 2)) *(H - (y - H / 2)) < 64 || (x - W / 2) * (x - W / 2) + (H - (y - H / 2)) * (H - (y - H / 2)) < 64 || (W - (x - W / 2)) *(W - (x - W / 2)) + (y - H / 2) * (y - H / 2) < 64) {fRe2[y][x][c] = fRe[y][x][c];} else{fRe2[y][x][c] = 0;}} changed = 1;} //circle of image
    if(keyPressed(SDLK_w)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x - W / 2) * (x - W / 2) + (y - H / 2) * (y - H / 2) < 512 || (W - (x - W / 2)) * (W - (x - W / 2)) + (H - (y - H / 2)) *(H - (y - H / 2)) < 512 || (x - W / 2) * (x - W / 2) + (H - (y - H / 2)) * (H - (y - H / 2)) < 512 || (W - (x - W / 2)) *(W - (x - W / 2)) + (y - H / 2) * (y - H / 2) < 512) {fRe2[y][x][c] = fRe[y][x][c];} else{fRe2[y][x][c] = 0;}} changed = 1;} //circle of image
    if(keyPressed(SDLK_UP)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fIm2[y][x][c] = fRe2[y][x][c];} changed = 1;} //imaginary part = real part
    if(keyPressed(SDLK_DOWN)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {fIm2[y][x][c] = 0;} changed = 1;} //imaginary part=0
    if(keyPressed(SDLK_SPACE)) endloop= 1;
    if(changed)
    {
      //Draw the image and its FT
      calculateAmp(W, H, fAmp2[0][0], fRe2[0][0], fIm2[0][0]);
      draw(0, ytrans, W, H, fRe2[0][0], 0, 0);  draw(W, 0+ytrans, W, H, fIm2[0][0], 0, 0);  draw(2 * W, 0+ytrans, W, H, fAmp2[0][0], 0, 0); //draw real, imag and amplitude
      FFT2D(W, H, 0, fRe2[0][0], fIm2[0][0], FRe[0][0], FIm[0][0]);
      calculateAmp(W, H, FAmp[0][0], FRe[0][0], FIm[0][0]);
      draw(0,H + ytrans, W, H, FRe[0][0], 1, 1);  draw(W, H + ytrans, W, H, FIm[0][0], 1, 1);  draw(2 * W, H + ytrans, W, H, FAmp[0][0], 1, 0); //draw real, imag and amplitude
      print("Press a-z for effects and space to accept", 0, 0, RGB_White, 1, ColorRGB(128, 0, 0));
      redraw();
    }
    changed=0;
  }
  changed = 1;
  while(!done())
  {
    readKeys();
    if(keyPressed(SDLK_z) || changed) { for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} changed = 1;} //no filter
    if(keyPressed(SDLK_a)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = 0;} changed = 1;} //imaginary part 0
    if(keyPressed(SDLK_b)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = 0; FIm2[y][x][c] = FIm[y][x][c];} changed = 1;} //real part 0
    if(keyPressed(SDLK_c)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FIm[y][x][c]; FIm2[y][x][c] = FRe[y][x][c];} changed = 1;} //swap real and imag part
    if(keyPressed(SDLK_d)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y < 16 || (W - x) * (W - x) + (H - y) * (H - y) < 16 || x * x + (H - y) * (H - y) < 16 || (W - x) * (W - x) + y * y < 16) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //LP filter
    if(keyPressed(SDLK_e)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y <64 || (W - x) * (W - x) + (H - y) * (H - y) < 64 || x * x + (H - y) * (H - y) < 64 || (W - x) * (W - x) + y * y <64) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //LP filter
    if(keyPressed(SDLK_f)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y < 256 || (W - x) * (W - x) + (H - y) * (H - y) < 256 || x * x + (H - y) * (H - y) < 256 || (W - x) * (W - x) + y * y < 256) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //LP filter
    if(keyPressed(SDLK_g)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y < 1024 || (W - x) * (W - x) + (H - y) * (H - y) < 1024 || x * x + (H - y) * (H - y) < 1024 || (W - x) * (W - x) + y * y < 1024) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //LP filter
    if(keyPressed(SDLK_h)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y > 16 && (W - x) * (W - x) + (H - y) * (H - y) > 16 && x * x + (H - y) * (H - y) > 16 && (W - x) * (W - x) + y * y > 16) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //HP filter
    if(keyPressed(SDLK_i)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c=0;c<3;c++ ) {if(x * x + y * y > 64 && (W - x) * (W - x) + (H - y) * (H - y) > 64&& x * x + (H - y) * (H - y) > 64&& (W - x) * (W - x) + y * y > 64) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //HP filter
    if(keyPressed(SDLK_j)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y > 256 && (W - x) * (W - x) + (H - y) * (H - y) > 256 && x * x + (H - y) * (H - y) > 256 && (W - x) * (W - x) + y * y > 256) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //HP filter
    if(keyPressed(SDLK_k)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x * x + y * y >512 && (W - x) * (W - x) + (H - y) * (H - y) > 512 && x * x + (H - y) * (H - y) > 512 && (W - x) * (W - x) + y * y >512) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //HP filter
    if(keyPressed(SDLK_l)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;} changed = 1;} //make all zero
    if(keyPressed(SDLK_m)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FRe[y][x][c]/2; FIm2[y][x][c] = FIm[y][x][c];} changed = 1;} //divide real through 2
    if(keyPressed(SDLK_n)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c]/2;} changed = 1;} //divide imag through 2
    if(keyPressed(SDLK_o)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < 4 || x > W - 4) && (y < 4 || y > W -4)) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //square LP filter
    if(keyPressed(SDLK_p)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < 8||x > W -8) && (y < 8 || y > W -8)) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //square LP filter
    if(keyPressed(SDLK_q)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x < 16 || x > W - 16) && (y < 16||y > W -16)) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //square LP filter
    if(keyPressed(SDLK_r)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x * x + y * y < 256 || (W - x) * (W - x) + (H - y) * (H - y) < 256 || x * x + (H - y) * (H - y) < 256 || (W - x) * (W - x) + y * y < 256) && (x * x + y * y > 128 && (W - x) * (W - x) + (H - y) * (H - y) > 128&& x * x + (H - y) * (H - y) > 128 && (W - x) * (W - x) + y * y > 128)) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //BP filter
    if(keyPressed(SDLK_s)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if((x * x + y * y < 512 || (W - x) * (W - x) + (H - y) * (H - y) < 512||x * x + (H - y) * (H - y) < 512 || (W - x) * (W - x) + y * y < 512) && (x * x + y * y > 256 && (W - x) * (W - x) + (H - y) * (H - y) > 256 && x * x + (H - y) * (H - y) > 256 && (W - x) * (W - x) + y * y > 256)) {FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];} else{FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;}} changed = 1;} //BP filter
    if(keyPressed(SDLK_t)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = cos(3.1415*x / 8.0) * FRe[y][x][c]; FIm2[y][x][c] = cos(3.1415*x / 8.0) * FIm[y][x][c];} changed = 1;} //some cos function
    if(keyPressed(SDLK_u)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = cos(y / 8.0) * FRe[y][x][c]; FIm2[y][x][c] = cos(y / 8.0) * FIm[y][x][c];} changed = 1;} //some cos function
    if(keyPressed(SDLK_v)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = cos(x / 8.0) * FRe[y][x][c]; FIm2[y][x][c] = cos(y / 8.0) * FIm[y][x][c];} changed = 1;} //some cos function
    if(keyPressed(SDLK_w)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = cos(x/4.0) * FRe[y][x][c]; FIm2[y][x][c] = cos(y/4.0) * FIm[y][x][c];} changed = 1;} //some cos function
    if(keyPressed(SDLK_x)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {if(x == 0||y == 0) {FRe2[y][x][c] = 0; FIm2[y][x][c] = 0;} else{FRe2[y][x][c] = FRe[y][x][c]; FIm2[y][x][c] = FIm[y][x][c];}} changed = 1;} //take out horizontal and vertical line through the center
    if(keyPressed(SDLK_y)) {for(int y = 0; y < H; y++) for(int x = 0; x < W; x++) for(int c = 0; c < 3; c++) {FRe2[y][x][c] = FRe[y][x][c]/2; FIm2[y][x][c] = FIm[y][x][c]/2;} changed = 1;} //divide all through 2
    if(keyPressed(SDLK_UP)) {FRe2[0][0][0] = FRe[0][0][0]; FRe2[0][0][1] = FRe[0][0][1]; FRe2[0][0][2] = FRe[0][0][2]; FIm2[0][0][0] = FIm[0][0][0]; FIm2[0][0][1] = FIm[0][0][1]; FIm2[0][0][2] = FIm[0][0][2]; changed = 1;} //Bring DC back
    if(keyPressed(SDLK_DOWN)) {FRe2[0][0][0] = 0; FRe2[0][0][1] = 0; FRe2[0][0][2] = 0; FIm2[0][0][0] = 0; FIm2[0][0][1] = 0; FIm2[0][0][2] = 0; changed = 1;} //remove DC
    if(keyPressed(SDLK_LEFT)) {FRe2[0][0][0] = FIm[0][0][0]; FRe2[0][0][1] = FIm[0][0][1]; FRe2[0][0][2] = FIm[0][0][2]; FIm2[0][0][0] = FRe[0][0][0]; FIm2[0][0][1] = FRe[0][0][1]; FIm2[0][0][2] = FRe[0][0][2]; changed = 1;} //Bring DC back
    if(keyPressed(SDLK_RIGHT)) {FRe2[0][0][0] = W * H; FRe2[0][0][1] = W * H; FRe2[0][0][2] = W * H; FIm2[0][0][0] = W * H; FIm2[0][0][1] = W * H; FIm2[0][0][2] = W * H; changed = 1;} //remove DC
    if(changed)
    {
      //after pressing a key: calculate the inverse!
      FFT2D(W, H, 1, FRe2[0][0], FIm2[0][0], fRe[0][0], fIm[0][0]);
      calculateAmp(W, H, fAmp[0][0], fRe[0][0], fIm[0][0]);
      draw(0, 3 * H + ytrans, W, H, fRe[0][0], 0, 0);  draw(W, 3 * H + ytrans, W, H, fIm[0][0], 0, 0);  draw(2 * W, 3 * H + ytrans, W, H, fAmp[0][0], 0, 0);
      calculateAmp(W, H, FAmp2[0][0], FRe2[0][0], FIm2[0][0]);
      draw(0, 2 * H + ytrans, W, H, FRe2[0][0], 1, 1);  draw(W, 2 * H + ytrans, W, H, FIm2[0][0], 1, 1);  draw(2 * W, 2 * H + ytrans, W, H, FAmp2[0][0], 1, 0);
      print("Press a-z for filters and arrows to change DC", 0, 0, RGB_White, 1, ColorRGB(128, 0, 0));
      redraw();
    }
    changed=0;
  }
  return 0;
}


void DFT(int n, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm, int stride, double factor)
{
  for(int n = 0; n < n; n++)
  {
    GRe[n * stride] = GIm[n * stride] = 0;
    for(int x = 0; x < n; x++)
    {
      double a = -2 * pi * n * x / float(n);
      if(inverse) a = -a;
      double ca = cos(a);
      double sa = sin(a);
      GRe[n * stride] += gRe[x * stride] * ca - gIm[x * stride] * sa;
      GIm[n * stride] += gRe[x * stride] * sa + gIm[x * stride] * ca;
    }
    //Divide through the factor, e.g. n
    GRe[n * stride] /= factor;
    GIm[n * stride] /= factor;
  }
}

void DFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm)
{
   //temporary buffers
  std::vector<double> Gr2(h * w * 3);
  std::vector<double> Gi2(h * w * 3);

  for(int y = 0; y < h; y++) // for each row
  for(int c = 0; c < 3; c++) // for each color channel
  {
    DFT(w, inverse, &gRe[y * w * 3 + c], &gIm[y * w * 3 + c], &Gr2[y * w * 3 + c], &Gi2[y * w * 3 + c], 3, 1);
  }
  for(int x = 0; x < w; x++) // for each column
  for(int c = 0; c < 3; c++) // for each color channel
  {
    DFT(h, inverse, &Gr2[x * 3 + c], &Gi2[x * 3 + c], &GRe[x * 3 + c], &GIm[x * 3 + c], w * 3, inverse ? w : h);
  }
}

void FFT(int n, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm, int stride, double factor)
{
  //Calculate h=log_2(n)
  int h = 0;
  int p = 1;
  while(p < n)
  {
    p *= 2;
    h++;
  }
  //Bit reversal
  GRe[(n - 1) * stride] = gRe[(n - 1) * stride];
  GIm[(n - 1) * stride] = gIm[(n - 1) * stride];
  int j = 0;
  for(int i = 0; i < n - 1; i++)
  {
    GRe[i * stride] = gRe[j * stride];
    GIm[i * stride] = gIm[j * stride];
    int k = n / 2;
    while(k <= j)
    {
      j -= k;
      k /= 2;
    }
    j += k;
  }
  //Calculate the FFT
  double ca = -1.0;
  double sa = 0.0;
  int l1 = 1, l2 = 1;
  for(int l = 0; l < h; l++)
  {
    l1 = l2;
    l2 *= 2;
    double u1 = 1.0;
    double u2 = 0.0;
    for(int j = 0; j < l1; j++)
    {
      for(int i = j; i < n; i += l2)
      {
        int i1 = i + l1;
        double t1 = u1 * GRe[i1 * stride] - u2 * GIm[i1 * stride];
        double t2 = u1 * GIm[i1 * stride] + u2 * GRe[i1 * stride];
        GRe[i1 * stride] = GRe[i * stride] - t1;
        GIm[i1 * stride] = GIm[i * stride] - t2;
        GRe[i * stride] += t1;
        GIm[i * stride] += t2;
      }
      double z =  u1 * ca - u2 * sa;
      u2 = u1 * sa + u2 * ca;
      u1 = z;
    }
    sa = sqrt((1.0 - ca) / 2.0);
    if(!inverse) sa =- sa;
    ca = sqrt((1.0 + ca) / 2.0);
  }
  //Divide through the factor, e.g. n
  for(int i = 0; i < n; i++)
  {
    GRe[i * stride] /= factor;
    GIm[i * stride] /= factor;
  }
}

void FFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm)
{
   //temporary buffers
  std::vector<double> Gr2(h * w * 3);
  std::vector<double> Gi2(h * w * 3);

  for(int y = 0; y < h; y++) // for each row
  for(int c = 0; c < 3; c++) // for each color channel
  {
    FFT(w, inverse, &gRe[y * w * 3 + c], &gIm[y * w * 3 + c], &Gr2[y * w * 3 + c], &Gi2[y * w * 3 + c], 3, 1);
  }
  for(int x = 0; x < w; x++) // for each column
  for(int c = 0; c < 3; c++) // for each color channel
  {
    FFT(h, inverse, &Gr2[x * 3 + c], &Gi2[x * 3 + c], &GRe[x * 3 + c], &GIm[x * 3 + c], w * 3, inverse ? w : h);
  }
}

//Draws an image
void draw(int xPos, int yPos, int w, int h, const double *g, bool shift, bool neg128) //g is the image to be drawn
{
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  {
    int x2 = x, y2 = y;
    if(shift) {x2 = (x + w / 2) % w; y2 = (y + h / 2) % h;} //Shift corners to center
    ColorRGB color;
    //calculate color values out of the floating point buffer
    color.r = int(g[3 * w * y2 + 3 * x2 + 0]);
    color.g = int(g[3 * w * y2 + 3 * x2 + 1]);
    color.b = int(g[3 * w * y2 + 3 * x2 + 2]);

    if(neg128) color = color + RGB_Gray;
    //negative colors give confusing effects so set them to 0
    if(color.r < 0) color.r = 0;
    if(color.g < 0) color.g = 0;
    if(color.b < 0) color.b = 0;
    //set color components higher than 255 to 255
    if(color.r > 255) color.r = 255;
    if(color.g > 255) color.g = 255;
    if(color.b > 255) color.b = 255;
    //plot the pixel
    pset(x + xPos, y + yPos, color);
  }
}

//Calculates the amplitude of *gRe and *gIm and puts the result in *gAmp
void calculateAmp(int w, int h, double *gAmp, const double *gRe, const double *gIm)
{
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  for(int c = 0; c < 3; c++)
  {
    gAmp[w * 3 * y + 3 * x + c] = sqrt(gRe[w * 3 * y + 3 * x + c] * gRe[w * 3 * y + 3 * x + c] + gIm[w * 3 * y + 3 * x + c] * gIm[w * 3 * y + 3 * x + c]);
  }
}
