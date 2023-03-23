//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "OpenCV.h"
#include "ScreenHelper.h"

cv::Mat convertToMat(CGImageRef image) {
    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    CGRect rect = CGRectMake(0, 0, width, height);

    cv::Mat mat(height, width, CV_8UC4);
    CGContextRef context = CGBitmapContextCreate(mat.data, width, height, 8, 4 * width, CGImageGetColorSpace(image), kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little);

    CGContextDrawImage(context, rect, image);
    CGContextRelease(context);
    CGImageRelease(image);

    return mat;
}

FoundPoint* FindImageInScreen(const cv::Mat &pattern){
    Screenshot* screenImage = GetScreenshot();
    Mat haystack = convertToMat(screenImage->ImageData);

    Mat result;
    matchTemplate(haystack, pattern, result, cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    auto* res = new FoundPoint(maxLoc.x, maxLoc.y, maxVal);

    return res;
}

FoundPoint* FindImageInScreen(CGImageRef pattern) {
    Screenshot* screenImage = GetScreenshot();
    Mat haystack = convertToMat(screenImage->ImageData);
    Mat needle = convertToMat(pattern);
    Mat result;
    matchTemplate(haystack, needle, result, cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    auto* res = new FoundPoint(maxLoc.x, maxLoc.y, maxVal);

    return res;
}

Mat LoadImageFromByteArray(const uint8_t *data, size_t size) {
    vector<uint8_t> buffer(data, data + size);
    Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    return image;
}

double Similarity(Mat image1, Mat image2){
    // Calculate the difference image
    Mat diff;
    absdiff(image1, image2, diff);

    // Calculate the number of pixels with a non-zero difference
    int count = countNonZero(diff);

    // Calculate the percentage of pixels with a non-zero difference
    double percentage = (double)count / (double)(diff.total());

    diff.release();

    image1.release();
    image2.release();

    return percentage;
}

double Similarity(CGImageRef image1, CGImageRef image2)
{
    Mat image1_mat = convertToMat(image1);
    Mat image2_mat = convertToMat(image2);

    auto result = Similarity(image1_mat, image2_mat);

    CGImageRelease(image1);
    CGImageRelease(image2);

    return result;
}
