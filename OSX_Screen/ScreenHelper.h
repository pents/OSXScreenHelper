//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPER_H
#define HELPERLIB_SCREENHELPER_H

#include "inttypes.h"

struct ScreenWidthHeight{
public:
    int Width;
    int Height;
    ScreenWidthHeight(int W, int H){
        Width = W;
        Height = H;
    }
};

struct Screenshot{
public:
    int Width;
    int Height;
    int BitsPerPixel;
    int8_t* ImageData;
    Screenshot(int W, int H, int BPP, int8_t* data){
        Width = W;
        Height = H;
        BitsPerPixel = BPP;
        ImageData = data;
    }
};

ScreenWidthHeight GetScreenResolution();
Screenshot GetScreenshot();


#endif //HELPERLIB_SCREENHELPER_H
