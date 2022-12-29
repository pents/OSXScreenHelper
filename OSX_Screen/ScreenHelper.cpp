//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "ScreenHelper.h"
#include "ScreenHelperExternal.h"

inline Screenshot* GetScreenshotInner(CGImageRef image_ref)
{
    if (image_ref != nullptr){
        auto width = CGImageGetWidth(image_ref);
        auto height = CGImageGetHeight(image_ref);
        auto dataProvider = CGImageGetDataProvider(image_ref);
        if (dataProvider != nullptr){
            auto cs_ref = CGImageGetColorSpace(image_ref);
            if (cs_ref != nullptr) {
                
                Screenshot* result = (Screenshot*)malloc(sizeof(Screenshot));
                result->ImageData = image_ref;
                result->Width = width;
                result->Height = height;
                
                CGColorSpaceRelease(cs_ref);
                CGDataProviderRelease(dataProvider);
                return result;
            }
            CGDataProviderRelease(dataProvider);
        }
    }

    return nullptr;
}

ScreenWidthHeight* GetScreenResolution()
{
    auto displayId = CGMainDisplayID();
    auto width  = CGDisplayPixelsWide(displayId);
    auto height = CGDisplayPixelsHigh(displayId);
    
    auto result = ScreenWidthHeight((int)width, (int)height);
    
    ScreenWidthHeight* ptr = &result;
    
    return ptr;
}

Screenshot* GetPartScreenshot(PartScreenshotParams* params)
{
    CGRect rect = CGRectMake(params->Left,
                             params->Top,
                             params->Right-params->Left,
                             params->Bottom-params->Top);
    auto image_ref = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
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
        CFStringRef folderCFStr = CFStringCreateWithCString(0, fileName->data(), kCFStringEncodingUTF8);
        CFURLRef url_ref = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, folderCFStr, kCFURLPOSIXPathStyle, false);
        
        if (url_ref != nullptr) {
            
            CGImageDestinationRef destination_ref = CGImageDestinationCreateWithURL(url_ref, kUTTypePNG, 1, NULL);
            
            if (destination_ref != nullptr) {
                
                auto test = screenshot_ptr->ImageData;
                CGImageDestinationAddImage(destination_ref, test, NULL);
                CGImageDestinationFinalize(destination_ref);
                CFRelease(destination_ref);
            }

            CFRelease(url_ref);
            CFRelease(folderCFStr);
        }
    }
}
