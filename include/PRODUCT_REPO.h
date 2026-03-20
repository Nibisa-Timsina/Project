#pragma once
#include <string>
#include <vector>
#include <queue>
#include "PRODUCT.h"
using namespace std;
class PRODUCT_REPO
{
    private:
    vector<PRODUCT> all_products;
    priority_queue<PRODUCT, vector<PRODUCT>, greater<PRODUCT>> sorted_price;
    void rebuildSorting();
    void showCategory();
    void showProductsByCategory(string category);
    public:
        void addProduct(PRODUCT product);
        void removeProduct();
        void updateProduct();
        void searchByName(string name);
        void getAllProducts();
};