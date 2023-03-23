//
// Created by Dmitry on 21.03.2023.
//

#include "ScreenHelperException.h"

const char* ScreenHelperException::what() const noexcept {
    std::stringstream ss;
    ss << "[" << Caller << "] " << Message << " --- " << "Internal exception: " << InnerMessage;
    auto concated = ss.str().c_str();

    char* res = new char[ss.str().length()];

    memcpy(res, concated, ss.str().length());

    return res;
}

ScreenHelperException::ScreenHelperException(const char* caller, const char* message, const exception& externalException){
    Caller = caller;
    Message = message;
    InnerMessage = externalException.what();
}

ScreenHelperException::ScreenHelperException(const char* caller, const char* message){
    Caller = caller;
    Message = message;
    InnerMessage = "";
}