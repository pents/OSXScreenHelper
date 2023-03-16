//
// Created by Dmitry on 10.03.2023.
//

#include "Common/Headers/CommonFunctions.h"

const char* GetInnerCStr(CFStringRef cfString){
    if (cfString == nullptr){
        return nullptr;
    }
    CFIndex bufferSize = CFStringGetLength(cfString) + 1;
    char* buffer = new char[bufferSize];

    if (CFStringGetCString(cfString, buffer, bufferSize, kCFStringEncodingUTF8))
    {
        return buffer;
    }
    return nullptr;
}

std::string* CFStringToStdString(CFStringRef cfString){
    if (cfString == nullptr){
        return nullptr;
    }

    CFIndex bufferSize = CFStringGetLength(cfString) + 1; // The +1 is for having space for the string to be NUL terminated
    char buffer[bufferSize];

    // CFStringGetCString is documented to return a false if the buffer is too small
    // (which shouldn't happen in this example) or if the conversion generally fails
    if (CFStringGetCString(cfString, buffer, bufferSize, kCFStringEncodingUTF8))
    {
        return new std::string (buffer);
    }
    return nullptr;
}

const char* ConcatenateInner(CFStringRef str1, CFStringRef str2, const char* delimiter){
    auto chArr1 = GetInnerCStr(str1);
    auto chArr2 = GetInnerCStr(str2);

    auto chArr1Size = strlen(chArr1);
    auto chArr2Size = strlen(chArr2);
    auto delimiterSize = strlen(delimiter);

    auto chResult = new char[chArr1Size+chArr2Size+delimiterSize];
    auto resultPointer = 0;

    if (chArr1 != nullptr){
        for (int i = 0; i < chArr1Size; ++i){
            chResult[resultPointer] = chArr1[i];
            resultPointer++;
        }
    }

    if (delimiter != nullptr){
        for (int i = 0; i < delimiterSize; ++i){
            chResult[resultPointer] = delimiter[i];
            resultPointer++;
        }
    }

    if (chArr2 != nullptr){
        for (int i = 0; i < chArr2Size; ++i){
            chResult[resultPointer] = chArr2[i];
            resultPointer++;
        }
    }

    return chResult;
}

CFStringRef ConcatenateCFStrings(CFStringRef str1, CFStringRef str2, const char* delimiter)
{
    auto innerConcat = ConcatenateInner(str1, str2, delimiter);
    auto concatenatedString = CFStringCreateWithCString(
            nullptr,
            innerConcat,
            kCFStringEncodingUTF8);

    CFRelease(str1);
    CFRelease(str2);
    delete[] innerConcat;

    return concatenatedString;
}

std::string* ConcatenateStrings(CFStringRef str1, CFStringRef str2, const char* delimiter)
{
    auto innerConcat = ConcatenateInner(str1, str2, delimiter);

    CFRelease(str1);
    CFRelease(str2);

    auto strResult = new std::string(innerConcat);
    delete[] innerConcat;
    return strResult;
}