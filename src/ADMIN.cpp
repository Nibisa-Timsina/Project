#include <iostream>
#include <limits>
#include <vector>
#include "SYSTEM.h"
#include "USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
#include "../include/ADMIN.h"
using namespace std;

// Constructor
ADMIN::ADMIN(const std::string & pass) : passcode(pass)
{
}

// Authenticate admin with passcode
bool ADMIN::authenticate(AUTHORITY_SERVICE& auth)
{
    return auth.verifyAdmin(passcode);
}

// Perform admin action
void ADMIN::performAction()
{
    AdminMenu();
}

// Admin Menu
void ADMIN::AdminMenu()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-------ADMIN PANEL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "\n--- Admin Panel ---\n1. Manage User\n2. View all Products\n3. Add Product\n4. Remove Product\n5. Update Product\n6. Search Product\n7. Logout\n";
    cout << "Enter Choice: ";
}

// Get username
std::string ADMIN::getUsername() const
{
    return "ADMIN";
}

// Delete product by name
void ADMIN::deleteProduct(std::string productName)
{
    cout << "Deleting product: " << productName << endl;
}

// Update product
void ADMIN::updateProduct(PRODUCT product)
{
    cout << "Updating product: " << product.getName() << endl;
}

// Manage sales report
void ADMIN::manageSalesReport()
{
    cout << "Managing sales report..." << endl;
}

// View all users
void ADMIN::viewAllUsers()
{
    cout << "Viewing all users..." << endl;
}

// Generate sales report
void ADMIN::generateSalesReport()
{
    cout << "Generating sales report..." << endl;
}

// View product (implementing pure virtual)
void ADMIN::viewProduct(std::string productName)
{
    cout << "Viewing product: " << productName << endl;
}

// Search product (implementing pure virtual)
void ADMIN::searchProduct(std::string productName)
{
    cout << "Searching for product: " << productName << endl;
}
