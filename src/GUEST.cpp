#include<string>
#include"../include/ConsoleHelper.h"
#include"GUEST.h"
#include"AUTHORITY_SERVICE.h"
#include<iostream>
#include<iomanip>
using namespace std;
GUEST:: GUEST(): USER()
{
    location = " ";
    mail_address = " ";

}

    bool GUEST::  authenticate(AUTHORITY_SERVICE& auth)  {
        return auth.verifyClient(username, password); // Guest registration
    }

void GUEST:: performAction() { std::cout << "Guest browsing\n"; }
void GUEST :: registerToSystem(){
    ConsoleHelper::PrintHeader("-----REGISTRATION PANEL-----");
    cout<<"Enter your Full-Name: ";
    cin>>full_name;
    cout<<"Enter your Username: ";
    cin>>username;
    cout<<"Enter your Password: ";
    cin>>password;
    cout<<"Enter your Location: ";
    cin>>location;
    cout<<"Enter your Email Address: ";
    cin>>mail_address;
    cout<<"Enter your age: ";
    cin>>age;
    ConsoleHelper::PrintHeader("----REGISTRATION SUCESSFULL-----");
}
void GUEST:: viewProducts(){
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
void GUEST :: searchProducts(std:: string keyword){
    ConsoleHelper::PrintHeader("GUEST-Search Products");
    ConsoleHelper::PrintHeader("-SEARCH OPTION-");
    cout << "[1] ProductName" << endl;
    cout << "[2] ProductCategory" << endl;
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
GUEST:: ~GUEST(){};