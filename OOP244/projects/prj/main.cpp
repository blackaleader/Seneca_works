#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

int main() {
    Ordering ord("drinks.csv", "foods.csv");
    if (!ord) {
        cout << "Failed to open data files or the data files are corrupted!" << endl;
        return 1;
    }

    Menu mainMenu("Seneca Restaurant ", "End Program");
    mainMenu << "Order"
             << "Print Bill"
             << "Start a New Bill"
             << "List Foods"
             << "List Drinks";

    Menu orderMenu("Order Menu", "Back to main menu", 1);
    orderMenu << "Food"
              << "Drink";

    Menu exitConfirm("You have bills that are not saved, are you sue you want to exit?", "No");
    exitConfirm << "Yes";

    bool done = false;
    while (!done) {
        size_t choice = mainMenu.select();
        switch (choice) {
        case 0:
            if (ord.hasUnsavedBill()) {
                size_t c = exitConfirm.select();
                if (c == 1) done = true;
            } else {
                done = true;
            }
            break;
        case 1: {
            bool inOrder = true;
            while (inOrder) {
                size_t oc = orderMenu.select();
                if (oc == 0) inOrder = false;
                else if (oc == 1) ord.orderFood();
                else if (oc == 2) ord.orderDrink();
            }
            break;
        }
        case 2:
            ord.printBill(cout);
            break;
        case 3:
            ord.resetBill();
            break;
        case 4:
            ord.listFoods();
            break;
        case 5:
            ord.listDrinks();
            break;
        }
    }
    return 0;
}
