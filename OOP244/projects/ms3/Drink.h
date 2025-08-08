#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"
#include "Menu.h"

namespace seneca {

    class Drink : public Billable {
        char sz_char;

    public:
        Drink();

        std::ostream& print(std::ostream& os = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& f) override;
        double price() const override;
    };

}

#endif // SENECA_DRINK_H