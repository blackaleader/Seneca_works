#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <iostream>

namespace seneca {

    char* strCpyAndAloc(const char* cstr);

    bool isCstrEmptyOrSpaces(const char* cstr);

    int getInt();

    int getInt(int min, int max);

}

#endif // SENECA_UTILS_H