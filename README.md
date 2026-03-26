# Sales & Inventory Management System

## Project Overview

A comprehensive **Sales & Inventory Management System** built in C++ that implements a multi-user platform with role-based access control. The system facilitates interactions between:

- **Buyers**: Can browse products, manage shopping carts, place orders, and view purchase history
- **Sellers**: Can list products, manage inventory, set pricing, and track sales
- **Admins**: Can manage users, products, and generate sales reports

---

## Architecture Overview

### Core Components

#### 1. **User Management**
- **USER** (Abstract Base Class)
  - Base class for all user types
  - Defines common interface for authentication and user operations
  - Stores USER_ACCOUNT for centralized user data

- **USER_ACCOUNT**
  - Data holder for all user information
  - Manages user credentials, contact details, and authority levels
  - Authority types: ClientBUYER, ClientSELLER, Admin

- **BUYER, SELLER, ADMIN** (Concrete Implementations)
  - Specialized user types inheriting from USER
  - Each implements role-specific functionality
  - Inherits authentication and account management from USER

#### 2. **System Management**
- **SYSTEM**
  - Central orchestrator for the entire application
  - Manages user registration, login, and session controls
  - Handles access control and authorization
  - Coordinates with AUTHORITY_SERVICE for authentication

#### 3. **Product Management**
- **PRODUCT**: Represents individual products
- **PRODUCT_REPO**: Repository pattern for product operations
- **PRODUCT_SERVICE**: Business logic for product operations

#### 4. **Transaction Management**
- **BILL**: Represents purchase transactions
- **BILL_SERVICE**: Business logic for bill operations
- **CART**: Shopping cart functionality for buyers

#### 5. **Security**
- **AUTHORITY_SERVICE**: Handles user authentication and authorization

---

## File Structure

```
├── include/                    # Header files
│   ├── USER.h                 # Abstract user base class
│   ├── USER_ACCOUNT.h         # User account data class
│   ├── BUYER.h                # Buyer implementation
│   ├── SELLER.h               # Seller implementation
│   ├── ADMIN.h                # Admin implementation
│   ├── SYSTEM.h               # Main system orchestrator
│   ├── PRODUCT.h              # Product class
│   ├── PRODUCT_REPO.h         # Product repository
│   ├── PRODUCT_SERVICE.h      # Product service logic
│   ├── BILL.h                 # Bill/Invoice class
│   ├── BILL_SERVICE.h         # Bill service logic
│   ├── CART.h                 # Shopping cart
│   ├── AUTHORITY_SERVICE.h    # Authentication service
│   └── README.md              # Architecture documentation
├── src/                        # Implementation files
│   ├── USER.cpp
│   ├── USER_ACCOUNT.cpp
│   ├── BUYER.cpp
│   ├── SELLER.cpp
│   ├── ADMIN.cpp
│   ├── SYSTEM.cpp
│   ├── PRODUCT.cpp
│   ├── PRODUCT_REPO.cpp
│   ├── PRODUCT_SERVICE.cpp
│   ├── BILL.cpp
│   ├── BILL_SERVICE.cpp
│   ├── CART.cpp
│   ├── AUTHORITY_SERVICE.cpp
│   └── main.cpp
├── my_file.csv                # Data storage
├── users.csv                  # User data
└── README.md                  # This file
```

---

## Key Classes & Responsibilities

### USER (Abstract Base Class)
```cpp
class USER {
   protected:
   USER_ACCOUNT user_acc;  // Single source of truth for user data
   CART* cart;
   
   virtual bool authenticate(AUTHORITY_SERVICE& auth) = 0;
   virtual void performAction() = 0;
   virtual std::string getUsername() const = 0;
};
```

**Key Methods:**
- `authenticate()`: Verify user credentials
- `performAction()`: Define role-specific actions
- `getUsername()`: Retrieve username
- `getAccount()`: Get USER_ACCOUNT data
- `getAuthority()`: Get authority level

### USER_ACCOUNT (Data Container)
Stores all user information with getters:
- Basic Info: full_name, username, password, age
- Contact: contact_num, location, mail_address
- Authority: role level (ClientBUYER, ClientSELLER, Admin)

