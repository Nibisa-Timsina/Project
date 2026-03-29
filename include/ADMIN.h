#pragma once
#include"USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"PRODUCT_REPO.h"
#include<string>
#include<vector>
class ADMIN: public USER
{
    private:
    std:: string passcode;
    PRODUCT_REPO* repo;
    AUTHORITY_SERVICE* auth_service;
    
    void AdminMenu();
    void handleUserManagement();
    void handleProductOperations();
    
    public:
    ADMIN(const std:: string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc);
    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std:: string getUsername() const;
    void deleteProduct(std:: string productName);
    void updateProduct(PRODUCT product);
    void manageSalesReport();
    void viewAllUsers();
    void generateSalesReport();
    void viewProduct(std::string productName) override;
    void searchProduct(std::string productName) override;
    void startSession();
};
