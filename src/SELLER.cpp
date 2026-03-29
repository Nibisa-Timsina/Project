#include"SELLER.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<limits>
#include"USER_ACCOUNT.h"
using namespace std;

SELLER:: SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository){
    user_acc = sDetails;
    repo = &repository;
}

std:: string SELLER:: getUsername() const{
    return user_acc.getUsername();
}

bool SELLER:: authenticate(AUTHORITY_SERVICE& auth) {
    return auth.verifyClient(user_acc.getUsername(), "");   
}

void SELLER:: performAction(){
    cout<<"Seller interacting"<<endl;
}

void SELLER::SellerMenu()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------SELLER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "[1] Add Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] View Products" << endl;
    cout << "[4] Logout" << endl;
    cout << "Enter your choice: ";
}

void SELLER:: viewProduct(std:: string){
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

void SELLER:: searchProduct(std:: string keyword){
    if (repo)
    {
        repo->searchByName(keyword);
    }
}

void SELLER:: addProduct(PRODUCT product){
    if (repo)
    {
        repo->addProduct(product);
        repo->saveToFile();
    }
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void SELLER:: addPrice(std:: string productName, float productPrice){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRICE ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void SELLER:: addQuantity(std:: string productName, int qty){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT QUANTITY ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void SELLER::startSession()
{
    bool sellerLoggedIn = true;
    while (sellerLoggedIn)
    {
        SellerMenu();
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
            {
                string category, name;
                double price;
                int qty;
                cout << "Enter product category: ";
                getline(cin, category);
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> qty;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                PRODUCT product(category, name, price, qty);
                addProduct(product);
                break;
            }
            case 2:
            {
                string productName;
                cout << "Enter product name to search: ";
                getline(cin, productName);
                searchProduct(productName);
                break;
            }
            case 3:
                viewProduct("");
                break;
            case 4:
                cout << "Logging out..." << endl;
                sellerLoggedIn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}