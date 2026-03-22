#include"../include/ConsoleHelper.h"
#include"PRODUCT_REPO.h"
#include<iostream>
#include"PRODUCT.h"
#include<iomanip>
#include<set>
#include<queue>
using namespace std;

void PRODUCT_REPO:: addProduct(PRODUCT product)
{
    all_products.push_back(product);
    sorted_price.push(product);
}
void PRODUCT_REPO::rebuildSorting()
{
    while(!sorted_price.empty()) 
    {
        sorted_price.pop();
    }
        for(int i=0; i<all_products.size(); i++)
        {
            sorted_price.push(all_products[i]);
        }
}
void PRODUCT_REPO:: showCategory()
    {
        set<string> category;

        for(int i=0; i<all_products.size(); i++)
        {
             category.insert(all_products[i].getCategory());
        }
        for(auto it:category)
        {
            cout<<it<<endl;
        }
    }
    void PRODUCT_REPO::showProductsByCategory(string category)
    {
        for(int i=0; i<all_products.size(); i++)
        {
            if(category==all_products[i].getCategory())
            {
                all_products[i].displayInfo();
            }
        }
    }

void PRODUCT_REPO:: removeProduct()
{
    if(all_products.empty())
    {
        cout<<"No product found, can't delete!!!";
        return;
    }
    cout<<"Available Products!!"<<endl;
   showCategory();
    string choice;
    cout<<"Select the Category: ";
    cin>>choice;
   showProductsByCategory(choice);
    int index;
    cout<<"Index No. ";
    cin>>index;
    if(index<0 || index>all_products.size())
    {
        cout<<"Invalid choice";
    }
    else{
        all_products.erase(all_products.begin() + index-1);
        cout<<"Removed successfully";
    rebuildSorting();
    }

}
void PRODUCT_REPO:: updateProduct()
{
    if(all_products.empty())
    {
        cout<<"No product found."<<endl;
        cout<<"Can't Update."<<endl;
        return;
    }
    cout<<"Available Products";
    showCategory();
    string choice;
    cout<<"Select the Category: ";
    cin>>choice;
    showProductsByCategory(choice);
    int index;
    cout<<"Index No. ";
    cin>>index;
    if(index<0|| index> all_products.size())
    {
        cout<<"Invalid choice";
    }
    else{
        cout<<"What do you want to Update: "<<endl;
        while(1)
        {
        cout<<"1. Name"<<endl;
        cout<<"2. Price"<<endl;
        cout<<"3. Qty"<<endl;
        int option;
        cout<<"Select: ";
        cin>>option;
        if(option==1)
        {
            string name;
            cout<<"New Name: ";
            cin>>name;
            all_products[index-1].setName(name);
            break;
        }
        else if(option==2)
        {
            double price;
            cout<<"New Price: ";
            cin>>price;
            all_products[index-1].setPrice(price);
            break;        
        }
        else if(option==3)
        {
            int qty;
            cout<<"New Qty: ";
            cin>>qty;
            all_products[index-1].setQuantity(qty);
            break;
        }
        else{
            cout<<"You alright?";
            cout<<"Select again.";
        }
        }
        rebuildSorting();
        
    }
}
void PRODUCT_REPO:: searchByName(string name)
{
    for(int i=0; i<all_products.size(); i++)
    {
        if(name==all_products[i].getName())
        {
            all_products[i].displayInfo();
        }
    }
}
void PRODUCT_REPO:: getAllProducts()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("------TOTAL PRODUCTS------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    int total_count = all_products.size();
    auto temp = sorted_price;
    while(!temp.empty())
    {
        temp.top().displayInfo();
        temp.pop();
    }
    cout<<"Available Products In System: "<<total_count<<endl;
}
    