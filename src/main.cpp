#include <iostream>
#include <limits>
#include "SYSTEM.h"
#include "USER_ACCOUNT.h"

using namespace std;

int main()
{
    cout<<endl;
    cout << "=== Sales & Inventory System ===" << endl << endl;
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
            cout << "Select role (1 = Buyer, 2 = Seller): ";
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
                cout << "\n--- Admin Panel ---\n1. View all users\n2. Delete user\n3. Logout admin\nEnter choice: ";
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
                }
                else if (adminChoice == 2)
                {
                    string usernameToDelete;
                    cout << "Enter username to delete: ";
                    getline(cin, usernameToDelete);

                    if (system.deleteUser(usernameToDelete))
                    {
                        cout << "User deleted successfully." << endl;
                    }
                    else
                    {
                        cout << "User not found or failed to update CSV." << endl;
                    }
                }
                else if (adminChoice == 3)
                {
                    adminLoggedIn = false;
                    cout << "Admin logged out." << endl;
                }
                else
                {
                    cout << "Invalid admin choice." << endl;
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
