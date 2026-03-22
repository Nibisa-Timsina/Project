#include<iostream>
#include"../include/ConsoleHelper.h"
#include"../include/CartMenu.h"
#include"../include/CART.h"
#include"../include/BILL.h"
using namespace std;
void CartMenu::editCartItems()
{
    int choice;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("EDIT CART ITEMS");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "[1] remove Item :" << endl;
    cout << "[2] update Quantity :" << endl;
    cout << "Enter your choice:" << endl;
    cin >> choice;
    /*switch(choice)
    {
        case 1:
            string product_name;
            cout << "Enter Product Name:" << endl;
            cin >> product_name;
            Cart.removeItem(product_name);
            break;
        case 2:
            string product_name;
            int qnt;
            cout << "Enter Product Name:" << endl;
            cin >> product_name;
            cout << "Enter quantity:" << endl;
            cin >> qnt;
            Cart.updateQuantity(product_name,qnt);
            break;
        default:
            ConsoleHelper::PrintError();
    }*/
}
void CartMenu::proceedToCheckout()
{
    int choice;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("PROCEED_TO_CHECKOUT");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "[1] confirm your cart Items:"<< endl;
    cout << "[2] Go back to cart menu:" << endl;
    cout << "Enter your choice:" << endl;
    cin >> choice;
    /*switch(choice)
    {
        case 1:
            Bill.createBill(cart,  userId );
            Bill.autoGenerateBill(cart);
            Bill.autoConfirmSale( billId );
           break;
        case 2:
            showCart();
            break;
        default:
            ConsoleHelper::PrintError();
    }  */ 
}
void CartMenu::requestBillView()
{
    int choice;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("REQUEST BILL VIEW");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "[1] view Bill:" << endl;
    cout << "[2] Go back to cart menu:" << endl;
    cout << "Enter your choice:" << endl;
    cin >> choice;
    /*switch(choice)
    {
        case 1:
            Bill.getSalesReport();
        case 2:
            CartMenu.ShowCart();
            break;
        default:

    }*/
}
void CartMenu::confirmPurchase()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("CONFIRM PURCHASE");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //Bill.autoConfirmSale(/* billId */);
    //logic
}
void CartMenu::viewCartItems()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("VIEW CART ITEMS");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();  
    //Cart.viewCart();
    //logic
}
void CartMenu::showCart()
{
    int choice;
    cout << "[1] editCartItems" << endl;
    cout << "[2] proceedToCheckout" << endl;
    cout << "[3] requestBillView" << endl;
    cout << "[4] confirmPurchase" << endl;
    cout << "[5] viewCartItems" << endl;
    cout << "[1] Exit" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    switch(choice)
    {
        case 1: editCartItems(); break;
        case 2: proceedToCheckout(); break;
        case 3: requestBillView(); break;
        case 4: confirmPurchase(); break;
        case 5: viewCartItems(); break;
        case 6: cout << "Exiting cart menu !!!"; break;
        default: ConsoleHelper::PrintError();
    }
}