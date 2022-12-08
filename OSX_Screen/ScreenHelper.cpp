//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "ScreenHelper.h"
#include <UniformTypeIdentifiers/UniformTypeIdentifiers.h>
#include <string>
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

bool SaveToFile(int8_t* buffer, uint16_t width, uint16_t height, std::string filename)
{
    bool status = false;

    CGDataProviderRef provider_ref = CGDataProviderCreateWithData(NULL, buffer, width * height * 4, NULL);
    if (provider_ref != NULL) {
        CGColorSpaceRef cs_ref = CGColorSpaceCreateDeviceRGB();
        if (cs_ref != nullptr) {
            CGImageRef img_ref = CGImageCreate(
                width,
                height,
                8,          // bitsPerComponent
                32,         // bitsPerPixel
                width * 4,  // bytesPerRow
                cs_ref,
                kCGBitmapByteOrderDefault,
                provider_ref,
                NULL,       // decode array
                false,      // shouldInterpolate
                kCGRenderingIntentDefault
            );

            if (img_ref != NULL) {
                CFStringRef folderCFStr = CFStringCreateWithCString(0, filename.data(), kCFStringEncodingUTF8);
                CFURLRef url_ref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, folderCFStr, kCFURLPOSIXPathStyle, false);
                if (url_ref != NULL) {
                    CGImageDestinationRef destination_ref = CGImageDestinationCreateWithURL(url_ref, UTTypePNG, 1, NULL);
                    if (destination_ref != NULL) {
                        CGImageDestinationAddImage(destination_ref, img_ref, NULL);
                        if (CGImageDestinationFinalize(destination_ref)) {
                            status = true;
                        }

                        CFRelease(destination_ref);
                    }

                    CFRelease(url_ref);
                }

                CGImageRelease(img_ref);
            }

            CGColorSpaceRelease(cs_ref);
        }

        CGDataProviderRelease(provider_ref);
    }

    return status;
}
