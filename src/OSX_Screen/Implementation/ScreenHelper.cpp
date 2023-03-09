//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "Headers/ScreenHelper.h"
#include "Headers/ScreenHelperExternal.h"

ScreenWidthHeight* CurrentScreenResolution = nullptr;

inline Screenshot* GetScreenshotInner(CGImageRef image_ref)
{
    if (image_ref != nullptr){
        auto width = CGImageGetWidth(image_ref);
        auto height = CGImageGetHeight(image_ref);
        auto dataProvider = CGImageGetDataProvider(image_ref);
        if (dataProvider != nullptr){
            auto cs_ref = CGImageGetColorSpace(image_ref);
            if (cs_ref != nullptr) {
                                
                auto* result = new Screenshot(width, height, image_ref);
                
                CGColorSpaceRelease(cs_ref);
                CGDataProviderRelease(dataProvider);
                return result;
            }
            CGDataProviderRelease(dataProvider);
        }
    }

    throw new runtime_error("[GetScreenshotInner] Some error occured in taking screenshot - this may be because image_ref,dataProvider or cs_ref is null");
}

ScreenWidthHeight* GetScreenResolution()
{
    if (CurrentScreenResolution == nullptr)
    {
        auto displayId = CGMainDisplayID();
        auto width  = CGDisplayPixelsWide(displayId);
        auto height = CGDisplayPixelsHigh(displayId);
        CurrentScreenResolution = new ScreenWidthHeight((int)width, (int)height);
    }

    return CurrentScreenResolution;
}

Screenshot* GetPartScreenshot(PartScreenshotParams* params)
{
    CGRect rect = CGRectMake(params->Left,
                             params->Top,
                             params->Right-params->Left,
                             params->Bottom-params->Top);
    auto image_ref = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
    delete params;
    return GetScreenshotInner(image_ref);
}

Screenshot* GetScreenshot()
{
    auto image_ref = CGDisplayCreateImage(CGMainDisplayID());
    return GetScreenshotInner(image_ref);
}

bool SaveToFile(string* fileName, Screenshot* screenshot_ptr)
{
    
    if (screenshot_ptr != nullptr) {
        CFStringRef folderCFStr = CFStringCreateWithCString(nullptr, fileName->data(), kCFStringEncodingUTF8);
        CFURLRef url_ref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, folderCFStr, kCFURLPOSIXPathStyle, false);
        
        if (url_ref != nullptr) {
            
            CGImageDestinationRef destination_ref = CGImageDestinationCreateWithURL(url_ref, kUTTypePNG, 1, nullptr);
            
            if (destination_ref != nullptr) {
                
                auto test = screenshot_ptr->ImageData;
                CGImageDestinationAddImage(destination_ref, test, nullptr);
                CGImageDestinationFinalize(destination_ref);
                CFRelease(destination_ref);
            }

            CFRelease(url_ref);
            CFRelease(folderCFStr);
        }
    }
}
