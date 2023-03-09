#include <cstdio>
#include <string>
#include "OSX_Screen/Headers/ScreenHelper.h"


int main()
{
    std::string testFileName ="/Users/dmitdavydov/Desktop/screencap.png";
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
    }

    return 0;
}
