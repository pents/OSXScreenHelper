//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPEREXTERNAL_H
#define HELPERLIB_SCREENHELPEREXTERNAL_H
#include "ScreenHelper.h"
#include "OpenCV.h"

extern "C" {
    struct BaseExternal{
        const char* Exception;
        int ExceptionLength;
    };

    struct ScreenWidthHeightExternal : BaseExternal{
        unsigned int Width;
        unsigned int Height;
    };

    struct ScreenshotExternal : BaseExternal{
        unsigned int Width;
        unsigned int Height;
        unsigned char* ImageData;
        int DataLength;
    };

    struct FoundPointExternal : BaseExternal{
        int X;
        int Y;
        double Confidence;
    };

    struct SimilarityResultExternal : BaseExternal{
        double Value;
    };

    struct ImageBytes{
        unsigned char* Data;
        unsigned long DataCount;
    };


ScreenWidthHeightExternal* GetScreenResolutionExternal();
ScreenshotExternal* GetScreenshotExternal();
ScreenshotExternal* GetPartScreenshotExternal(unsigned int top, unsigned int left, unsigned int right, unsigned int bottom);
const char* GetCurrentActiveWindowNameExternal();

SimilarityResultExternal* SimilarityExternal(ImageBytes* image1, ImageBytes* image2);
FoundPointExternal* FindImageInScreenExternal(ImageBytes* pattern);

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef);
void ReleaseFoundPoint(FoundPointExternal* pointRef);
void ReleaseScreenshot(ScreenshotExternal* screenshotsRef);
void ReleaseString(const char* strRef);

}

#endif //HELPERLIB_SCREENHELPEREXTERNAL_H
