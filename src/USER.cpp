#include<iostream>
using namespace std;
#include "USER.h"
#include"USER_ACCOUNT.h"
#include"AUTHORITY_SERVICE.h"
#include"SYSTEM.h"
USER::USER()
{
    full_name = " ";
    username = " ";
    password = " ";
    age = 0;
    // user_acc will be initialized by subclasses
}
USER_ACCOUNT USER::getAccount() const {
    return user_acc;
}

Authority USER::getAuthority() const {
    return user_acc.getAuthority();
}
void USER:: addToCart(){

}
void USER:: checkout(){}