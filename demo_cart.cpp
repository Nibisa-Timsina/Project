#include "../include/CART.h"
#include "../include/ConsoleHelper.h"
#include "../include/UI_config.h"
#include "../include/PRODUCT.h"
#include <iostream>
using namespace std;

int main() {
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("DEMO - CART CODE");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();

    CART cart;

    PRODUCT apple("Fruits", "Apple", 120.0, 3);
    cart.addItem(apple);
    PRODUCT shampoo("PersonalCare", "Shampoo", 250.0, 2);
    cart.addItem(shampoo);
    PRODUCT laptop("Electronics", "Laptop", 120000.0, 1);
    cart.addItem(laptop);

    ConsoleHelper::PrintDivider();
    cout << "Samples loaded. Press Enter to see cart menu...";
    cin.get();
    cart.CartMenu();

    return 0;
}

