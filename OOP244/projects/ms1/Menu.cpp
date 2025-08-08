#include "Menu.h"
#include "Utils.h"
#include <iomanip>
#include <cstring>
#include <cctype>

namespace seneca {

    MenuItem::MenuItem(const char* content, unsigned int indentNum, unsigned int indentSize, int rowNumber) {
        m_content = nullptr;
        m_indentCount = 0;
        m_indentWidth = 0;
        m_rowNum = -1;

        bool isValid = true;

        if (seneca::isCstrEmptyOrSpaces(content)) {
            isValid = false;
        }

        if (indentNum > 4 || indentSize > 4) {
            isValid = false;
        }

        if (rowNumber > (int)MaximumNumberOfMenuItems) {
            isValid = false;
        }

        if (isValid) {
            m_content = seneca::strCpyAndAloc(content);
            m_indentCount = indentNum;
            m_indentWidth = indentSize;
            m_rowNum = rowNumber;
        }
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    MenuItem::operator bool() const {
        return m_content != nullptr;
    }

    std::ostream& MenuItem::display(std::ostream& ostr) const {
        if (*this) {
            for (unsigned int i = 0; i < m_indentCount; ++i) {
                for (unsigned int j = 0; j < m_indentWidth; ++j) {
                    ostr << ' ';
                }
            }

            if (m_rowNum >= 0) {
                ostr << std::right << std::setw(2) << m_rowNum << "- ";
            }

            const char* tempContentPtr = m_content;
            while (*tempContentPtr != '\0' && std::isspace(*tempContentPtr)) {
                tempContentPtr++;
            }
            ostr << tempContentPtr;
        } else {
            ostr << "??????????";
        }
        return ostr;
    }

} // namespace seneca