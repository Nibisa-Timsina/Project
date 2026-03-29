#include <iostream>
#include <limits>
#include <vector>
#include "SYSTEM.h"
#include "USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
#include "../include/ADMIN.h"
using namespace std;

// Constructor
ADMIN::ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc) 
    : passcode(pass)
{
    repo = &repository;
    auth_service = &auth_svc;
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

// Admin Menu - display only
void ADMIN::AdminMenu()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-------ADMIN PANEL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "\n--- Admin Panel ---\n";
    cout << "1. Manage User\n";
    cout << "2. View all Products\n";
    cout << "3. Add Product\n";
    cout << "4. Remove Product\n";
    cout << "5. Update Product\n";
    cout << "6. Search Product\n";
    cout << "7. Logout\n";
    cout << "Enter Choice: ";
}

void ADMIN::handleUserManagement()
{
    if (!auth_service)
    {
        cout << "Auth service not available." << endl;
        return;
    }

    vector<USER_ACCOUNT> users = auth_service->getAllRegisteredUsers();
    if (users.empty())
    {
        cout << "No users registered." << endl;
        return;
    }

    cout << "\nRegistered Users:\n";
    for (int i = 0; i < users.size(); i++)
    {
        cout << i + 1 << ". "
             << users[i].getFullname()
             << " | username: " << users[i].getUsername()
             << " | role: " << (users[i].getAuthority() == ClientSELLER ? "Seller" : "Buyer")
             << " | email: " << users[i].getMailAddress()
             << endl;
    }
    string usernameToDelete;
    cout << "Enter username to delete or 0 to go back: ";
    getline(cin, usernameToDelete);

    if (usernameToDelete == "0")
    {
        return;
    }
    if (auth_service->deleteUserByUsername(usernameToDelete))
    {
        cout << "User deleted successfully." << endl;
    }
    else
    {
        cout << "User not found or failed to delete." << endl;
    }
}

void ADMIN::handleProductOperations()
{
    if (!repo)
    {
        cout << "Product repository not available." << endl;
        return;
    }

    cout << "All Products:\n";
    repo->getAllProducts(true);
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

// Admin session handler
void ADMIN::startSession()
{
    bool adminLoggedIn = true;
    while (adminLoggedIn)
    {
        AdminMenu();
        int adminChoice;
        cin >> adminChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (adminChoice)
        {
            case 1:
                handleUserManagement();
                break;
            case 2:
                handleProductOperations();
                break;
            case 3:
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
                if (repo)
                {
                    repo->addProduct(product);
                    repo->saveToFile();
                    cout << "Product added successfully!" << endl;
                }
                break;
            }
            case 4:
                if (repo)
                {
                    repo->removeProduct();
                    repo->saveToFile();
                }
                break;
            case 5:
                if (repo)
                {
                    repo->updateProduct();
                    repo->saveToFile();
                }
                break;
            case 6:
            {
                string name;
                cout << "Enter product name to search: ";
                getline(cin, name);
                if (repo)
                {
                    repo->searchByName(name);
                }
                break;
            }
            case 7:
                cout << "Admin logout." << endl;
                adminLoggedIn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
