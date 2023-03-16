//
//  ScreenHelperExternal.c
//  OSX_Screen
//
//  Created by Davydov Dmitriy on 13.01.2023.
//

#include "Headers/ScreenHelperExternal.h"


inline unsigned char* byteArrayFromCGImage(CGImageRef image) {
    // Get the width and height of the image
    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);

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

    return byteArray;
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

    auto* result = new ScreenshotExternal();

    result->Height = screenshot->Height;
    result->Width = screenshot->Width;
    result->ImageData = byteArrayFromCGImage(screenshot->ImageData);

    return result;
}

const char* GetCurrentActiveWindowNameExternal(){
    return GetCurrentActiveWindowName()->c_str();
}

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef){
    delete screenRef;
}

void ReleaseScreenShot(ScreenshotExternal* screenRef){
    delete[] screenRef->ImageData;
    delete screenRef;
}

void ReleaseString(const char* strRef){
    delete[] strRef;
}
