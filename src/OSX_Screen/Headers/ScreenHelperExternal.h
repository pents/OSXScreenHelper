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
        int DataLength;
    };

ScreenWidthHeightExternal* GetScreenResolutionExternal();
ScreenshotExternal* GetScreenshotExternal();
ScreenshotExternal* GetPartScreenshotExternal(unsigned int top, unsigned int left, unsigned int right, unsigned int bottom);
const char* GetCurrentActiveWindowNameExternal();

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef);
void ReleaseScreenshot(ScreenshotExternal* screenshotsRef);
void ReleaseString(const char* strRef);

}

#endif //HELPERLIB_SCREENHELPEREXTERNAL_H
