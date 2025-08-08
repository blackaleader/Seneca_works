#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {

    class Menu;

    class MenuItem {
        friend class Menu;

        char* ct;
        unsigned int iC;
        unsigned int iW;
        int rN;

        MenuItem(const MenuItem& ot) = delete;
        MenuItem& operator=(const MenuItem& ot) = delete;

        MenuItem(const char* c_c = nullptr,
                 unsigned int i_c = 0,
                 unsigned int i_s = 0,
                 int r_n = -1);

        ~MenuItem();

        operator bool() const;

        std::ostream& display(std::ostream& os = std::cout) const;
    };

    class Menu {
        unsigned int mi;
        unsigned int ms;
        size_t nm;
        MenuItem ti;
        MenuItem ex;
        MenuItem se;
        MenuItem* mIt[MaximumNumberOfMenuItems];

        Menu(const Menu& o) = delete;
        Menu& operator=(const Menu& o) = delete;

    public:
        Menu(const char* T, const char* E = "Exit",
             unsigned int I = 0, unsigned int S = 3);

        ~Menu();

        Menu& operator<<(const char* mIc);

        size_t select() const;

    };

    size_t operator<<(std::ostream& ostr, const Menu& m);

}

#endif // SENECA_MENU_H