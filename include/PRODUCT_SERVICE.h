#pragma once
#include<string>
#include"../include/PRODUCT_REPO.h"
class PRODDUCT_SERVICE
{
    private: 
    PRODUCT_REPO* repository;
    public:
    void displayProducts();
    void searchProducts(std::string);

};