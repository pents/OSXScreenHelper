//
// Created by Dmitry on 10.03.2023.
//

#ifndef SCREENHELPER_COMMONFUNCTIONS_H
#define SCREENHELPER_COMMONFUNCTIONS_H

#include <CoreFoundation/CoreFoundation.h>
#include <string>

std::string* CFStringToStdString(CFStringRef cfString);
CFStringRef ConcatenateCFStrings(CFStringRef str1, CFStringRef str2, const char* delimiter);
std::string* ConcatenateStrings(CFStringRef str1, CFStringRef str2, const char* delimiter);

#endif //SCREENHELPER_COMMONFUNCTIONS_H
