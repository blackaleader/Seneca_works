#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iostream>
#include <fstream>
#include "Billable.h"
#include "Food.h"
#include "Drink.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"

namespace seneca {

    class Ordering {
        Food* m_foodArray;
        Drink* m_drinkArray;
        Billable* m_billItems[MaximumNumberOfMenuItems];

        unsigned int m_foodCount;
        unsigned int m_drinkCount;
        unsigned int m_billItemCount;
        unsigned int m_billNumber;

        size_t countRecords(const char* file) const;
        void billTitlePrint(std::ostream& os) const;
        void printTotals(std::ostream& os, double total) const;
        void cleanBill();

    public:
        Ordering(const char* foodFileName, const char* drinkFileName);
        ~Ordering();

        Ordering(const Ordering& o) = delete;
        Ordering& operator=(const Ordering& o) = delete;

        operator bool() const;
        unsigned int noOfBillItems() const;
        bool hasUnsavedBill() const;
        void listFoods() const;
        void listDrinks() const;
        void orderFood();
        void orderDrink();
        void printBill(std::ostream& os) const;
        void resetBill();
    };
}
#endif // SENECA_ORDERING_H