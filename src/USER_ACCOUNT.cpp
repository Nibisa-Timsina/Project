#include "../include/USER_ACCOUNT.h"
#include<iostream>
#include "USER_ACCOUNT.h"
using namespace std;

USER_ACCOUNT::USER_ACCOUNT(){
    full_name=" ";
    username=" ";
    password=" ";
    contact_num=" ";
    age=0;
    location=" ";
    mail_address=" ";
    authority= Guest;
        
}
USER_ACCOUNT:: USER_ACCOUNT(std:: string full_name, std:: string username, std:: string password, std:: string contact_num, int age, std:: string location, std:: string  mail_address, Authority auth)
{
    this-> full_name= full_name;
    this-> username= username;
    this-> password= password;
    this-> contact_num = contact_num;
    this-> age= age;
    this-> location= location;
    this-> mail_address = mail_address;
    this-> authority= auth;

}

Authority USER_ACCOUNT::getAuthority() const
{
    return authority;   
}

void USER_ACCOUNT::setAuthority(Authority auth)
{
    authority = auth;   
}
string USER_ACCOUNT:: getFullname()
{
    return full_name;
}

string USER_ACCOUNT::getPassword()
{
    return password;
}

string USER_ACCOUNT::getUsername()
{
    return username;
}