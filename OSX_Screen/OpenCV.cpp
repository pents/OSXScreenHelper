//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "OpenCV.h"


Mat* CGImageRefToMat(CGImageRef cgImage) {
  // Get the width and height of the CGImageRef
  size_t width = CGImageGetWidth(cgImage);
  size_t height = CGImageGetHeight(cgImage);

  // Create a color space
  CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

  // Create a bitmap context
  CGContextRef bitmapContext = CGBitmapContextCreate(NULL, width, height, 8, width * 4, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);

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

cv::Point* Confidence(Mat* image, Mat* pattern, double sensetivity)
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
    cv::Point* minLoc = new cv::Point();
    cv::Point* maxLoc = new cv::Point();

    minMaxLoc(result, &minVal, &maxVal, minLoc, maxLoc, Mat());
    
    if (maxVal >= sensetivity){
        return maxLoc;
    }
    
    return nullptr;
}


FoundPoint* FindImageOnImage(CGImageRef image, CGImageRef pattern, double sensetivity)
{
    Mat* matImage = CGImageRefToMat(image);
    Mat* matPattern = CGImageRefToMat(pattern);
    
    cv::Point* foundObject = Confidence(matImage, matPattern, sensetivity);
    
    delete matImage;
    delete matPattern;
    
    if (foundObject == nullptr){
        return new FoundPoint(foundObject);
    }
    return nullptr;
}

