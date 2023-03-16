//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPER_H
#define HELPERLIB_SCREENHELPER_H

#include <cinttypes>
#include <ImageIO/ImageIO.h>
#include <string>
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>
#include "Common/Headers/CommonFunctions.h"

using namespace std;


// Resolution in pixels
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
    unsigned long Width;
    unsigned long Height;
    CGImageRef ImageData;
    Screenshot(unsigned long W, unsigned long H, CGImageRef data){
        Width = W;
        Height = H;
        ImageData = data;
    }
    
    ~Screenshot(){
        if (ImageData != nullptr){
            CGImageRelease(ImageData);
        }
    }
};

struct PartScreenshotParams{
public:
    unsigned long Top;
    unsigned long Left;
    unsigned long Right;
    unsigned long Bottom;
    
    PartScreenshotParams(unsigned long t, unsigned long l, unsigned long r, unsigned long b){
        Top = t;
        Left = l;
        Right = r;
        Bottom = b;
    }
};

// gets main display resolution in pixels - and stores it for future use in global variable
ScreenWidthHeight* GetScreenResolution();
Screenshot* GetScreenshot();
Screenshot* GetPartScreenshot(PartScreenshotParams* params);

bool SaveToFile(string* fileName, Screenshot* screenshot_ptr);
string* GetCurrentActiveWindowName();
    
#endif //HELPERLIB_SCREENHELPER_H
