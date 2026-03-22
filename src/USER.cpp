#include<iostream>
using namespace std;
#include "USER.h"
#include"USER_ACCOUNT.h"
#include"AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include"SYSTEM.h"
USER::USER()
{
    full_name = " ";
    username = " ";
    password = " ";
    age = 0;
}
USER_ACCOUNT USER::getAccount() const {
    return user_acc;
}

Authority USER::getAuthority() const {
    return user_acc.getAuthority();
}
void USER:: addToCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("------CONFIRMED ITEMS-----");
    ConsoleHelper::ResetColor();
    //logic
    //Cart.addToCart();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-----ITEMS ADDED SUCESSFULLY-----");
    ConsoleHelper::ResetColor();
}
void USER:: checkout(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-----CHECKOUT-----");
    ConsoleHelper::ResetColor();
    //logic
}