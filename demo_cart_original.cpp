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
    cart.CartMenu();

    return 0;
}

