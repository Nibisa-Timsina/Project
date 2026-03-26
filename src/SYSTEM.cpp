#include"SYSTEM.h"
#include"USER.h"
#include<iostream>
#include"USER_ACCOUNT.h"
using namespace std;
SYSTEM::SYSTEM()
    : current_user(nullptr), repo(), isAdminLogggedin(false){}

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
    isAdminLogggedin = false;
    return current_user;
}

bool SYSTEM::adminLogin(const std::string& passcode)
{
    isAdminLogggedin= auth.verifyAdmin(passcode);
    return isAdminLogggedin;
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
    if(isAdminLogggedin==true)
    {
        isAdminLogggedin= false;
        cout<<"Admin logout"<<endl;
        return;
    }
    if (!current_user) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    std::string uname = current_user->getUsername();
    delete current_user;
    current_user = nullptr;
    cout << "Session ended for " << uname << endl;
}
    void SYSTEM:: addProduct(PRODUCT product){
        if(isAdminLogggedin){
            repo.addProduct(product);
            return;
        }
        if(current_user==nullptr){
            cout<<"No user Logged in"<<endl;
            return;
        }
        if(current_user->getAuthority()!=ClientSELLER)
        {
            cout<<"Access not granted!!"<<endl;
            return;
        }
        repo.addProduct(product);
    }
    void SYSTEM::removeProduct(){
        if(!isAdminLogggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }

        repo.removeProduct();
    }
    void SYSTEM:: updateProduct(){
        if(!isAdminLogggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }
        repo.updateProduct();
    }
    void SYSTEM:: searchByName(string name){
        
        repo.searchByName(name);
        


    }

    void SYSTEM:: getAllProducts(){
        if(isAdminLogggedin){
            repo.getAllProducts(true);
            return;
        }
        if(current_user==nullptr){
            cout<<"No user Logged in"<<endl;
            return;
        }
        repo.getAllProducts(false);
    }
    void SYSTEM:: saveToFile()
    {
        repo.saveToFile();
    }