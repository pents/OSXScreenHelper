//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_OPENCV_H
#define HELPERLIB_OPENCV_H

#include <ImageIO/ImageIO.h>
#include <ApplicationServices/ApplicationServices.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


struct FoundPoint{
    public:
    int X;
    int Y;
    double Confidence;
    FoundPoint(int x, int y, double confidence){
        X = x;
        Y = y;
        Confidence = confidence;
    }
};

double Similarity(CGImageRef image1, CGImageRef image2);
double Similarity(Mat image1, Mat image2);
FoundPoint* FindImageInScreen(CGImageRef pattern);
FoundPoint* FindImageInScreen(const cv::Mat &pattern);

Mat LoadImageFromByteArray(const uint8_t *data, size_t size);

#endif //HELPERLIB_OPENCV_H
