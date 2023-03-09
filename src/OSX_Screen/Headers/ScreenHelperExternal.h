//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPEREXTERNAL_H
#define HELPERLIB_SCREENHELPEREXTERNAL_H
#include "ScreenHelper.h"
#include "OpenCV.h"

extern "C" {

    struct ScreenWidthHeightExternal{
        unsigned int Width;
        unsigned int Height;
    };

    struct ScreenshotExternal{
        unsigned int Width;
        unsigned int Height;
        unsigned char* ImageData;
    };

ScreenWidthHeightExternal GetScreenResolutionExternal();
ScreenshotExternal* GetScreenshotExternal();


void ReleaseScreenShot(ScreenshotExternal* screenshotRef);

}

#endif //HELPERLIB_SCREENHELPEREXTERNAL_H
