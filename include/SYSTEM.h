#pragma once
#include<string>
#include<vector>
#include"USER.h"
#include"AUTHORITY_SERVICE.h"
#include"USER_ACCOUNT.h"
class SYSTEM
{
    private:
    USER* current_user;
    AUTHORITY_SERVICE auth;
    public:
    SYSTEM();
    bool registerAccount(const USER_ACCOUNT& account);
    USER* loginAccount(const std::string& username, const std::string& password);
    bool adminLogin(const std::string& passcode);
    std::vector<USER_ACCOUNT> getAllUsers() const;
    bool deleteUser(const std::string& username);
    USER* process(bool isLogin, USER_ACCOUNT account); 
    void logoutCurrentUser();
};

