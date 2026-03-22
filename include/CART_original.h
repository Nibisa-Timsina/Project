#pragma once
#include<string>
#include"../include/PRODUCT.h"
class CART
{
    private:
    PRODUCT* cart_items;
    double total_amount;
    public:
    void printMenu();
    void CartMenu();
    void addItem(PRODUCT product);
    void removeItem(std:: string product_name );
    void updateQuantity(std::string product_name, int qnt);
    void viewCart();
    double calculateTotal();
};

