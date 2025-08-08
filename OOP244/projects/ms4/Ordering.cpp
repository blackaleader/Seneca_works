#include "Ordering.h"
#include "Utils.h"
#include "Billable.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace seneca {
    
    Ordering::Ordering(const char* drinkFileName, const char* foodFileName) {
        m_foodArray = nullptr;
        m_drinkArray = nullptr;
        m_foodCount = 0;
        m_drinkCount = 0;
        m_billItemCount = 0;
        m_billNumber = 1;
        for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
            m_billItems[i] = nullptr;
        }

        std::ifstream foodFile(foodFileName);
        if (foodFile) {
            m_foodCount = countRecords(foodFileName);
            if (m_foodCount > 0) {
                m_foodArray = new Food[m_foodCount];
                for (size_t i = 0; i < m_foodCount; ++i) {
                    m_foodArray[i].read(foodFile);
                }
            }
        }
        
        std::ifstream drinkFile(drinkFileName);
        if (drinkFile) {
            m_drinkCount = countRecords(drinkFileName);
            if (m_drinkCount > 0) {
                m_drinkArray = new Drink[m_drinkCount];
                for (size_t i = 0; i < m_drinkCount; ++i) {
                    m_drinkArray[i].read(drinkFile);
                }
            }
        }
    }

    Ordering::~Ordering() {
        delete[] m_foodArray;
        delete[] m_drinkArray;
        cleanBill();
    }

    Ordering::operator bool() const {
        return m_foodCount > 0 && m_drinkCount > 0;
    }
    
    unsigned int Ordering::noOfBillItems() const {
        return m_billItemCount;
    }

    size_t Ordering::countRecords(const char* file) const {
        std::ifstream f(file);
        size_t count = 0;
        if (f) {
            std::string line;
            while (std::getline(f, line)) {
                count++;
            }
        }
        return count;
    }

    void Ordering::listFoods() const {
        if (!*this) return;
        std::cout << "List Of Avaiable Meals\n";
        std::cout << "========================================\n";
        for (size_t i = 0; i < m_foodCount; i++) {
            std::cout << m_foodArray[i];
            if (i < m_foodCount - 1) std::cout << "\n";
        }
        std::cout << "\n========================================\n";
    }

    void Ordering::listDrinks() const {
        if (!*this) return;
        std::cout << "List Of Avaiable Drinks\n";
        std::cout << "========================================\n";
        for (size_t i = 0; i < m_drinkCount; i++) {
            std::cout << m_drinkArray[i];
            if (i < m_drinkCount - 1) std::cout << "\n";
        }
        std::cout << "\n========================================\n";
    }

    void Ordering::orderFood() {
        if (!*this) return;
        Menu f_menu("Food Menu", "Back to Order", 2, 3);
        for (size_t i = 0; i < m_foodCount; ++i) {
            f_menu << (const char*)m_foodArray[i];
        }

        size_t selection = std::cout << f_menu;
        if (selection > 0) {
            if (m_billItemCount < MaximumNumberOfMenuItems) {
                m_billItems[m_billItemCount] = new Food(m_foodArray[selection - 1]);
                if (m_billItems[m_billItemCount]->order()) {
                    m_billItemCount++;
                } else {
                    delete m_billItems[m_billItemCount];
                    m_billItems[m_billItemCount] = nullptr;
                }
            }
        }
    }

    void Ordering::orderDrink() {
        if (!*this) return;
        Menu d_menu("Drink Menu", "Back to Order", 2, 3);
        for (size_t i = 0; i < m_drinkCount; ++i) {
            d_menu << (const char*)m_drinkArray[i];
        }

        size_t selection = std::cout << d_menu;
        if (selection > 0) {
            if (m_billItemCount < MaximumNumberOfMenuItems) {
                m_billItems[m_billItemCount] = new Drink(m_drinkArray[selection - 1]);
                if (m_billItems[m_billItemCount]->order()) {
                    m_billItemCount++;
                } else {
                    delete m_billItems[m_billItemCount];
                    m_billItems[m_billItemCount] = nullptr;
                }
            }
        }
    }

    void Ordering::printBill(std::ostream& os) const {
        if (m_billItemCount == 0) return;
        double total = 0.0;
        double tax = 0.0;
        billTitlePrint(os);
        for (size_t i = 0; i < m_billItemCount; i++) {
            m_billItems[i]->print(os);
            os << "\n";
            total += m_billItems[i]->price();
        }
        tax = total * Tax;
        printTotals(os, total);
        os << "                     Total+Tax:   " << std::right << std::setw(6) << std::fixed << std::setprecision(2) << total + tax << "\n";
        os << "========================================\n";
    }

    void Ordering::billTitlePrint(std::ostream& os) const {
        os << "Bill # " << std::right << std::setw(3) << std::setfill('0') << m_billNumber << " =============================\n";
        os << std::setfill(' ');
    }

    void Ordering::printTotals(std::ostream& os, double total) const {
        double tax = total * Tax;
        os << "                     Total:       " << std::right << std::setw(6) << std::fixed << std::setprecision(2) << total << "\n";
        os << "                     Tax:         " << std::right << std::setw(6) << std::fixed << std::setprecision(2) << tax << "\n";
    }

    bool Ordering::hasUnsavedBill() const {
        return m_billItemCount > 0;
    }

    void Ordering::resetBill() {
        if (hasUnsavedBill()) {
            std::cout << "Saved bill number " << m_billNumber << "\n";
            std::cout << "Starting bill number " << (m_billNumber + 1) << "\n";
            // Create a stringstream to capture bill output, then print it
            // This way Food::print won't detect it as std::cout and won't show special instructions
            std::ostringstream billStream;
            printBill(billStream);
            std::cout << billStream.str();
            m_billNumber++;
            cleanBill();
        }
    }

    void Ordering::cleanBill() {
        for (size_t i = 0; i < m_billItemCount; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }
        m_billItemCount = 0;
    }
}