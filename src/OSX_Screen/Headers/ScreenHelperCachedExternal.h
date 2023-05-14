//
// Created by Dmitry on 25.04.2023.
//

#ifndef SCREENHELPER_SCREENHELPERCACHEDEXTERNAL_H
#define SCREENHELPER_SCREENHELPERCACHEDEXTERNAL_H

#include "OpenCV.h"
#include "ScreenHelperExternal.h"

extern "C" {

    Mat* InstantiateOpenCVImage(unsigned char* data, int rows, int cols);

    FoundPointExternal* FindImageInScreenCachedExternal(Mat* pattern);
}


#endif //SCREENHELPER_SCREENHELPERCACHEDEXTERNAL_H
