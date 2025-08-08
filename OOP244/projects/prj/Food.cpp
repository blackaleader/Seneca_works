#include "Food.h"
#include "Utils.h"
#include "Menu.h"
#include <iomanip>
#include <cstring>
#include <string>

namespace seneca {

    Food::~Food() {
        delete[] cust_str;
    }

    Food::Food(const Food& ot) : Billable(ot) {
        ord_b = ot.ord_b;
        ch_b = ot.ch_b;
        cust_str = seneca::strCpyAndAloc(ot.cust_str);
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

    std::ostream& Food::print(std::ostream& os) const {
        std::string name_str = (const char*)(*this);
        const int total_width_before_price = 33;
        
        if (ordered()) {
            std::string portion_str;
            if (ch_b) {
                portion_str = "Child";
            } else {
                portion_str = "Adult";
            }
            int num_dots = total_width_before_price - name_str.length() - portion_str.length();
            
            os << std::left << name_str;
            for (int i = 0; i < num_dots; ++i) {
                os << '.';
            }
            os << portion_str;
            os << " ";
            os << std::right << std::setw(6) << std::fixed << std::setprecision(2) << price();

            if (&os == &std::cout && cust_str != nullptr) {
                os << " >> ";
                size_t ln = std::strlen(cust_str);
                for (size_t i_i = 0; i_i < ln && i_i < 30; ++i_i) {
                    os << cust_str[i_i];
                }
            }
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
            // The following line is the fix for the memory leak:
            delete[] t_n;
        }
        return f;
    }

    std::ostream& operator<<(std::ostream& os, const Food& f) {
        return f.print(os);
    }
    
    Food::Food() : Billable() {
        ord_b = false;
        ch_b = false;
        cust_str = nullptr;
    }
}