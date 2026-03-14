#include"PRODUCT.h"
#include<iostream>
using namespace std;
PRODUCT:: PRODUCT()
{
    product_name =" ";
    product_price=0;
    product_qty=0;
    product_category= " ";
}
PRODUCT:: PRODUCT (string product_category, std:: string product_name, double product_price,int product_qty )
{
    this-> product_category= product_category;
    this-> product_name = product_name;
    this-> product_price= product_price;
    this-> product_qty= product_qty;
}
void PRODUCT:: setName( string name)
{
    this-> product_name= name;
}
std:: string PRODUCT:: getName(){ return product_name;}
void PRODUCT:: setPrice( double price)
{
    this-> product_price= price;
}
double PRODUCT:: getPrice(){ return product_price; }
void PRODUCT:: setQuantity( int qty)
{
    this-> product_qty= qty;
}
int PRODUCT:: getQuantity()
{
    return product_qty;
}
string PRODUCT:: getCategory()
{
    return product_category;
}

void PRODUCT:: updateQuantity(int qty)
{
    this-> product_qty= qty;
}
bool PRODUCT:: operator<( const PRODUCT& other) const
{
    return product_price<other. product_price;
}
void PRODUCT:: displayInfo()
{
    cout<<" Category: "<<product_category<<endl;
    cout<<" Name: "<<product_name<<endl;
    cout<<" Price: "<<product_price<<endl;
    cout<<" Quantity: "<<product_qty<<endl;
    cout<<" Category: "<<product_category<<endl;

}