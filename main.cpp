#include <cstdio>
#include "OSX_Screen/ScreenHelper.h"

int main()
{
    auto screenRes = GetScreenResolution();
    printf("Screen resolution: %dx%d\n", screenRes.Width, screenRes.Height);

    auto screenshot = GetScreenshot();

    FILE *stream = fopen("/Users/dmitdavydov/Desktop/screencap.png", "w+");
    fwrite(screenshot.ImageData, screenshot.BitsPerPixel, screenshot.Width * screenshot.Height, stream);
    fclose(stream);

    return 0;
}
