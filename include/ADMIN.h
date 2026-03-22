#pragma once
#include"USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<string>
class ADMIN: public USER
{
    private:
    std:: string passcode;
    public:
    ADMIN(const std:: string & pass );
    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    void AdminMenu();
    std:: string getUsername() const;
    void viewProduct();
    void searchProduct(std::string);
    void manageProduct(std:: string);
    void deleteProduct(std:: string productName);
    void updateProduct(PRODUCT product);
    void manageSalesReport();
    void viewAllUsers();
    void generateSalesReport();
};
