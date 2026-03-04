#include<iostream>
using namespace std;
#include"ADMIN.h"
#include"USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<string>
ADMIN:: ADMIN(const std:: string& pass): USER()
{
this -> passcode= pass;
}
bool ADMIN:: authenticate(AUTHORITY_SERVICE& auth) 
{
    return auth.verifyAdmin(passcode);
}
void ADMIN:: performAction() 
{
    cout<<"Admin entering system"<<endl;
}
std::string ADMIN::getUsername() const {
    return username;
}
void ADMIN:: viewProduct(){}
void  ADMIN:: searchProduct(std:: string){}
void ADMIN :: manageProduct(std:: string){}
void ADMIN :: deleteProduct(std:: string productName){}
void ADMIN:: updateProduct(PRODUCT product){}
void ADMIN:: manageSalesReport(){}