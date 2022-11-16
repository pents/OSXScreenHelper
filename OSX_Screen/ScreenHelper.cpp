//
// Created by Davydov Dmitriy on 15.11.2022.
//

#include "ScreenHelper.h"
#include <CoreGraphics/CGDisplayConfiguration.h>

ScreenWidthHeight GetScreenResolution()
{
    auto displayId = CGMainDisplayID();
    auto width  = CGDisplayPixelsWide(displayId);
    auto height = CGDisplayPixelsHigh(displayId);

    ScreenWidthHeight result = ScreenWidthHeight((int)width, (int)height);

    return result;
}
