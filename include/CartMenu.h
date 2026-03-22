#pragma once
#include"CART.h"
#include"BILL.h"
class CartMenu {
    private:
        CART Cart;
        BILL Bill;
    public:
        void showCart();
        void editCartItems();
        void proceedToCheckout();
        void requestBillView();
        void confirmPurchase();
        void viewCartItems();
};