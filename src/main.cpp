#include <iostream>
#include <limits>
#include "SYSTEM.h"
#include "USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
using namespace std;
#include "PRODUCT_REPO.h"
#include "PRODUCT.h"
#include <string>
using std::cout;

int main()
{
    cout << endl;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------------SALES & INVENTORY SYSTEM---------------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << endl;
     
    SYSTEM system;
    
    bool adminLoggedIn = false;
    while (true)
    {
        int choice;
        cout << "1. Register\n2. User Login\n3. User Log out\n4. Admin Login\n5. Exit\nEnter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            string fullName, username, password, contactNo, location, email;
            int age;
            int roleChoice;

            cout << "Enter full name: ";
            getline(cin, fullName);
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Enter contact number: ";
            getline(cin, contactNo);
            cout << "Enter age: ";
            cin >> age;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age. Registration cancelled." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter location: ";
            getline(cin, location);
            cout << "Enter email address: ";
            getline(cin, email);
            cout << "Select role " << endl;
            cout << "[1]  Buyer" << endl << "[2] Seller" << endl;
            cin >> roleChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid role. Registration cancelled." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Authority role = (roleChoice == 2) ? ClientSELLER : ClientBUYER;
            USER_ACCOUNT newAccount(fullName, username, password, contactNo, age, location, email, role);

            if (system.registerAccount(newAccount))
            {
                cout << "Registration successful!" << endl;
            }
            else
            {
                cout << "Username already exists. Try another username." << endl;
            }
        }
        else if (choice == 2)
        {
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            USER* user = system.loginAccount(username, password);
            if (user)
            {
                cout << "Welcome, " << user->getUsername() << "!" << endl;
            
            while(1)
            {
                if(user->getAuthority()==ClientSELLER)
                {
                    cout<<"MENU\n"<<endl;
                    cout<<"1. Add Product\n 2. Search Product\n 3. Logout\n"<<endl;
                    int choice;
                    cout<<"Select from the menu: ";
                    cin>>choice;
                    if(choice==1)
                    {
                        std:: string category,name;
                        double price;
                        int qty;
                     cout<<"Enter the details:\n";
                    cout<< "Category: \n Name: \n Price: \n Quantity: \n"<<endl;
                    cin>>category>>name>>price>>qty;
                    PRODUCT product(category, name,price, qty);
                    system.addProduct(product);   
                    }
                    else if(choice==2)
                    {
                        std::string name;
                        cout<<"Enter the product name: ";
                        cin>>name;
                        system.searchByName(name);
                    }
                    else if(choice==3)
                    {
                        system.logoutCurrentUser();
                        break;
                    }
                }
                else if(user->getAuthority()==ClientBUYER)
                {
                    cout<<"MENU";
                    cout<<"1. Search Product\n 2. Logout"<<endl;
                    int choice;
                    cout<<"Select from the menu: "<<endl;
                    cin>>choice;
                    if(choice==1)
                    {
                        std::string name;
                        cout<<"Enter the product name: ";
                        cin>>name;
                        system.searchByName(name);
                    }
                    else if(choice==2)
                    {
                        system.logoutCurrentUser();
                        break;
                    }
                }
                else{
                    cout<<"invlaid"<<endl;
                }
            }
        }
        
        }
        else if (choice == 3)
        {
            system.logoutCurrentUser();
        }
        else if (choice == 4)
        {
            string adminPass;
            cout << "Enter admin passcode: ";
            getline(cin, adminPass);

            if (!system.adminLogin(adminPass))
            {
                cout << "Invalid admin passcode." << endl;
                continue;
            }

            adminLoggedIn = true;
            cout << "Admin login successful." << endl;

            while (adminLoggedIn)
            {
                int adminChoice;
                ConsoleHelper::ClearScreen();
                ConsoleHelper::SetColor(11);
                ConsoleHelper::PrintHeader("-------ADMIN PANEL-------");
                ConsoleHelper::ResetColor();
                ConsoleHelper::PrintDivider();
                cout << "\n--- Admin Panel ---\n1. Manage User\n2. view all Products\n3.Add Product\n4. Remove Product\n.5 Update Product\n6. Search Product\n7. logout\n ";
                cout<<"Enter Choice: ";
                cin >> adminChoice;
                
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Try again." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (adminChoice == 1)
                {
                    vector<USER_ACCOUNT> users = system.getAllUsers();
                    if (users.empty())
                    {
                        cout << "No users registered." << endl;
                        continue;
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
              cout<<"Enter username to delete or 0 to go back: ";
                    getline(cin, usernameToDelete);

                    if(usernameToDelete=="0")
                    {
                        continue;
                    }
                if (system.deleteUser(usernameToDelete))
                    {
                        cout << "User deleted successfully." << endl;
                    }
                    else
                    {
                        cout << "User not found or failed to update CSV." << endl;
                    }
                }
                else if (adminChoice == 2)
                {
                    cout<<"All products:";
                    system.getAllProducts();
                }
                else if(adminChoice==3)
                {
                    std:: string category, name;
                    double price;
                    int qty;
                    cout<<"Enter the details: ";
                    cout<< "Category: \n Name: \n Price: \n Quantity: \n"<<endl;
                    cin>>category>>name>>price>>qty;
                    PRODUCT product(category, name,price, qty);
                    system.addProduct(product);
                    system.saveToFile();
                }
                else if(adminChoice==4)
                {
                    system.removeProduct();
                    system.saveToFile();
                }
                else if(adminChoice==5)
                {
                    system.updateProduct();
                    system.saveToFile();
                }
                else if(adminChoice==6)
                {
                    string name;
                    cout << "Enter product name: ";
                    getline(cin, name);
                    system.searchByName(name);   
                }
                else if(adminChoice==7)
                {
                    system.logoutCurrentUser();
                    adminLoggedIn=false;
                }
                else 
                {
                    cout<<"Invalid choice";
                }
            }
        }
        else if (choice == 5)
        {
            system.logoutCurrentUser();
            cout << "Exiting system..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }
    }
 
    return 0;
}
