#include"SELLER.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<string>
#include<iostream>
#include"USER_ACCOUNT.h"
using namespace std;
SELLER:: SELLER(USER_ACCOUNT sDetails){
    user_acc = sDetails;
    full_name = sDetails.getFullname();
    username = sDetails.getUsername();
    password = sDetails.getPassword();
}
 std:: string SELLER:: getUsername() const{return username;}
bool SELLER:: authenticate(AUTHORITY_SERVICE& auth) {
 return auth.verifyClient(username, "");   
}
void SELLER:: performAction(){
    cout<<"Seller interacting"<<endl;
}
void SELLER:: viewProduct(std:: string){}
void SELLER:: searchProduct(std:: string){}
void SELLER:: addProduct(PRODUCT product){}
void SELLER:: addPrice(std:: string productName, float productPrice){}
void SELLER:: addQuantity(std:: string productName, int qty){}