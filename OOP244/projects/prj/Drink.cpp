#include "Drink.h"
#include "Utils.h"
#include "Menu.h"
#include <iomanip>
#include <cstring>
#include <string>

namespace seneca {

    Drink::Drink() : Billable() {
        sz_char = '\0';
    }

    std::ostream& Drink::print(std::ostream& os) const {
        std::string name_str = (const char*)(*this);
        const int total_width_before_price = 33;

        if (ordered()) {
            std::string size_str;
            if (sz_char == 'S') {
                size_str = "SML..";
            } else if (sz_char == 'M') {
                size_str = "MID..";
            } else if (sz_char == 'L') {
                size_str = "LRG..";
            } else if (sz_char == 'X') {
                size_str = "XLR..";
            }
            int num_dots = total_width_before_price - name_str.length() - size_str.length();

            os << std::left << name_str;
            for (int i = 0; i < num_dots; ++i) {
                os << '.';
            }
            os << size_str;
            os << " ";
            os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << price();

        } else {
            int num_dots = total_width_before_price - name_str.length();

            os << std::left << name_str;
            for (int i = 0; i < num_dots; ++i) {
                os << '.';
            }
            os << " ";
            os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << price();
        }
        return os;
    }

    bool Drink::order() {
        Menu d_m("Drink Size Selection", "Back", 3, 3);
        d_m << "Small" << "Medium" << "Larg" << "Extra Large";

        size_t slc = std::cout << d_m;

        if (slc == 1) {
            sz_char = 'S';
        } else if (slc == 2) {
            sz_char = 'M';
        } else if (slc == 3) {
            sz_char = 'L';
        } else if (slc == 4) {
            sz_char = 'X';
        } else {
            sz_char = '\0';
        }
        return ordered();
    }

    bool Drink::ordered() const {
        return sz_char != '\0';
    }

    std::ifstream& Drink::read(std::ifstream& f) {
        char* t_nm = nullptr;
        double t_pr = 0.0;
        if (seneca::readFnamePrice(f, t_nm, t_pr)) {
            nm(t_nm);
            pr(t_pr);
            sz_char = '\0';
            delete[] t_nm;
        }
        return f;
    }

    double Drink::price() const {
        double bP = Billable::price();
        if (!ordered()) {
            return bP;
        }
        if (sz_char == 'S') {
            return bP * 0.5;
        } else if (sz_char == 'M') {
            return bP * 0.75;
        } else if (sz_char == 'L') {
            return bP;
        } else if (sz_char == 'X') {
            return bP * 1.5;
        }
        return bP;
    }

    std::ostream& operator<<(std::ostream& os, const Drink& d) {
        return d.print(os);
    }
}