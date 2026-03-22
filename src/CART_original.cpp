#include "../include/ConsoleHelper.h"
#include "../include/CART.h"
#include "../include/UI_config.h"
#include "../include/PRODUCT.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

void CART::printMenu()
{
    cout << "[1] ➕ Add Item" << endl;
    cout << "[2] 🗑️ Remove Item" << endl;
    cout << "[3] 📝 Update Quantity" << endl;
    cout << "[4] 📋 View Cart" << endl;
    cout << "[5] 🧮 Calculate Total" << endl;
    cout << "[0] ❌ Exit" << endl;
}

void CART::CartMenu()
{
    int choice;
    while (true) {
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(11);
        ConsoleHelper::PrintHeader("CART MENU");
        cout << endl;
        ConsoleHelper::PrintDivider();
        ConsoleHelper::ResetColor();
        printMenu();
        cout << "Enter your choice: ";
        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            ConsoleHelper::PrintError();
            cout << "Invalid input. Press Enter to continue...";
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');
        switch(choice)
        {
            case 1:
                // TODO: addItem(product);
                cout << "Add item stub" << endl;
                ConsoleHelper::PrintSuccess();
                break;
            case 2:
                // TODO: removeItem(product_name);
                cout << "Remove item stub" << endl;
                ConsoleHelper::PrintSuccess();
                break;
            case 3:
                // TODO: updateQuantity(product_name, qty);
                cout << "Update quantity stub" << endl;
                ConsoleHelper::PrintSuccess();
                break;
            case 4:
                viewCart();
                break;
            case 5:
                calculateTotal();
                break;
            case 0:
                cout << "Exiting cart menu." << endl;
                return;
            default:
                ConsoleHelper::PrintError();
                cout << "Invalid choice. Press Enter to continue...";
                cin.ignore(10000, '\n');
        }
        cout << "Press Enter to continue...";
        cin.ignore(10000, '\n');
    }
}

void CART::addItem(const PRODUCT product)
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-------ITEM ADDED--------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    // TODO: logic to add product to cart_items
    ConsoleHelper::PrintHeader("------------ITEM ADDED SUCCESSFULLY---------");
}

void CART::removeItem(const std::string product_name )
{
    // TODO: logic
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-------ITEM REMOVED SUCCESSFULLY--------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void CART::updateQuantity(const std::string product_name, int qnt)
{
    // TODO: logic
    ConsoleHelper::PrintHeader("-------ITEM UPDATED SUCCESSFULLY----------");
    cout << left << setw(10) << "ProductName" << setw(20) << "Quantity" << endl;
    cout << left << setw(10) << product_name << setw(20) << qnt << endl;     
}

void CART::viewCart()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintDivider();
    cout << endl;
    ConsoleHelper::PrintDivider();
    cout << endl;
    ConsoleHelper::SetColor(11);
    cout << left << setw(10);
    ConsoleHelper::PrintHeader("🛒 YOUR CART");
    ConsoleHelper::ResetColor();
    cout << endl;
    ConsoleHelper::PrintDivider();
    cout << "Cart is empty (stub implementation - add items to see contents)" << endl;
    cout << left << setw(10) << "Product Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(20) << "Category" << endl;
    ConsoleHelper::PrintDivider();
    cout << endl;
    //logic for view product 
    //cout << left << setw(10) << "Product Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(20) << "Category" << endl;
    //in this pattern
    ConsoleHelper::PrintDivider();
    cout << endl;
    cout << left << setw(10) << "TOTAL ITEMS:" << /*LOGIC FOR TOTAL ITEMS*/ endl;
    cout << left << setw(10) << "TOTAL AMOUNTS:" << /*LOGIC FOR TOTAL AMOUNTS*/ endl;
    ConsoleHelper::PrintDivider();
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore(10000, '\n');
}

double CART::calculateTotal()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("CART TOTAL");
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Total amount: $0.00 (stub - populate cart to calculate)" << endl;
    cout << "Press Enter to continue...";
    cin.ignore(10000, '\n');
    return 0.0;
}

