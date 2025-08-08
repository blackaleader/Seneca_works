#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {

    class Menu;

    class MenuItem {
        friend class Menu;

        char* m_content;
        unsigned int m_indentCount;
        unsigned int m_indentWidth;
        int m_rowNum;

        MenuItem(const MenuItem& other) = delete;
        MenuItem& operator=(const MenuItem& other) = delete;

        MenuItem(const char* content = nullptr,
                 unsigned int indentNum = 0,
                 unsigned int indentSize = 0,
                 int rowNumber = -1);

        ~MenuItem();

        operator bool() const;

        std::ostream& display(std::ostream& ostr = std::cout) const;
    };

    class Menu {
        unsigned int m_indentNum;
        unsigned int m_indentSize;
        unsigned int m_numMenuItems;
        MenuItem m_title;
        MenuItem m_exitOption;
        MenuItem m_selectionPrompt;
        MenuItem* m_menuItems[MaximumNumberOfMenuItems];

        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

    public:
        Menu(const char* title, const char* exitOptionContent = "Exit",
             unsigned int indentNum = 0, unsigned int indentSize = 3);

        ~Menu();

        Menu& operator<<(const char* menuItemContent);

        size_t select() const;

    };

    size_t operator<<(std::ostream& ostr, const Menu& m);

}

#endif // SENECA_MENU_H