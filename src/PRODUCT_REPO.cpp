#include"../include/ConsoleHelper.h"
#include"PRODUCT_REPO.h"
#include<iostream>
#include"PRODUCT.h"
#include<iomanip>
#include<set>
#include<queue>
#include<sstream>
#include<fstream>
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
std:: set<string> PRODUCT_REPO::getCategoryInfo()
{
    set<string> category;

        for(int i=0; i<all_products.size(); i++)
        {
             category.insert(all_products[i].getCategory());
        }
       return category;
}
void PRODUCT_REPO:: showCategory()
    {
        set<string> Info= getCategoryInfo();
       for(auto it: Info)
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
               cout<<i+1<<". ";
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
    cout<<"Available Category!!"<<endl;
   showCategory();
    string choice;
    cout<<"Select the Category: ";
    cin>>choice;
   set<string> verify= getCategoryInfo();
   if(verify.count(choice)==0)
   {
        cout<<"Category not found!!";
        return;
   }
   showProductsByCategory(choice);
    int index;
    cout<<"Index No. ";
    cin>>index;
    if(index<=0 || index>all_products.size())
    {
        cout<<"Invalid choice";
    }
    else{
        all_products.erase(all_products.begin() + index-1);
        cout<<"Removed successfully";
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
    bool found = false;
    for(int i=0; i<all_products.size(); i++)
    {
        if(name==all_products[i].getName())
        {
            all_products[i].displayInfo();
            found = true;
        }
    }
    if(!found)
    {
        cout << "Product not found!" << endl;
    }
}
void PRODUCT_REPO:: getAllProducts(bool showCount)
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("------TOTAL PRODUCTS------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    rebuildSorting();
    int total_count = all_products.size();
    auto temp = sorted_price;
    while(!temp.empty())
    {
        temp.top().displayInfo();
        temp.pop();
    }
    if (showCount==true)
    {
    cout<<"Available Products In System: "<<total_count<<endl;
    }
   
}
    void PRODUCT_REPO:: saveToFile()
    {
        std::ofstream my_file("my_file.csv");
        if(!my_file)
        {
            cout<<"file not created";
        }
        for(int i=0; i<all_products.size(); i++)
        {
            my_file<<all_products[i].getCategory()<<","<<all_products[i].getName()<<","<<all_products[i].getPrice()<<","<<all_products[i].getQuantity()<<endl;
        }
        

    }
    void PRODUCT_REPO:: loadFromFile()
    {
        ifstream my_file("my_file.csv", ios::in);
        if(!my_file)
        {
            cout<<"file doesn't exist";

        }
        string line;
        while(getline(my_file, line))
        {
            std::stringstream ss(line);
            std:: string category, name;
            double price;
            int qty;
            getline(ss, category, ',');
            getline(ss,name,',');
            ss>>price;
            ss.ignore();
            ss>>qty;
            ss.ignore();
            PRODUCT p(category,name, price, qty);
            all_products.push_back(p);
            sorted_price.push(p);
            
        }
    }
    PRODUCT_REPO::PRODUCT_REPO()
    {
        loadFromFile();
    }