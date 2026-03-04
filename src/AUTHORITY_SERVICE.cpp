#include "AUTHORITY_SERVICE.h"
#include<iostream>
using namespace std;
#include"USER_ACCOUNT.h"
#include<vector>
#include"BUYER.h"
#include"SELLER.h"
#include"ADMIN.h"
bool AUTHORITY_SERVICE::registerUser(USER_ACCOUNT account) 
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == account.getUsername())
        {
            return false;
        }
    }
    registered_user.push_back(account);
    return true;
}

USER* AUTHORITY_SERVICE::login(std::string username, std::string password)
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getAuthority() == ClientBUYER || registered_user[i].getAuthority() == ClientSELLER)
        {
            if (registered_user[i].getUsername() == username)
            {
                if (registered_user[i].getPassword() == password)
                {
                    cout << "Login Successful >-<" << endl;
                    if (registered_user[i].getAuthority() == ClientBUYER)
                    {
                        
                        return new BUYER(registered_user[i]);
                    }
                    else if (registered_user[i].getAuthority() == ClientSELLER)
                        return new SELLER(registered_user[i]);
                }
                else
                {
                    cout << "Password incorrect T-T" << endl;
                }
            }
            else
            {
                cout << "Username Incorrect T-T" << endl;
            }
        }
    }
    return nullptr;
}

bool AUTHORITY_SERVICE::verifyClient(const std::string& username, const std::string& password)
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == username)
        {
            if (password.empty() || registered_user[i].getPassword() == password)
            {
                return true;
            }
            else
            {
                return false; 
            }
        }
    }
    return false; 
}

bool AUTHORITY_SERVICE::verifyAdmin(std::string passcode)
{
        if (passcode == admin_pass)
            {
                return true;
            }
            else
            {
                return false;
            }

}

