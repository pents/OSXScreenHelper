//
//  ScreenHelperExternal.c
//  OSX_Screen
//
//  Created by Davydov Dmitriy on 13.01.2023.
//

#include "Headers/ScreenHelperExternal.h"

struct ImageBytes{
    ImageBytes(unsigned char* data, int count){
        Data = data;
        DataCount = count;
    }

    unsigned char* Data;
    int DataCount;
};

inline ImageBytes byteArrayFromCGImage(unsigned long width, unsigned long height, CGImageRef image) {
    // Get the width and height of the image
//    size_t width = CGImageGetWidth(image);
//    size_t height = CGImageGetHeight(image);

    // Get a pointer to the raw image data
    CGDataProviderRef provider = CGImageGetDataProvider(image);
    CFDataRef data = CGDataProviderCopyData(provider);
    const unsigned char* bytes = CFDataGetBytePtr(data);

    size_t bitsPerPixel = CGImageGetBitsPerPixel(image);
    size_t bytesPerPixel = bitsPerPixel / 8;

    // Create a byte array and copy the image data into it
    size_t byteCount = width * height * bytesPerPixel;
    auto* byteArray = new unsigned char[byteCount]; // allocate memory for the new array

    memcpy(byteArray, bytes, byteCount);

    // Clean up
    CFRelease(data);

    return {byteArray, (int)byteCount};
}

inline ScreenshotExternal* GetScreenshotExternal(Screenshot* screenshot){
    auto* result = new ScreenshotExternal();

    auto imageData = byteArrayFromCGImage(
            screenshot->Width,
            screenshot->Height,
            screenshot->ImageData);

    result->Height = screenshot->Height;
    result->Width = screenshot->Width;
    result->ImageData = imageData.Data;
    result->DataLength = imageData.DataCount;
    CGImageRelease(screenshot->ImageData);
    delete screenshot;

    return result;
}

ScreenWidthHeightExternal* GetScreenResolutionExternal(){

    auto data = GetScreenResolution();
    auto result = new ScreenWidthHeightExternal();
    result->Height = data->Height;
    result->Width = data->Width;
    delete data;
    return result;
}

ScreenshotExternal* GetScreenshotExternal(){
    auto* screenshot = GetScreenshot();
    return GetScreenshotExternal(screenshot);
}

ScreenshotExternal* GetPartScreenshotExternal(unsigned int top, unsigned int left, unsigned int right, unsigned int bottom){
    auto* params = new PartScreenshotParams(top, left, right, bottom);
    auto* screenshot = GetPartScreenshot(params);
    return GetScreenshotExternal(screenshot);
}

const char* GetCurrentActiveWindowNameExternal(){
    return GetCurrentActiveWindowName()->c_str();
}

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef){
    delete screenRef;
}

void ReleaseScreenshot(ScreenshotExternal* screenRef){
    delete[] screenRef->ImageData;
    delete screenRef;
}

void ReleaseString(const char* strRef){
    delete[] strRef;
}
