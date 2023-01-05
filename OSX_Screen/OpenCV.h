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


void FindImageOnImage(CGImageRef image, CGImageRef pattern);


struct FoundPoint{
    public:
    int X;
    int Y;
    FoundPoint(cv::Point* point){
        X = point->x;
        Y = point->y;
        delete point;
    }
};


#endif //HELPERLIB_SCREENHELPER_H
