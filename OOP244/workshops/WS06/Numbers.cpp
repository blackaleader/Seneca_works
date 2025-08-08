#include "Numbers.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

namespace seneca {

Numbers::Numbers(const Numbers& other) {
    m_isOriginal = false;
    m_numCount   = other.m_numCount;
    m_filename   = nullptr;
    if (other.m_numbers) {
        m_numbers = new double[m_numCount];
        for (int i = 0; i < m_numCount; i++)
            m_numbers[i] = other.m_numbers[i];
    }
    else {
        m_numbers = nullptr;
    }
}

Numbers& Numbers::operator=(const Numbers& other) {
    if (this != &other) {
        bool    wasOrig   = m_isOriginal;
        char*   savedName = nullptr;
        if (wasOrig && m_filename) {
            savedName = new char[strlen(m_filename) + 1];
            strcpy(savedName, m_filename);
        }
        delete[] m_numbers;
        m_numCount = other.m_numCount;
        if (other.m_numbers) {
            m_numbers = new double[m_numCount];
            for (int i = 0; i < m_numCount; i++)
                m_numbers[i] = other.m_numbers[i];
        }
        else {
            m_numbers = nullptr;
        }
        delete[] m_filename;
        if (savedName) {
            m_filename   = savedName;
            m_isOriginal = true;
        }
        else {
            m_filename   = nullptr;
            m_isOriginal = false;
        }
    }
    return *this;
}

Numbers::~Numbers() {
    save();
    delete[] m_numbers;
    delete[] m_filename;
}

int Numbers::numberCount() const {
    if (!m_filename) return 0;
    ifstream file(m_filename);
    int cnt = 0;
    char ch;
    while (file.get(ch)) {
        if (ch == '\n') cnt++;
    }
    return cnt;
}

bool Numbers::load() {
    if (m_numCount <= 0) return false;
    delete[] m_numbers;
    m_numbers = new double[m_numCount];
    ifstream file(m_filename);
    int i = 0;
    double v;
    while (i < m_numCount && file >> v) {
        m_numbers[i++] = v;
    }
    if (i != m_numCount) {
        delete[] m_numbers;
        m_numbers = nullptr;
        m_numCount = 0;
        return false;
    }
    return true;
}

bool Numbers::save() const {
    if (!m_isOriginal || isEmpty()) return false;
    ofstream file(m_filename);
    for (int i = 0; i < m_numCount; i++) {
        file << m_numbers[i] << '\n';
    }
    return true;
}

Numbers& Numbers::operator+=(double value) {
    double* tmp = new double[m_numCount + 1];
    for (int i = 0; i < m_numCount; i++) {
        tmp[i] = m_numbers[i];
    }
    tmp[m_numCount++] = value;
    delete[] m_numbers;
    m_numbers = tmp;
    sort();
    return *this;
}

ostream& Numbers::display(ostream& ostr) const {
    if (isEmpty()) {
        ostr << "Empty list";
        return ostr;
    }
    ostr << fixed << setprecision(2)
         << "=========================" << '\n'
         << (m_isOriginal ? m_filename : "*** COPY ***") << '\n';
    for (int i = 0; i < m_numCount; i++) {
        ostr << m_numbers[i]
             << (i < m_numCount - 1 ? ", " : "");
    }
    ostr << '\n'
         << "-------------------------" << '\n'
         << "Total of "     << m_numCount << " number(s)" << '\n'
         << "Largest number:  " << max()     << '\n'
         << "Smallest number: "  << min()     << '\n'
         << "Average:         "  << average() << '\n'
         << "=========================";
    return ostr;
}

ostream& operator<<(ostream& os, const Numbers& N) {
    return N.display(os);
}

istream& operator>>(istream& is, Numbers& N) {
    double v;
    if (is >> v) {
        N += v;
    }
    return is;
}

} // namespace seneca
