#pragma once
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include<string>
#include"USER_ACCOUNT.h"
class SELLER: public USER
{
    public:
    SELLER(USER_ACCOUNT sDetails);
    bool  authenticate(AUTHORITY_SERVICE& auth);
    std:: string getUsername() const;
    void  performAction();
    void SellerMenu();
    void viewProduct(std:: string);
    void searchProduct(std::string);
    void addProduct(PRODUCT product);
    void addPrice(std::string productName, float productPrice);
    void addQuantity(std::string productName, int qty);
};