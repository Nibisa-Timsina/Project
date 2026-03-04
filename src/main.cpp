#include <iostream>
#include "SYSTEM.h"
#include "AUTHORITY_SERVICE.h"
#include "USER_ACCOUNT.h"
#include "BUYER.h"
#include "SELLER.h"

using namespace std;

int main()
{
    cout << "=== Sales & Inventory Management System ===" << endl << endl;

    AUTHORITY_SERVICE auth_service;

    USER_ACCOUNT buyer_acc("Alice Johnson", "alice", "pass123a","984203342",19, "123 Main St", "alice@example.com", ClientBUYER);
    USER_ACCOUNT seller_acc("Bob Smith", "bob", "pass456","545285579", 54, "456 Oak Ave", "bob@example.com", ClientSELLER);    
    SYSTEM system;
    system.process(false, buyer_acc);
    system.process(true, seller_acc);

    return 0;
}
