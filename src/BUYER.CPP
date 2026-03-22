#include"BUYER.h"
#include<iostream>
#include<iomanip>
using namespace std;
#include"../include/ConsoleHelper.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
BUYER:: BUYER(USER_ACCOUNT Bdetails){
    user_acc = Bdetails;
    full_name = Bdetails.getFullname();
    username = Bdetails.getUsername();
    password = Bdetails.getPassword();
}
bool BUYER:: authenticate(AUTHORITY_SERVICE& auth) {
     return auth.verifyClient(username, "");
}
void BUYER:: performAction() {
    cout<<"Buyer interacting"<<endl;
}
std:: string BUYER:: getUsername()const{
    return username;
}
void BUYER::BuyerMenu()
{
    int choice;
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BUYER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();  
    cout << "[1] View Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] PlaceOrder" << endl;
    cout << "[4] View Cart" << endl;
    cout << "[5] Edit Cart" << endl;
    cout << "Enetr your Choice:";
    cin >> choice;
    switch(choice)
    {
        case 1:
            //viewProduct();
            break;
        case 2:
            //searchProduct();
            break;
        case 3:
            //placeOrder();
            break;
        case 4:
            //viewCart();
            break;
        case 5:
            //editCart();
            break;
        default:
            ConsoleHelper::PrintError();
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
    //logic
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
            //logic
    else if(keyword=="ProductCategory")
        cout << "Enter ProductCategory:";
            //logic
    else
         ConsoleHelper::PrintError();
}
void BUYER:: addToCart(){
    //LOGIC
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------ITEM ADDED SUCCESSFULLY-------");
    ConsoleHelper::ResetColor();    
    ConsoleHelper::PrintDivider();
}
void BUYER:: checkout(){}
void BUYER:: myProducts(){}
void BUYER:: placeOrder(){
        //LOGIC
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
    //LOGIC
}
void BUYER :: editCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------EDIT CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}
void  BUYER:: requestBill(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BILL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}
