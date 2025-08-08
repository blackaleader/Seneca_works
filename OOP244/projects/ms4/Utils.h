#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <iostream>
#include <fstream>

namespace seneca {

    char* strCpyAndAloc(const char* c_sTr);
    bool isCstrEmptyOrSpaces(const char* c_st_r);
    int getInt();
    int getInt(int miN, int mx);
    char* getDynCstrInput();
    bool readFnamePrice(std::ifstream& fIle, char*& nAMe, double& pRICE);
    char* makeBillFileName(char* filename, size_t billNo);

}

#endif // SENECA_UTILS_H