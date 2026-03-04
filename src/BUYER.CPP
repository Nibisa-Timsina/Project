#include"BUYER.h"
#include<iostream>
using namespace std;
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
BUYER:: BUYER(USER_ACCOUNT Bdetails){
    user_acc = Bdetails;
    full_name = Bdetails.getFullname();
    username = Bdetails.getUsername();
    password = Bdetails.getPassword();
}
bool BUYER:: authenticate(AUTHORITY_SERVICE& auth) {
     return auth.verifyClient(username, "");
}
void BUYER:: performAction() {
    cout<<"Buyer interacting"<<endl;
}
std:: string BUYER:: getUsername()const{
    return username;
}
void BUYER:: viewProduct(std:: string) {}
void BUYER:: searchProduct(std:: string){}
void BUYER:: addToCart(){}
void BUYER:: checkout(){}
void BUYER:: myProducts(){}
void BUYER:: placeOrder(){}
void BUYER:: viewCart(){}
void BUYER :: editCart(){}
void  BUYER:: requestBill(){}
