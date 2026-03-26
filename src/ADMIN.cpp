#include<iostream>
using namespace std;
#include"ADMIN.h"
#include"USER.h"
#include"../include/ConsoleHelper.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<iomanip>
#include<string>
ADMIN:: ADMIN(const std:: string& pass): USER()
{
this -> passcode= pass;
}
bool ADMIN:: authenticate(AUTHORITY_SERVICE& auth) 
{
    return auth.verifyAdmin(passcode);
}
void ADMIN:: performAction() 
{
    cout<<"Admin entering system"<<endl;
}
std::string ADMIN::getUsername() const {
    return user_acc.getUsername();
}

// ------------------- ADMIN FUNCTIONS (UI to be implemented in main.cpp) -------------------
// Commented out as per user request - UI implementation on hold pending completion of main.cpp admin panel

/*
void ADMIN::AdminMenu()
{
    int choice;
    do {
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(11);
        ConsoleHelper::PrintHeader("ADMIN PANEL");
        ConsoleHelper::PrintDivider();
        ConsoleHelper::ResetColor();
        cout << "[1] Manage Products" << endl;
        cout << "[2] View Products" << endl;
        cout << "[3] Search Product" << endl;
        cout << "[4] Delete Product" << endl;
        cout << "[5] Update Product" << endl;
        cout << "[6] Manage Sales Report" << endl;
        cout << "[7] View All Users" << endl;
        cout << "[8] Generate Sales Report" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;
        ConsoleHelper::PrintDivider();

        switch(choice)
        {
            case 1: {
                string productName;
                cout << "Enter Product Name to Manage: ";
                cin >> productName;
                manageProduct(productName);
                break;
            }
            case 2: viewProduct(); break;
            case 3: {
                string keyword;
                cout << "Enter keyword to search: ";
                cin >> keyword;
                searchProduct(keyword);
                break;
            }
            case 4: {
                string productName;
                cout << "Enter Product Name to delete: ";
                cin >> productName;
                deleteProduct(productName);
                break;
            }
            case 5: {
                PRODUCT product;
                updateProduct(product); 
                break;
            }
            case 6: manageSalesReport(); break;
            case 7: viewAllUsers(); break;
            case 8: generateSalesReport(); break;
            case 0: ConsoleHelper::PrintHeader("Exiting Admin Panel... Goodbye!"); break;
            default: if (choice != -1) ConsoleHelper::PrintError();
        }
    } while(choice != 0);
}
*/

// void ADMIN:: viewProduct(){
    /*
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("----ALL PRODUCTS----");

    cout << left << setw(20) << "ProductName"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(15) << "Category" << endl;

    ConsoleHelper::PrintDivider();
    //logic
    ConsoleHelper::PrintDivider();
    */
// }

// void  ADMIN:: searchProduct(std:: string keyword){
    /*
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
    */
// }

// void ADMIN :: manageProduct(std:: string){
    /*
    int choice;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("MANAGE PRODUCT");
    cout << "[1] View Product" << endl;
    cout << "[2] Remove Product" << endl;
    cout << "[3] Add Product" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    switch(choice)
    {
        //case
    }
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
// }

void ADMIN :: deleteProduct(std:: string productName){
    /*
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("DELETE PRODUCT");
    cout << "Enter productName:" << endl;
    cin >> productName;
        //logic
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
}

void ADMIN:: updateProduct(PRODUCT product){
    /*
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("UPDATE PRODUCT");
        //logic
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
}

void ADMIN::viewAllUsers(){
    /*
    int choice;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("VIEW ALL USERS");
    cout << "[1] Client User" << endl;
    cout << "[2] Guest User" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    switch(choice)
    {
        //switch case
    }
    cout << left << setw(10) << "User_Id" << setw(20) << "User_Name" << endl;
    //logic
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
}

void ADMIN:: manageSalesReport(){
    /*
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("MANAGE SALES REPORT");
        //logic
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
}

void ADMIN::generateSalesReport()
{
    /*
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("GENERATE SALES REPORT");
        //logic
    ConsoleHelper::PrintDivider();
    cin.ignore();
    cin.get();
    */
}
