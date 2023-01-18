//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPEREXTERNAL_H
#define HELPERLIB_SCREENHELPEREXTERNAL_H
#include "ScreenHelper.h"
#include "OpenCV.h"

extern "C" {


    struct ScreenWidthHeightExternal{
        int Width;
        int Height;        
    };

ScreenWidthHeightExternal GetScreenResolutionExternal();
}

#endif //HELPERLIB_SCREENHELPER_H