### BUYER (Concrete Implementation)
**Main Responsibilities:**
- Browse and search products
- Manage shopping cart
- Place orders
- View purchase history
- Request bills

### SELLER (Concrete Implementation)
**Main Responsibilities:**
- Add and manage products
- Set product prices and quantities
- View sales
- Manage inventory

### ADMIN (Concrete Implementation)
**Main Responsibilities:**
- Delete users
- Update products
- Manage sales reports
- View all users

### SYSTEM (Orchestrator)
**Main Responsibilities:**
- User registration and login
- Current user session management
- Product operations with access control
- Data persistence

---

## Recent Refactoring (March 2026)

### Overview
Comprehensive code cleanup to eliminate redundancies, improve maintainability, and follow object-oriented design principles. Removed ~30 lines of duplicate code and empty implementations.

### 1. USER Class Refactoring

**Problem:** Duplicate attributes in both USER and USER_ACCOUNT classes
```cpp
// BEFORE - Redundant attributes
class USER {
    protected:
    USER_ACCOUNT user_acc;
    std::string full_name, username, password;  // ❌ REDUNDANT
    int age;                                     // ❌ REDUNDANT
    
    virtual void addToCart();    // ❌ Empty placeholder
    virtual void checkout();     // ❌ Empty placeholder
};
```

**Solution:** Remove duplicate attributes, rely on USER_ACCOUNT for all user data
```cpp
// AFTER - Clean, no duplication
class USER {
    protected:
    USER_ACCOUNT user_acc;  // ✅ Single source of truth
    CART* cart;
    
    // Virtual methods only for real functionality
    virtual bool authenticate(AUTHORITY_SERVICE& auth) = 0;
    virtual void performAction() = 0;
    virtual std::string getUsername() const = 0;
};
```

### 2. USER_ACCOUNT Bug Fix

**Problem:** Initialization to non-existent enum value
```cpp
// BEFORE - Bug
USER_ACCOUNT::USER_ACCOUNT() {
    authority = Guest;  // ❌ Guest doesn't exist in enum!
}
```

**Solution:** Fix to valid enum value
```cpp
// AFTER - Fixed
USER_ACCOUNT::USER_ACCOUNT() {
    authority = ClientBUYER;  // ✅ Proper default value
}
```

### 3. BUYER Class Refactoring

**Problem:** Redundant data copying in constructor
```cpp
// BEFORE - Unnecessary copying
BUYER::BUYER(USER_ACCOUNT Bdetails) {
    user_acc = Bdetails;
    full_name = Bdetails.getFullname();      // ❌ Redundant
    username = Bdetails.getUsername();       // ❌ Redundant
    password = Bdetails.getPassword();       // ❌ Redundant
}
```

**Solution:** Store only USER_ACCOUNT, access data through it
```cpp
// AFTER - Clean constructor
BUYER::BUYER(USER_ACCOUNT Bdetails) {
    user_acc = Bdetails;  // ✅ Single storage point
}
```

**Removed Methods:** `addToCart()`, `checkout()` (empty placeholders, not part of BUYER logic)

**Final Methods:**
- ✅ authenticate()
- ✅ performAction()
- ✅ getUsername()
- ✅ viewProduct()
- ✅ searchProduct()
- ✅ myProducts()
- ✅ placeOrder()
- ✅ viewCart()
- ✅ editCart()
- ✅ requestBill()

### 4. SELLER Class Refactoring

**Problem:** Same redundant data copying as BUYER
```cpp
// BEFORE
SELLER::SELLER(USER_ACCOUNT sDetails) {
    user_acc = sDetails;
    full_name = sDetails.getFullname();      // ❌ Redundant
    username = sDetails.getUsername();       // ❌ Redundant
    password = sDetails.getPassword();       // ❌ Redundant
}
```

**Solution:** Simplified constructor
```cpp
// AFTER
SELLER::SELLER(USER_ACCOUNT sDetails) {
    user_acc = sDetails;  // ✅ Clean
}
```

