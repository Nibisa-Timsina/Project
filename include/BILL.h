#pragma once
#include<string>
#include"../include/PRODUCT.h"
class BILL
{
    private:
    int billId;
    int customerId;
    PRODUCT* items;
    int item_count;
    float total_amount;
    std:: string date;
    std:: string payment_status;
    public:
    BILL();
    ~BILL();
    void generateBill();
    void displayBill();
};