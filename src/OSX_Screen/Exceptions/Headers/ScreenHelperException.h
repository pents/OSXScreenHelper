//
// Created by Dmitry on 21.03.2023.
//

#ifndef SCREENHELPER_SCREENHELPEREXCEPTION_H
#define SCREENHELPER_SCREENHELPEREXCEPTION_H

#include <exception>
#include <iostream>
#include <sstream>

using namespace std;

struct ScreenHelperException : public exception {

public:
    ScreenHelperException(const char* caller, const char* message);
    ScreenHelperException(const char* caller, const char* message, const exception& externalException);
    [[nodiscard]] const char* what () const noexcept override;

private:
    const char* Caller;
    const char* Message;
    const char* InnerMessage;
};

#endif //SCREENHELPER_SCREENHELPEREXCEPTION_H
