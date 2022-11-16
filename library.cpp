#include <cstdio>
#include "OSX_Screen/ScreenHelper.h"

int main()
{
    auto screenRes = GetScreenResolution();
    printf("Screen resolution: %dx%d\n", screenRes.Width, screenRes.Height);

    return 0;
}
