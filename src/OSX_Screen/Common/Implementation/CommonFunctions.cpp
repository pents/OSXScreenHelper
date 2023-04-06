//
// Created by Dmitry on 10.03.2023.
//
#include "CommonFunctions.h"

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

const char* CFStringToStdString(CFStringRef cfString){
    if (cfString == nullptr){
        return nullptr;
    }

    CFIndex bufferSize = CFStringGetLength(cfString) + 1; // The +1 is for having space for the string to be NUL terminated
    char* buffer;

    // CFStringGetCString is documented to return a false if the buffer is too small
    // (which shouldn't happen in this example) or if the conversion generally fails
    if (CFStringGetCString(cfString, buffer, bufferSize, kCFStringEncodingUTF8))
    {
        return buffer;
    }
    return nullptr;
}

CFStringRef ConcatenateInner(CFStringRef string1, CFStringRef string2, const char* delimiter = nullptr){
    if (string1 == nullptr && string2 == nullptr) {
        return nullptr;
    }
    if (string1 == nullptr || CFStringGetLength(string1) == 0) {
        return string2;
    }
    if (string2 == nullptr || CFStringGetLength(string2) == 0) {
        return string1;
    }
    CFStringRef delimiterString = delimiter ? CFStringCreateWithCString(nullptr, delimiter, kCFStringEncodingUTF8) : nullptr;
    CFStringRef format = delimiterString ? CFSTR("%@%s%@") : CFSTR("%@%@");
    CFStringRef result = CFStringCreateWithFormat(nullptr, nullptr, format, string1, delimiterString, string2);
    if (delimiterString) {
        CFRelease(delimiterString);
    }
    return result;
}

CFStringRef ConcatenateCFStrings(CFStringRef str1, CFStringRef str2, const char* delimiter)
{
    auto innerConcat = ConcatenateInner(str1, str2, delimiter);

    CFRelease(str1);
    CFRelease(str2);
    CFRelease(innerConcat);

    return innerConcat;
}

const char* ConcatenateStrings(CFStringRef str1, CFStringRef str2, const char* delimiter)
{
    auto innerConcat = ConcatenateInner(str1, str2, delimiter);

    const char* cString = nullptr;
    char* buffer = nullptr;
    CFIndex bufferSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(innerConcat), kCFStringEncodingUTF8) + 1;
    buffer = new char[bufferSize];
    if (CFStringGetCString(innerConcat, buffer, bufferSize, kCFStringEncodingUTF8)) {
        cString = buffer;
    } else {
        delete[] buffer;
        std::string str = CFStringGetCStringPtr(innerConcat, kCFStringEncodingUTF8);
        cString = str.c_str();
    }
    CFRelease(innerConcat);
    return cString;


}