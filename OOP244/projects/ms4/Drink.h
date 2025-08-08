// Drink.h
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"

namespace seneca {

    class Drink : public Billable {
        char sz_char;

    public:
        Drink();
        Drink(const Drink& o) = default; // Copy constructor
        Drink& operator=(const Drink& o) = default; // Copy assignment operator
        std::ostream& print(std::ostream& os = std::cout) const override;
        double price() const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& f) override;
    };

    std::ostream& operator<<(std::ostream& os, const Drink& d);
    std::istream& operator>>(std::istream& in, Drink& d);
}

#endif // SENECA_DRINK_H