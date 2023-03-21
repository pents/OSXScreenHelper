//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "ScreenHelper.h"

ScreenWidthHeight* CurrentScreenResolution = nullptr;

inline Screenshot* GetScreenshotInner(CGImageRef image_ref)
{
    if (image_ref != nullptr){
        auto width = CGImageGetWidth(image_ref);
        auto height = CGImageGetHeight(image_ref);
        auto* result = new Screenshot(width, height, image_ref);
        return result;
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

bool SaveToFile(CGImageRef image, const std::string& filePath) {
    if (image == nullptr) {

        return false;
    }

    CFURLRef url = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault,
                                                           (const UInt8*)filePath.c_str(),
                                                           filePath.length(),
                                                           false);

    if (url == nullptr) {
        //std::cerr << "Failed to create CFURLRef from file path" << std::endl;
        return false;
    }

    CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, nullptr);

    if (destination == nullptr) {
        //std::cerr << "Failed to create CGImageDestinationRef" << std::endl;
        CFRelease(url);
        return false;
    }

    CGImageDestinationAddImage(destination, image, nullptr);

    bool result = CGImageDestinationFinalize(destination);

    if (!result) {
        //std::cerr << "Failed to save the image" << std::endl;
    }

    CFRelease(destination);
    CFRelease(url);

    return result;
}


string* GetCurrentActiveWindowName()
{
    // Get a list of all open windows
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID);
    string* result = nullptr;
    // Loop through the windows to find the currently active one
    for (CFIndex i = 0; i < CFArrayGetCount(windowList); i++) {
        auto windowInfo = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, i);

        // Check if the window is the currently active one
        auto isTransparent = (CFBooleanRef)CFDictionaryGetValue(windowInfo, kCGWindowAlpha);
        if (CFBooleanGetValue(isTransparent))
            continue;

        auto isMain = (CFBooleanRef)CFDictionaryGetValue(windowInfo, kCGWindowLayer);
        if (!CFBooleanGetValue(isMain))
            continue;

        // Get the title of the active window
        auto title = (CFStringRef)CFDictionaryGetValue(windowInfo, kCGWindowName);
        auto owner = (CFStringRef)CFDictionaryGetValue(windowInfo, kCGWindowOwnerName);

        if (title != nullptr){
            string delimiter = " - ";
            result = ConcatenateStrings(owner, title, delimiter.c_str());
            //CFRelease(title);
        }else{
            result = CFStringToStdString(owner);
        }

        //CFRelease(owner);
        break;
    }

    // Release the window list
    CFRelease(windowList);
    return result;
}