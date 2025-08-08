#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
namespace {
    std::string trim(const std::string& s) {
        size_t b = s.find_first_not_of(" \t\r\n");
        if (b == std::string::npos) return "";
        size_t e = s.find_last_not_of(" \t\r\n");
        return s.substr(b, e - b + 1);
    }
}
namespace seneca {
char* strCpyAndAloc(const char* str) {
    if (!str) return nullptr;
    size_t len = std::strlen(str);
    char* p = new char[len + 1];
    std::memcpy(p, str, len + 1);
    return p;
}
bool isCstrEmptyOrSpaces(const char* str) {
    if (!str || !*str) return true;
    for (const char* p = str; *p; ++p) {
        if (!std::isspace(static_cast<unsigned char>(*p))) return false;
    }
    return true;
}
bool readFnamePrice(std::ifstream& fin, char*& name, double& price) {
    name = nullptr;
    price = 0.0;
    std::string line;
    if (!std::getline(fin, line)) return false;
    std::string t = trim(line);
    if (t.empty()) return false;
    size_t comma = t.find(',');
    if (comma == std::string::npos) return false;
    std::string n = trim(t.substr(0, comma));
    std::string p = trim(t.substr(comma + 1));
    if (n.empty() || p.empty()) return false;
    name = strCpyAndAloc(n.c_str());
    try {
        price = std::stod(p);
    } catch (...) {
        delete[] name;
        name = nullptr;
        return false;
    }
    return true;
}
char* getDynCstrInput() {
    std::string line;
    std::getline(std::cin, line);
    return strCpyAndAloc(line.c_str());
}
int getInt() {
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        std::string t = trim(line);
        if (t.empty()) {
            std::cout << "You must enter a value: ";
            continue;
        }
        try {
            size_t idx = 0;
            long v = std::stol(t, &idx, 10);
            if (idx < t.length()) {
                std::cout << "Invalid integer: " << t << "\n";
                std::cout << "Only an integer please: ";
                continue;
            }
            return static_cast<int>(v);
        } catch (...) {
            std::cout << "Invalid integer: " << t << "\n";
            std::cout << "Only an integer please: ";
        }
    }
}
int getInt(int min, int max) {
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        std::string t = trim(line);
        if (t.empty()) {
            std::cout << "You must enter a value: ";
            continue;
        }
        try {
            size_t idx = 0;
            long v = std::stol(t, &idx, 10);
            if (idx < t.length()) {
                std::cout << "Only an integer please: ";
                continue;
            }
            if (v < min || v > max) {
                std::cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
                continue;
            }
            return static_cast<int>(v);
        } catch (...) {
            std::cout << "Invalid integer: ";
            continue;
        }
    }
}
}