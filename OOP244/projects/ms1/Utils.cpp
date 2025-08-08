#include "Utils.h"
#include <cstring>
#include <cctype>

namespace seneca {

    char* strCpyAndAloc(const char* cstr) {
        char* newCopy = nullptr;
        if (cstr != nullptr) {
            newCopy = new char[std::strlen(cstr) + 1];
            std::strcpy(newCopy, cstr);
        }
        return newCopy;
    }

    bool isCstrEmptyOrSpaces(const char* cstr) {
        if (cstr == nullptr || cstr[0] == '\0') {
            return true;
        }
        for (int i = 0; cstr[i] != '\0'; ++i) {
            if (!std::isspace(cstr[i])) {
                return false;
            }
        }
        return true;
    }

} // namespace seneca