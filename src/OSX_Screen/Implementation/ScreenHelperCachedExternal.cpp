//
// Created by Dmitry on 25.04.2023.
//

#include "ScreenHelperCachedExternal.h"
#include "ScreenHelperExternal.h"
#include "CImg.h"

CGImageRef convertCImgToCGImage(const cimg_library::CImg<unsigned char>& image) {
    CGImageRef cgImage = nullptr;
    size_t width = image.width();
    size_t height = image.height();
    size_t bytesPerRow = image.width() * image.spectrum() * sizeof(unsigned char);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault | kCGImageAlphaNoneSkipLast;
    CGDataProviderRef provider = CGDataProviderCreateWithData(nullptr, image.data(), bytesPerRow * height, nullptr);
    if (provider != nullptr) {
        cgImage = CGImageCreate(width, height, 8, 8 * image.spectrum(), bytesPerRow, colorSpace, bitmapInfo, provider, nullptr, false, kCGRenderingIntentDefault);
        CGDataProviderRelease(provider);
    }
    CGColorSpaceRelease(colorSpace);
    return cgImage;
}

Mat* InstantiateOpenCVImage(unsigned char* data, int rows, int cols){
    int channels = 4;
    auto* image = new cv::Mat(rows, cols, CV_MAKETYPE(CV_8U, channels), data);

    return image;
}

FoundPointExternal* FindImageInScreenCachedExternal(Mat* pattern){
    auto* result = new FoundPointExternal();
    try{
        auto* point = FindImageInScreen(*pattern);

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