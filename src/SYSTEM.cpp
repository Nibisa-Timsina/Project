#include"SYSTEM.h"
#include"USER.h"
#include"SELLER.h"
#include"BUYER.h"
#include<iostream>
#include"USER_ACCOUNT.h"
using namespace std;
SYSTEM::SYSTEM()
    : current_user(nullptr){}

bool SYSTEM::registerAccount(const USER_ACCOUNT& account)
{
    return auth.registerUser(account);
}

USER* SYSTEM::loginAccount(const std::string& username, const std::string& password)
{
    if (current_user)
    {
        delete current_user;
        current_user = nullptr;
    }

    current_user = auth.login(username, password);
    return current_user;
}

bool SYSTEM::adminLogin(const std::string& passcode)
{
    return auth.verifyAdmin(passcode);
}

std::vector<USER_ACCOUNT> SYSTEM::getAllUsers() const
{
    return auth.getAllRegisteredUsers();
}

bool SYSTEM::deleteUser(const std::string& username)
{
    return auth.deleteUserByUsername(username);
}

 USER* SYSTEM:: process(bool isLogin, USER_ACCOUNT account)
{
   if(!isLogin)
   {
         registerAccount(account);
         return nullptr;
   }
   else
   {
         return loginAccount(account.getUsername(), account.getPassword()); 
   }
}


void SYSTEM::logoutCurrentUser()
{
    if (!current_user) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    std::string uname = current_user->getUsername();
    delete current_user;
    current_user = nullptr;
    cout << "Session ended for " << uname << endl;
}
