#pragma once
#include<string>
#include"../include/USER_ACCOUNT.h"
#include<vector>

#include"USER.h"

class AUTHORITY_SERVICE
{
    private:
    std::string admin_pass = "admin1234";
    std::vector<USER_ACCOUNT> registered_user;
    public:
    bool registerUser(USER_ACCOUNT account);
    bool verifyClient(const std::string& username, const std::string& password);
    USER* login(std::string username, std::string password);
    bool verifyAdmin(std::string passcode);
};