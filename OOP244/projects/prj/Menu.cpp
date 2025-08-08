#include "Menu.h"
#include "Utils.h"
#include <iomanip>
#include <cstring>
#include <cctype>

namespace seneca {

    MenuItem::MenuItem(const char* c_c, unsigned int i_c, unsigned int i_s, int r_n) {
        ct = nullptr;
        iC = 0;
        iW = 0;
        rN = -1;

        bool ok = true;

        if (seneca::isCstrEmptyOrSpaces(c_c)) {
            ok = false;
        }

        if (i_c > 4 || i_s > 4) {
            ok = false;
        }

        if (r_n > (int)MaximumNumberOfMenuItems) {
            ok = false;
        }

        if (ok) {
            ct = seneca::strCpyAndAloc(c_c);
            iC = i_c;
            iW = i_s;
            rN = r_n;
        }
    }

    MenuItem::~MenuItem() {
        delete[] ct;
    }

    MenuItem::operator bool() const {
        return ct != nullptr;
    }

    std::ostream& MenuItem::display(std::ostream& os) const {
        if (*this) {
            for (unsigned int i_i = 0; i_i < iC; ++i_i) {
                for (unsigned int j_j = 0; j_j < iW; ++j_j) {
                    os << ' ';
                }
            }

            if (rN >= 0) {
                os << std::right << std::setw(2) << rN << "- ";
            }

            const char* tc = ct;
            while (*tc != '\0' && std::isspace(*tc)) {
                tc++;
            }
            os << tc;
        } else {
            os << "??????????";
        }
        return os;
    }

    Menu::Menu(const char* T, const char* E, unsigned int I, unsigned int S)
    : ti(T, I, S, -1),
      ex(E, I, S, 0),
      se("> ", I, S, -1)
    {
        mi = I;
        ms = S;
        nm = 0;
        for (size_t iii = 0; iii < MaximumNumberOfMenuItems; ++iii) {
            mIt[iii] = nullptr;
        }
    }

    Menu::~Menu() {
        for (size_t i_i = 0; i_i < nm; ++i_i) {
            delete mIt[i_i];
            mIt[i_i] = nullptr;
        }
    }

    Menu& Menu::operator<<(const char* mIc) {
        if (nm < MaximumNumberOfMenuItems) {
            mIt[nm] = new MenuItem(mIc, mi, ms, (int)nm + 1);
            nm++;
        }
        return *this;
    }

    size_t Menu::select() const {
        if (ti) {
            ti.display() << std::endl;
        }

        for (size_t idx = 0; idx < nm; ++idx) {
            if (mIt[idx]) {
                mIt[idx]->display() << std::endl;
            }
        }

        ex.display() << std::endl;
        se.display();

        int sel = seneca::getInt(0, (int)nm);

        return (size_t)sel;
    }

    size_t operator<<(std::ostream& ostr, const Menu& m) {
        if (&ostr == &std::cout) {
            return m.select();
        }
        return 0;
    }

}