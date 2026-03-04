#include"SYSTEM.h"
#include"USER.h"
#include"SELLER.h"
#include"BUYER.h"
#include<iostream>
#include"USER_ACCOUNT.h"
using namespace std;
SYSTEM::SYSTEM()
    : current_user(nullptr){}

 USER* SYSTEM:: process(bool isLogin, USER_ACCOUNT account)
{
   if(!isLogin)
   {
         auth.registerUser(account);
         return nullptr;
   }
   else
   {
         current_user= auth.login(account.getUsername(), account.getPassword());
        return current_user; 
   }
}


void SYSTEM::logoutCurrentUser()
{
    if (!current_user) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    std::string uname = current_user->getUsername();
    current_user = nullptr;
    cout << "Session ended for " << uname << endl;
}
