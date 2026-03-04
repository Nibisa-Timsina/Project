#pragma once
#include<string>
#include"AUTHORITY_SERVICE.h"
#include"../include/USER.h"
class GUEST: public USER
{
    private:
    std:: string  location,  mail_address;
   
    public:
    GUEST();
    ~GUEST();
    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();

    std::string getUsername() const override { return username; }
    void viewProducts();
    void searchProducts(std:: string);
    void registerToSystem();

};