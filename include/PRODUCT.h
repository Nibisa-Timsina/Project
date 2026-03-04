#pragma once
#include<string>
class PRODUCT
{
    public:
    std::string prodctName;
    double price;
    int quantity;
    std::string category;

    private:
    std::string getProduct();
    double getPrice();
    void setPrice(double price);
    int getQuantity();
    void updateQuantity(int qty);
    void displayInfo();
};