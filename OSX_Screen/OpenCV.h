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
    FoundPoint(cv::Point* point, double confidence){
        X = point->x;
        Y = point->y;
        Confidence = confidence;
        delete point;
    }
};

double Similarity(Mat* image1, Mat* image2);
FoundPoint* FindImageOnImage(CGImageRef image, CGImageRef pattern);

#endif //HELPERLIB_SCREENHELPER_H
