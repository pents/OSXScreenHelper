#include <cstdio>
#include <string>
#include "OSX_Screen/Headers/ScreenHelper.h"


int main()
{
    /*std::string testFileName ="/Users/dmitdavydov/Desktop/screencap.png";
    std::string* testFileNamePtr = &testFileName;
    auto screenRes = GetScreenResolution();
    printf("Screen resolution: %dx%d\n", screenRes->Width, screenRes->Height);

    auto screenshot = GetScreenshot();

    auto success = SaveToFile(testFileNamePtr, screenshot);

    if (success){
        printf("Image Saved in %s", testFileName.data());
    }
    else{
        printf("Error while saving image");
    }*/

 //   auto windowName = GetCurrentActiveWindowName();

 //   auto test = windowName->c_str();

    auto params = new PartScreenshotParams(200, 400, 600, 500);
    auto scr = GetPartScreenshot(params);

    SaveToFile(scr->ImageData, "/Users/pent/Desktop/testScreenshot.png");

    CGImageRelease(scr->ImageData);
    delete scr;

    return 0;
}
