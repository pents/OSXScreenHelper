//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "OpenCV.h"
#include "ScreenHelper.h"


Mat* CGImageRefToMat(CGImageRef cgImage) {
  // Get the width and height of the CGImageRef
  size_t width = CGImageGetWidth(cgImage);
  size_t height = CGImageGetHeight(cgImage);

  // Create a color space
  CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

  // Create a bitmap context
  CGContextRef bitmapContext = CGBitmapContextCreate(nullptr, width, height, 8, width * 4, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);

  // Draw the CGImageRef onto the bitmap context
  CGRect rect = CGRectMake(0, 0, width, height);
  CGContextDrawImage(bitmapContext, rect, cgImage);

  // Create an OpenCV image from the bitmap context
  Mat* image = new Mat(height, width, CV_8UC4, (unsigned char*)CGBitmapContextGetData(bitmapContext), width * 4);

  // Clean up
  CGContextRelease(bitmapContext);
  CGColorSpaceRelease(colorSpace);

  return image;
}

FoundPoint* Confidence(Mat* image, Mat* pattern)
{
    // Create a result matrix
    int result_cols =  image->cols - pattern->cols + 1;
    int result_rows = image->rows - pattern->rows + 1;
    Mat result;
    result.create(result_rows, result_cols, CV_32FC1);

    // Perform the matching
    matchTemplate(*image, *pattern, result, TM_CCOEFF_NORMED);

    // Normalize the result matrix
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    // Localize the highest value
    double minVal;
    double maxVal;
    auto* minLoc = new cv::Point();
    auto* maxLoc = new cv::Point();

    minMaxLoc(result, &minVal, &maxVal, minLoc, maxLoc, Mat());

    return new FoundPoint(maxLoc, maxVal);
}

void NormalizeToScreenResolution(int cols, int rows, FoundPoint* point)
{
    ScreenWidthHeight* currentScreenRes = GetScreenResolution();
    
    point->X = point->X / (cols / currentScreenRes->Width);
    point->Y = point->Y / (rows / currentScreenRes->Height);
}

FoundPoint* FindImageOnImage(CGImageRef image, CGImageRef pattern)
{
    Mat* matImage = CGImageRefToMat(image);
    Mat* matPattern = CGImageRefToMat(pattern);
    
    FoundPoint* foundObject = Confidence(matImage, matPattern);
    
    NormalizeToScreenResolution(matImage->cols, matImage->rows, foundObject);

    delete matImage;
    delete matPattern;
    
    return foundObject;
}

double Similarity(CGImageRef image1, CGImageRef image2)
{
    Mat* image1_mat = CGImageRefToMat(image1);
    Mat* image2_mat = CGImageRefToMat(image2);
    // Calculate the difference image
    Mat diff;
    absdiff(*image1_mat, *image2_mat, diff);

    // Calculate the number of pixels with a non-zero difference
    int count = countNonZero(diff);

    // Calculate the percentage of pixels with a non-zero difference
    double percentage = (double)count / (double)(diff.total());
    
    diff.release();
    
    image1_mat->release();
    image2_mat->release();
    
    CGImageRelease(image1);
    CGImageRelease(image2);
    
    return percentage;
}
