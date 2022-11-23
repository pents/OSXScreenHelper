//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "ScreenHelper.h"
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <ApplicationServices/ApplicationServices.h>

ScreenWidthHeight GetScreenResolution()
{
    auto displayId = CGMainDisplayID();
    auto width  = CGDisplayPixelsWide(displayId);
    auto height = CGDisplayPixelsHigh(displayId);

    ScreenWidthHeight result = ScreenWidthHeight((int)width, (int)height);

    return result;
}

Screenshot GetScreenshot()
{
    CGImageRef image_ref = CGDisplayCreateImage(CGMainDisplayID());

    CGDataProviderRef provider_ref = CGImageGetDataProvider(image_ref);
    CFDataRef data_ref = CGDataProviderCopyData(provider_ref);

    auto width = CGImageGetWidth(image_ref);
    auto height = CGImageGetHeight(image_ref);

    size_t bpp = CGImageGetBitsPerPixel(image_ref) / 8;

    auto *buffer = (int8_t*)malloc(width * height * bpp);
    memcpy(buffer, CFDataGetBytePtr(data_ref), width * height * bpp);

    CFRelease(data_ref);
    CGImageRelease(image_ref);

    return {(int)width, (int)height, (int)bpp, buffer};
}