#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {

    class MenuItem {
        char* m_content;
        unsigned int m_indentCount;
        unsigned int m_indentWidth;
        int m_rowNum;

        MenuItem(const MenuItem& other) = delete;
        MenuItem& operator=(const MenuItem& other) = delete;

    public:
        MenuItem(const char* content = nullptr,
                 unsigned int indentNum = 0,
                 unsigned int indentSize = 0,
                 int rowNumber = -1);

        ~MenuItem();

        operator bool() const;

        std::ostream& display(std::ostream& ostr = std::cout) const;
    };

} // namespace seneca

#endif // SENECA_MENU_H