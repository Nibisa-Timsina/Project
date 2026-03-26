#include<iostream>
using namespace std;
#include "USER.h"
#include"USER_ACCOUNT.h"
#include"AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include"SYSTEM.h"
USER::USER()
{
}

USER_ACCOUNT USER::getAccount() const {
    return user_acc;
}

Authority USER::getAuthority() const {
    return user_acc.getAuthority();
}