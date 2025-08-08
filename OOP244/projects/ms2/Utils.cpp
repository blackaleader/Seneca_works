#include "Utils.h"
#include <cstring>
#include <cctype>
#include <limits>
#include <string>
#include <sstream>

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

    int getInt() {
        int value;
        bool done = false;
        std::string line;

        while (!done) {
            std::getline(std::cin, line);

            if (line.empty()) {
                std::cout << "You must enter a value: ";
                continue;
            }

            std::stringstream ss(line);
            ss >> value;

            if (ss.fail()) {
                std::cout << "Invalid integer: ";
            } else {
                char remaining;
                if (ss >> remaining) {
                    std::cout << "Only an integer please: ";
                } else {
                    done = true;
                }
            }
        }
        return value;
    }

    int getInt(int min, int max) {
        int value;
        bool done = false;
        while (!done) {
            value = getInt();
            if (value < min || value > max) {
                std::cout << "Invalid value: [" << min << "<= value <= " << max << "], try again: ";
            } else {
                done = true;
            }
        }
        return value;
    }

}