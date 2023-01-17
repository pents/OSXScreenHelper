//
//  ScreenHelperExternal.c
//  OSX_Screen
//
//  Created by Davydov Dmitriy on 13.01.2023.
//

#include <stdio.h>
#include "ScreenHelper.h"
#include "OpenCV.h"
#include "ScreenHelperExternal.h"


ScreenWidthHeightExternal GetScreenResolutionExternal()
{
    auto data = GetScreenResolution();
    auto result = ScreenWidthHeightExternal(data->Width, data->Height);
    delete data;
    return result;
}
