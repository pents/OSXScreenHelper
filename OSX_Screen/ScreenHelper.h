//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPER_H
#define HELPERLIB_SCREENHELPER_H

#include "inttypes.h"
#include <ImageIO/ImageIO.h>
#include <string>
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>

using namespace std;


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


ScreenWidthHeight* GetScreenResolution();
Screenshot* GetScreenshot();
bool SaveToFile(string* fileName, Screenshot* screenshot_ptr);
    
    
#endif //HELPERLIB_SCREENHELPER_H
