#include"SELLER.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include<string>
#include<iostream>
#include<iomanip>
#include"USER_ACCOUNT.h"
using namespace std;
SELLER:: SELLER(USER_ACCOUNT sDetails){
    user_acc = sDetails;
}
 std:: string SELLER:: getUsername() const{return user_acc.getUsername();}
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
    int choice;
    cout << "[1] Add Product";
    cout << "[2] Add Price";
    cout << "[3] Add Quantity";
    cout << "Enter your choice:";
    cin >> choice;
    switch(choice)
    {
        case 1:
            //addProduct();
            break;
        case 2:
            //addPrice();
            break;
        case 3:
            //addQuantity();
            break;
        default:
            ConsoleHelper::PrintError();
    }
}
void SELLER:: viewProduct(std:: string){
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("----ALL PRODUCTS----");

    cout << left << setw(20) << "ProductName"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(15) << "Category" << endl;

    ConsoleHelper::PrintDivider();
    //logic
    ConsoleHelper::PrintDivider();
}
void SELLER:: searchProduct(std:: string keyword){
    ConsoleHelper::PrintHeader("GUEST-Search Products");
    ConsoleHelper::PrintHeader("-SEARCH OPTION-");
    cout << "[1] ProductName" << endl;
    cout << "[2] ProductCategory" << endl;
    cout << "[3] ProductID" << endl;
    cout << "searching For:" << keyword << endl;
    if(keyword=="ProductName")
        cout << "Enter ProductName:";
            //logic
    else if(keyword=="ProductCategory")
        cout << "Enter ProductCategory:";
            //logic
    else if(keyword=="ProductID")
        cout << "Enter ProductID:";
            //logic
    else
         ConsoleHelper::PrintError();
}
void SELLER:: addProduct(PRODUCT product){
        //logic
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}
void SELLER:: addPrice(std:: string productName, float productPrice){
        //logic
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRICE ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}
void SELLER:: addQuantity(std:: string productName, int qty){
        //logic
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT QUANTITY ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}