// Food.h
#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"

namespace seneca {

    class Food : public Billable {
        bool ord_b;
        bool ch_b;
        char* cust_str;

    public:
        Food();
        Food(const Food& ot);
        Food& operator=(const Food& ot);
        virtual ~Food();

        std::ostream& print(std::ostream& os = std::cout) const override;
        double price() const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& f) override;
    };

    std::ostream& operator<<(std::ostream& os, const Food& f);
    std::istream& operator>>(std::istream& in, Food& f);

}

#endif // SENECA_FOOD_H