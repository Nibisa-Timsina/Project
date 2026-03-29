#include"BUYER.h"
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
#include"../include/ConsoleHelper.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"

BUYER:: BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository){
    user_acc = Bdetails;
    repo = &repository;
}

bool BUYER:: authenticate(AUTHORITY_SERVICE& auth) {
     return auth.verifyClient(user_acc.getUsername(), "");
}

void BUYER:: performAction() {
    cout<<"Buyer interacting"<<endl;
}

std:: string BUYER:: getUsername()const{
    return user_acc.getUsername();
}

void BUYER::BuyerMenu()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BUYER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();  
    cout << "[1] View Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] Place Order" << endl;
    cout << "[4] View Cart" << endl;
    cout << "[5] Edit Cart" << endl;
    cout << "[6] Logout" << endl;
    cout << "Enter your Choice: ";
}

void BUYER::handleSearch()
{
    string keyword;
    cout << "Enter the product name: ";
    cin.ignore();
    getline(cin, keyword);
    if (repo)
    {
        repo->searchByName(keyword);
    }
}

void BUYER:: viewProduct(std:: string) {
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("----ALL PRODUCTS----");

    cout << left << setw(20) << "ProductName"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(15) << "Category" << endl;

    ConsoleHelper::PrintDivider();
    if (repo)
    {
        repo->getAllProducts(false);
    }
    ConsoleHelper::PrintDivider();
}

void BUYER:: searchProduct(std:: string keyword){
    ConsoleHelper::PrintHeader("GUEST-Search Products");
    ConsoleHelper::PrintHeader("-SEARCH OPTION-");
    cout << "[1] ProductName" << endl;
    cout << "[2] ProductCategory" << endl;
    cout << "[3] ProductID" << endl;
    cout << "searching For:" << keyword << endl;
    if(keyword=="ProductName")
        cout << "Enter ProductName:";
    else if(keyword=="ProductCategory")
        cout << "Enter ProductCategory:";
    else
         ConsoleHelper::PrintError();
}

void BUYER:: myProducts(){}

void BUYER:: placeOrder(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PLACE ORDER-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void BUYER:: viewCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------VIEW CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void BUYER :: editCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------EDIT CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void  BUYER:: requestBill(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BILL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void BUYER::startSession()
{
    bool buyerLoggedIn = true;
    while (buyerLoggedIn)
    {
        BuyerMenu();
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                viewProduct("");
                break;
            case 2:
                handleSearch();
                break;
            case 3:
                placeOrder();
                break;
            case 4:
                viewCart();
                break;
            case 5:
                editCart();
                break;
            case 6:
                cout << "Logging out..." << endl;
                buyerLoggedIn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
