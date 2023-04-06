//
//  ScreenHelperExternal.c
//  OSX_Screen
//
//  Created by Davydov Dmitriy on 13.01.2023.
//

#include "ScreenHelperExternal.h"
#include "ScreenHelperException.h"

inline void FillException(exception& ex, BaseExternal* obj){
    obj->Exception = ex.what();
    obj->ExceptionLength = strlen(obj->Exception);
}

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

    return {byteArray, byteCount};
}

inline ScreenshotExternal* GetScreenshotExternal(Screenshot* screenshot){
    auto* result = new ScreenshotExternal();
    try{


        auto imageData = byteArrayFromCGImage(
                screenshot->Width,
                screenshot->Height,
                screenshot->ImageData);

        result->Height = screenshot->Height;
        result->Width = screenshot->Width;
        result->ImageData = imageData.Data;
        result->DataLength = imageData.DataCount;

        return result;
    }
    catch(exception& ex){
        FillException(ex, result);
        return result;
    }
}

ScreenWidthHeightExternal* GetScreenResolutionExternal(){

    auto result = new ScreenWidthHeightExternal();
    try{
        auto data = GetScreenResolution();
        result->Height = data->Height;
        result->Width = data->Width;
        delete data;
        return result;
    }catch(exception& ex){
        FillException(ex, result);
    }
}

ScreenshotExternal* GetScreenshotExternal(){
    try{
        auto* screenshot = GetScreenshot();
        return GetScreenshotExternal(screenshot);
    }catch(exception& ex){
        auto* result = new ScreenshotExternal();
        FillException(ex, result);
        return result;
    }
}

ScreenshotExternal* GetPartScreenshotExternal(unsigned int top, unsigned int left, unsigned int right, unsigned int bottom){
    try{
        auto* params = new PartScreenshotParams(top, left, right, bottom);
        auto* screenshot = GetPartScreenshot(params);
        return GetScreenshotExternal(screenshot);
    }
    catch(exception& ex){
        auto result = new ScreenshotExternal();
        FillException(ex, result);
        return result;
    }
}

SimilarityResultExternal* SimilarityExternal(ImageBytes* image1, ImageBytes* image2){
    auto* result = new SimilarityResultExternal();
    try{
        auto mat1Image = LoadImageFromByteArray(image1->Data, image1->DataCount);
        auto mat2Image = LoadImageFromByteArray(image2->Data, image2->DataCount);

        delete[] image1->Data;
        delete[] image2->Data;
        delete image1;
        delete image2;

        auto sim = Similarity(mat1Image, mat2Image);
        result->Value = sim;
        return result;
    }
    catch(exception& ex){
        FillException(ex, result);
        return result;
    }
}

FoundPointExternal* FindImageInScreenExternal(ImageBytes* pattern){
    auto* result = new FoundPointExternal();
    try{
        auto patternImage = LoadImageFromByteArray(pattern->Data, pattern->DataCount);
        auto* point = FindImageInScreen(patternImage);
        delete[] pattern->Data;
        delete pattern;


        result->Confidence = point->Confidence;
        result->X = point->X;
        result->Y = point->Y;

        delete point;

        return result;
    }
    catch(exception& ex){
        FillException(ex, result);
        return result;
    }
}

ActiveWindowName* GetCurrentActiveWindowNameExternal(){
    auto* result = new ActiveWindowName();
    try{
        result->Name = GetCurrentActiveWindowName()->c_str();
        return result;
    }
    catch(exception& ex){
        FillException(ex, result);
        return result;
    }
}
void ReleaseException(BaseExternal* ptr){
    if (ptr->ExceptionLength > 0){
        delete[] ptr->Exception;
    }
}

void ReleaseScreenWidthHeight(ScreenWidthHeightExternal* screenRef){
    ReleaseException(screenRef);
    delete screenRef;
}

void ReleaseFoundPoint(FoundPointExternal* pointRef){
    ReleaseException(pointRef);
    delete pointRef;
}

void ReleaseScreenshot(ScreenshotExternal* screenRef){
    ReleaseException(screenRef);
    delete[] screenRef->ImageData;
    delete screenRef;
}

void ReleaseActiveWindowName(ActiveWindowName* nameRef){
    ReleaseException(nameRef);
    ReleaseString(nameRef->Name);
    delete nameRef;
}

void ReleaseString(const char* strRef){
    delete[] strRef;
}

void ReleaseSimilarityResult(SimilarityResultExternal* simRef)
{
    ReleaseException(simRef);
    delete simRef;
}
