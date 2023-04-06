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

    struct ActiveWindowName : BaseExternal{
        const char* Name;
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
ActiveWindowName* GetCurrentActiveWindowNameExternal();

SimilarityResultExternal* SimilarityExternal(ImageBytes* image1, ImageBytes* image2);
FoundPointExternal* FindImageInScreenExternal(ImageBytes* pattern);

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef);
void ReleaseFoundPoint(FoundPointExternal* pointRef);
void ReleaseScreenshot(ScreenshotExternal* screenshotsRef);
void ReleaseActiveWindowName(ActiveWindowName* nameRef);
void ReleaseString(const char* strRef);
void ReleaseSimilarityResult(SimilarityResultExternal* simRef);

}

#endif //HELPERLIB_SCREENHELPEREXTERNAL_H
