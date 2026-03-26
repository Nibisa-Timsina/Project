#pragma once
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include<string>
#include"USER_ACCOUNT.h"
class BUYER: public USER
{
    public:
    BUYER(USER_ACCOUNT Bdetails);

    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std:: string getUsername() const;
    void BuyerMenu();
    void viewProduct(std:: string);
    void searchProduct(std:: string);
    void myProducts();
    void placeOrder();
    void viewCart();
    void editCart();
    void requestBill();

};