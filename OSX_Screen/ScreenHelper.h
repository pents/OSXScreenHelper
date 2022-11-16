//
// Created by Davydov Dmitriy on 15.11.2022.
//

#ifndef HELPERLIB_SCREENHELPER_H
#define HELPERLIB_SCREENHELPER_H

struct ScreenWidthHeight{
public:
    int Width;
    int Height;
    ScreenWidthHeight(int W, int H){
        Width = W;
        Height = H;
    }
};

ScreenWidthHeight GetScreenResolution();


#endif //HELPERLIB_SCREENHELPER_H