**Final Methods:**
- ✅ authenticate()
- ✅ performAction()
- ✅ getUsername()
- ✅ viewProduct()
- ✅ searchProduct()
- ✅ addProduct()
- ✅ addPrice()
- ✅ addQuantity()

### 5. ADMIN Class Refactoring

**Problem:** Unused/empty methods in API
```cpp
// BEFORE - Unused methods
class ADMIN : public USER {
    void viewProduct();                    // ❌ Not used
    void searchProduct(std::string);       // ❌ Not used
    void manageProduct(std::string);       // ❌ Vague/unused
    void generateSalesReport();            // ❌ Duplicate of manageSalesReport()
};
```

**Solution:** Remove unused methods, keep only relevant functionality
```cpp
// AFTER - Clean API
class ADMIN : public USER {
    void deleteProduct(std::string productName);  // ✅ Clear purpose
    void updateProduct(PRODUCT product);          // ✅ Necessary
    void manageSalesReport();                     // ✅ Implemented
    void viewAllUsers();                          // ✅ Needed
};
```

### Benefits of Refactoring

| Benefit | Result |
|---------|--------|
| **Data Consistency** | Single source of truth for user data |
| **Maintainability** | No duplicate logic to maintain |
| **Bug Prevention** | Fixed enum initialization bug |
| **Code Clarity** | Removed misleading empty methods |
| **Performance** | Reduced memory footprint |
| **OOP Principles** | Better inheritance design |

### Files Modified

- `USER.h` & `USER.cpp`: Removed duplicate attributes and empty methods
- `USER_ACCOUNT.h` & `USER_ACCOUNT.cpp`: Fixed enum bug
- `BUYER.h` & `BUYER.cpp`: Simplified constructor and removed empty methods
- `SELLER.h` & `SELLER.cpp`: Simplified constructor
- `ADMIN.h` & `ADMIN.cpp`: Removed unused methods
- `SYSTEM.h` & `SYSTEM.cpp`: No changes needed (already well-designed)

---

## Usage Example

```cpp
// System initialization
SYSTEM system;

// Register a new buyer
USER_ACCOUNT buyer_account(
    "John Doe",           // full_name
    "john_doe",           // username
    "password123",        // password
    "555-1234",          // contact_num
    25,                   // age
    "New York",          // location
    "john@email.com",    // mail_address
    ClientBUYER          // authority
);

system.registerAccount(buyer_account);

// Login
USER* current_user = system.loginAccount("john_doe", "password123");

// Buyer operations
BUYER* buyer = dynamic_cast<BUYER*>(current_user);
if (buyer) {
    buyer->searchProduct("laptop");
    buyer->addToCart();
    buyer->placeOrder();
}

// Logout
system.logoutCurrentUser();
```

---

## Design Patterns Used

1. **Inheritance**: USER as abstract base class
2. **Polymorphism**: Role-specific implementations
3. **Repository Pattern**: PRODUCT_REPO for data access
4. **Service Pattern**: PRODUCT_SERVICE, BILL_SERVICE for business logic
5. **Single Responsibility**: Each class has a clear, focused role
6. **DRY Principle**: Eliminated code duplication

---

## Security Features

- **Authentication**: AUTHORITY_SERVICE validates credentials
- **Authorization**: Role-based access control (ClientBUYER, ClientSELLER, Admin)
- **Session Management**: Current user tracking in SYSTEM
- **Access Control**: Operations check user authority before execution

---

## Future Improvements

- [ ] Implement database persistence instead of CSV files
- [ ] Add payment processing integration
- [ ] Implement order tracking and notifications
- [ ] Add product reviews and ratings
- [ ] Enhance admin analytics dashboard
- [ ] Implement caching for frequently accessed products
- [ ] Add unit and integration tests

---

## Building & Running

```bash
# Compile
gcc src/*.cpp include/*.h -o program

# Run
./program
```

---

## Dependencies

- Standard C++ Library (iostream, string, vector)
- No external dependencies

---

## Notes

- All user data is stored in `users.csv` and `my_file.csv`
- Product data is managed through PRODUCT_REPO
- System uses CSV-based persistence

---

**Last Updated:** March 22, 2026  
**Version:** 2.0 (Post-Refactoring)