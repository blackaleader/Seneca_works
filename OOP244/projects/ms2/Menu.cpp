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

    Menu::Menu(const char* title, const char* exitOptionContent, unsigned int indentNum, unsigned int indentSize)
    : m_title(title, indentNum, indentSize, -1),
      m_exitOption(exitOptionContent, indentNum, indentSize, 0),
      m_selectionPrompt("> ", indentNum, indentSize, -1)
    {
        m_indentNum = indentNum;
        m_indentSize = indentSize;
        m_numMenuItems = 0;
        for (unsigned int i = 0; i < MaximumNumberOfMenuItems; ++i) {
            m_menuItems[i] = nullptr;
        }
    }

    Menu::~Menu() {
        for (unsigned int i = 0; i < m_numMenuItems; ++i) {
            delete m_menuItems[i];
            m_menuItems[i] = nullptr;
        }
    }

    Menu& Menu::operator<<(const char* menuItemContent) {
        if (m_numMenuItems < MaximumNumberOfMenuItems) {
            m_menuItems[m_numMenuItems] = new MenuItem(menuItemContent, m_indentNum, m_indentSize, (int)m_numMenuItems + 1);
            m_numMenuItems++;
        }
        return *this;
    }

    size_t Menu::select() const {
        if (m_title) {
            m_title.display() << std::endl;
        }

        for (unsigned int i = 0; i < m_numMenuItems; ++i) {
            if (m_menuItems[i]) {
                m_menuItems[i]->display() << std::endl;
            }
        }

        m_exitOption.display() << std::endl;
        m_selectionPrompt.display();

        int selection = seneca::getInt(0, (int)m_numMenuItems);

        return (size_t)selection;
    }

    size_t operator<<(std::ostream& ostr, const Menu& m) {
        if (&ostr == &std::cout) {
            return m.select();
        }
        return 0;
    }

}