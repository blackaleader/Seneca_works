// Numbers.cpp
#include "Numbers.h"
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

namespace seneca {

    //── Private Helpers ─────────────────────────────────────────────────

    void Numbers::setEmpty() {
        m_numbers    = nullptr;
        m_filename   = nullptr;
        m_numCount   = 0;
        m_isOriginal = false;
    }

    bool Numbers::isEmpty() const {
        return m_numbers == nullptr;
    }

    void Numbers::setFilename(const char* filename) {
        delete[] m_filename;
        if (filename && filename[0]) {
            m_filename = new char[strlen(filename) + 1];
            strcpy(m_filename, filename);
        } else {
            m_filename = nullptr;
        }
    }

    int Numbers::numberCount() const {
        if (!m_filename) return 0;
        ifstream file(m_filename);
        int count = 0;
        char ch;
        while (file.get(ch)) {
            if (ch == '\n') count++;
        }
        return count;
    }

    bool Numbers::load() {
        if (m_numCount <= 0) return false;
        delete[] m_numbers;
        m_numbers = new double[m_numCount];
        ifstream file(m_filename);
        int i = 0;
        double val;
        while (i < m_numCount && file >> val) {
            m_numbers[i++] = val;
        }
        if (i != m_numCount) {
            setEmpty();
            return false;
        }
        return true;
    }

    void Numbers::sort() {
        if (!isEmpty() && m_numCount > 1) {
            std::sort(m_numbers, m_numbers + m_numCount);
        }
    }

    bool Numbers::save() const {
        if (!m_isOriginal || isEmpty()) return false;
        ofstream file(m_filename);
        for (int i = 0; i < m_numCount; i++) {
            file << m_numbers[i] << '\n';
        }
        return true;
    }


    //── Constructors / Destructor ───────────────────────────────────────

    Numbers::Numbers() {
        setEmpty();
    }

    Numbers::Numbers(const char* filename) {
        setEmpty();
        m_isOriginal = true;
        setFilename(filename);
        m_numCount = numberCount();
        if (m_numCount > 0 && load()) {
            sort();
        } else {
            delete[] m_numbers;
            delete[] m_filename;
            setEmpty();
        }
    }

    Numbers::~Numbers() {
        save();
        delete[] m_numbers;
        delete[] m_filename;
    }

    Numbers::Numbers(const Numbers& other) {
        setEmpty();
        m_isOriginal = false;          
        m_numCount   = other.m_numCount;
        if (!other.isEmpty()) {
            m_numbers = new double[m_numCount];
            for (int i = 0; i < m_numCount; i++)
                m_numbers[i] = other.m_numbers[i];
        }
    }

    Numbers& Numbers::operator=(const Numbers& other) {
        if (this != &other) {
            delete[] m_numbers;
            m_numbers  = nullptr;
            m_numCount = other.m_numCount;
            if (!other.isEmpty()) {
                m_numbers = new double[m_numCount];
                for (int i = 0; i < m_numCount; i++)
                    m_numbers[i] = other.m_numbers[i];
            }
        }
        return *this;
    }


    //── Queries ─────────────────────────────────────────────────────────

    double Numbers::average() const {
        if (isEmpty()) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < m_numCount; i++)
            sum += m_numbers[i];
        return sum / m_numCount;
    }

    double Numbers::max() const {
        return isEmpty() ? 0.0 : m_numbers[m_numCount - 1];
    }

    double Numbers::min() const {
        return isEmpty() ? 0.0 : m_numbers[0];
    }


    //── Modifiers ────────────────────────────────────────────────────────

    Numbers& Numbers::operator+=(double value) {
        double* temp = new double[m_numCount + 1];
        for (int i = 0; i < m_numCount; i++)
            temp[i] = m_numbers[i];
        temp[m_numCount++] = value;
        delete[] m_numbers;
        m_numbers = temp;
        sort();
        return *this;
    }


    //── Display ─────────────────────────────────────────────────────────

    std::ostream& Numbers::display(std::ostream& ostr) const {
        if (isEmpty()) {
            ostr << "Empty list";
        } else {
            ostr << "=========================" << '\n';
            if (m_isOriginal) ostr << m_filename << '\n';
            else               ostr << "*** COPY ***"   << '\n';

            ostr << fixed << setprecision(2);
            for (int i = 0; i < m_numCount; i++) {
                ostr << m_numbers[i];
                if (i < m_numCount - 1) ostr << ", ";
            }
            ostr << '\n'
                 << "-------------------------" << '\n'
                 << "Total of "     << m_numCount << " number(s)\n"
                 << "Largest number:  " << max()     << '\n'
                 << "Smallest number: "  << min()     << '\n'
                 << "Average:         "  << average() << '\n'
                 << "=========================";
        }
        return ostr;
    }


    //── Stream Operators ────────────────────────────────────────────────

    std::ostream& operator<<(std::ostream& os, const Numbers& N) {
        return N.display(os);
    }

    std::istream& operator>>(std::istream& is, Numbers& N) {
        std::string token;
        if (is >> token) {
            // only echo when reading from the console
            if (&is == &std::cin) {
                std::cout << token << std::endl;
            }
            // convert token to double
            double val = std::strtod(token.c_str(), nullptr);
            N += val;
        }
        return is;
    }

} // namespace seneca
