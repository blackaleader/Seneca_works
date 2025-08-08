// Food.cpp
#include "Food.h"
#include "Utils.h"
#include <iomanip>
#include <cstring>
#include <string>

namespace seneca {

    Food::Food() : Billable() {
        ord_b = false;
        ch_b = false;
        cust_str = nullptr;
    }

    Food::Food(const Food& ot) : Billable(ot) {
        ord_b = ot.ord_b;
        ch_b = ot.ch_b;
        cust_str = seneca::strCpyAndAloc(ot.cust_str);
    }

    Food& Food::operator=(const Food& ot) {
        if (this != &ot) {
            Billable::operator=(ot);
            ord_b = ot.ord_b;
            ch_b = ot.ch_b;
            delete[] cust_str;
            cust_str = seneca::strCpyAndAloc(ot.cust_str);
        }
        return *this;
    }

    Food::~Food() {
        delete[] cust_str;
    }

    std::ostream& Food::print(std::ostream& os) const {
        std::string name_display = (const char*)(*this);

        if (ordered()) {
            if (name_display.length() > 28) {
                name_display = name_display.substr(0, 28);
            } else {
                name_display.resize(28, '.');
            }
            os << std::left << name_display;

            std::string portion_str;
            if (ch_b) {
                portion_str = "Child";
            } else {
                portion_str = "Adult";
            }
            os << std::left << std::setw(7) << portion_str; 
            os << std::right << std::setw(5) << std::fixed << std::setprecision(2) << price();

            if (&os == &std::cout && cust_str != nullptr) {
                os << " >> ";
                size_t ln = std::strlen(cust_str);
                for (size_t i_i = 0; i_i < ln && i_i < 30; ++i_i) {
                    os << cust_str[i_i];
                }
            }
        } else {
            if (name_display.length() > 33) {
                name_display = name_display.substr(0, 33);
            } else {
                name_display.resize(33, '.');
            }
            os << std::left << name_display;
            os << " "; 
            os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << price();
        }
        return os;
    }

    double Food::price() const {
        double bp = Billable::price();
        if (ordered() && ch_b) {
            return bp * 0.5;
        }
        return bp;
    }

    bool Food::order() {
        Menu f_m("Food Size Selection", "Back", 3, 3);
        f_m << "Adult" << "Child";

        size_t s = std::cout << f_m;

        if (s == 1) {
            ch_b = false;
            ord_b = true;
        } else if (s == 2) {
            ch_b = true;
            ord_b = true;
        } else {
            ord_b = false;
            delete[] cust_str;
            cust_str = nullptr;
            return false;
        }

        std::cout << "Special instructions" << std::endl;
        std::cout << "> ";
        delete[] cust_str;
        cust_str = seneca::getDynCstrInput();

        return true;
    }

    bool Food::ordered() const {
        return ord_b;
    }

    std::ifstream& Food::read(std::ifstream& f) {
        char* t_n = nullptr;
        double t_p = 0.0;
        if (seneca::readFnamePrice(f, t_n, t_p)) {
            nm(t_n);
            pr(t_p);
            ch_b = false;
            ord_b = false;
            delete[] cust_str;
            cust_str = nullptr;
            delete[] t_n;
        }
        return f;
    }

}