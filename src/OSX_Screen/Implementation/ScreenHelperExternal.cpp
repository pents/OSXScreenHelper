//
//  ScreenHelperExternal.c
//  OSX_Screen
//
//  Created by Davydov Dmitriy on 13.01.2023.
//

#include "Headers/ScreenHelperExternal.h"


ScreenWidthHeightExternal GetScreenResolutionExternal()
{
    auto data = GetScreenResolution();
    auto result = ScreenWidthHeightExternal();
    result.Height = data->Height;
    result.Width = data->Width;
    delete data;
    return result;
}
