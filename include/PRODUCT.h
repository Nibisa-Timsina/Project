#pragma once
#include<string>
#include"PRODUCT_REPO.h"
class PRODUCT
{
    private:
    std::string product_name;
    double product_price;
    int product_qty;
    std::string product_category;
  

public:
    PRODUCT();
    PRODUCT(string product_category, std:: string product_name, double product_price,int product_qty );
    void setName(string name);
    std:: string getName();
    void setPrice(double price);
    double getPrice();
    void setQuantity(int qty);
    int getQuantity();
    string getCategory();
    void displayInfo() const;
    void updateQuantity(int qty);
    bool operator<(const PRODUCT &other) const;
};