#pragma once
#include<string>
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
    USER* process(bool isLogin, USER_ACCOUNT account); 
    void logoutCurrentUser();
};

