// Utils.cpp
#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include <stdexcept>
#include "Utils.h"

namespace seneca {

    char* strCpyAndAloc(const char* c_str) {
        char* newStr = nullptr;
        if (c_str) {
            newStr = new char[std::strlen(c_str) + 1];
            std::strcpy(newStr, c_str);
        }
        return newStr;
    }

    bool isCstrEmptyOrSpaces(const char* c_str) {
        if (c_str == nullptr || *c_str == '\0') {
            return true;
        }
        for (size_t i = 0; c_str[i] != '\0'; ++i) {
            if (!isspace(c_str[i])) {
                return false;
            }
        }
        return false;
    }

    int getInt(int min, int max) {
        int val = 0;
        bool valid = false;
        std::string inputStr;

        do {
            std::getline(std::cin, inputStr);

            if (inputStr.empty() || isCstrEmptyOrSpaces(inputStr.c_str())) {
                std::cout << "You must enter a value: ";
                valid = false;
            } else {
                try {
                    size_t pos;
                    val = std::stoi(inputStr, &pos);
                    if (pos != inputStr.length()) {
                        throw std::invalid_argument("Not a valid integer");
                    }

                    if (val < min || val > max) {
                        std::cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
                        valid = false;
                    } else {
                        valid = true;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cout << "Invalid Integer, retry: ";
                    valid = false;
                } catch (const std::out_of_range& e) {
                    std::cout << "Value out of range [" << min << "-" << max << "]: ";
                    valid = false;
                }
            }
        } while (!valid);
        return val;
    }

    int getInt() {
        return getInt(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

    char* getDynCstrInput() {
        std::string input;
        std::getline(std::cin, input);
        if (input.empty() || isCstrEmptyOrSpaces(input.c_str())) {
            return nullptr;
        }
        return strCpyAndAloc(input.c_str());
    }

    bool readFnamePrice(std::ifstream& file, char*& name, double& price) {
        std::string tempName;
        double tempPrice;

        if (!std::getline(file, tempName, ',')) {
            return false;
        }

        if (!(file >> tempPrice)) {
            return false;
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        delete[] name;
        name = strCpyAndAloc(tempName.c_str());
        price = tempPrice;
        return true;
    }

    char* makeBillFileName(char* filename, size_t billNo) {
        std::string billFileName = "bill_";
        billFileName += std::to_string(billNo);
        billFileName += ".txt";
        std::strcpy(filename, billFileName.c_str());
        return filename;
    }
}