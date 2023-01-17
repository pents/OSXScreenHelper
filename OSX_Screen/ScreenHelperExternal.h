//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPEREXTERNAL_H
#define HELPERLIB_SCREENHELPEREXTERNAL_H
#define DLL_API __declspec(dllexport)

extern "C" {
    struct ScreenWidthHeightExternal{
    public:
        int Width;
        int Height;
        ScreenWidthHeightExternal(int W, int H){
            Width = W;
            Height = H;
        }
    };

DLL_API ScreenWidthHeightExternal GetScreenResolutionExternal();
}

#endif //HELPERLIB_SCREENHELPER_H
