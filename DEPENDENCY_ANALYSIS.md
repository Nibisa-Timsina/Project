# Class Dependencies and Interconnections Analysis

## 1. HEADER INCLUDES OVERVIEW

### SYSTEM.h
- Includes: `PRODUCT_REPO.h`, `USER.h`, `AUTHORITY_SERVICE.h`, `USER_ACCOUNT.h`, `<string>`, `<vector>`
- Creates/Owns: `PRODUCT_REPO repo` (member), `AUTHORITY_SERVICE auth` (member)
- Manages: `USER* current_user` (pointer, created/destroyed dynamically)

### USER.h (Base Class)
- Includes: `USER_ACCOUNT.h`, `CART.h`, `<string>`
- Forward declares: `AUTHORITY_SERVICE`
- Protected members: `USER_ACCOUNT user_acc`
- Private members: `CART* cart`
- **Pure virtual methods** (must be implemented by derived classes):
  - `bool authenticate(AUTHORITY_SERVICE& auth) = 0`
  - `void performAction() = 0`
  - `std::string getUsername() const = 0`
  - `void viewProduct(std::string) = 0`
  - `void searchProduct(std::string) = 0`

### BUYER.h
- Includes: `USER.h`, `BILL.h`, `PRODUCT.h`, `AUTHORITY_SERVICE.h`, `USER_ACCOUNT.h`, `PRODUCT_REPO.h`, `<string>`
- **Constructor parameter**: `BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository)`
- Member: `PRODUCT_REPO* repo` (pointer, NOT initialized by default!)
- Implements all 5 pure virtual methods from USER
- Additional methods: `myProducts()`, `placeOrder()`, `viewCart()`, `editCart()`, `requestBill()`, `startSession()`

### SELLER.h
- Includes: `USER.h`, `BILL.h`, `PRODUCT.h`, `AUTHORITY_SERVICE.h`, `USER_ACCOUNT.h`, `PRODUCT_REPO.h`, `<string>`
- **Constructor parameter**: `SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository)`
- Member: `PRODUCT_REPO* repo` (pointer, NOT initialized by default!)
- Implements all 5 pure virtual methods from USER
- Additional methods: `addProduct()`, `addPrice()`, `addQuantity()`, `startSession()`

### ADMIN.h
- Includes: `USER.h`, `PRODUCT.h`, `AUTHORITY_SERVICE.h`, `PRODUCT_REPO.h`, `<string>`, `<vector>`
- **Constructor parameter**: `ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc)`
- Members: `std::string passcode`, `PRODUCT_REPO* repo`, `AUTHORITY_SERVICE* auth_service`
- Implements all 5 pure virtual methods from USER
- Additional methods: `deleteProduct()`, `updateProduct()`, `manageSalesReport()`, `viewAllUsers()`, `generateSalesReport()`, `startSession()`

### AUTHORITY_SERVICE.h
- Includes: `USER_ACCOUNT.h`, `USER.h`, `<string>`, `<vector>`
- Members: `std::string admin_pass = "admin1234"`, `std::vector<USER_ACCOUNT> registered_user`
- Key methods:
  - `bool registerUser(USER_ACCOUNT account)`
  - `USER* login(std::string username, std::string password)` - **Creates BUYER/SELLER dynamically**
  - `bool verifyAdmin(std::string passcode)`
  - `bool verifyClient(const std::string& username, const std::string& password)`

### PRODUCT_REPO.h
- Includes: `PRODUCT.h`, `<string>`, `<vector>`, `<queue>`, `<set>`
- Members: `vector<PRODUCT> all_products`, `priority_queue<PRODUCT>` sorted_price
- Methods: `addProduct()`, `removeProduct()`, `updateProduct()`, `searchByName()`, `getAllProducts()`, `saveToFile()`, `loadFromFile()`

---

## 2. CONSTRUCTOR SIGNATURES & PARAMETER PASSING

### SYSTEM Constructor
```cpp
SYSTEM::SYSTEM()
    : current_user(nullptr), repo(), isAdminLogggedin(false)
```
- ✅ Initializes `repo` (PRODUCT_REPO) - will have default constructor
- ✅ Initializes `auth` (AUTHORITY_SERVICE as member var) - will have default constructor
- ✅ Both are available as members

### BUYER Constructor
```cpp
BUYER::BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository) {
    user_acc = Bdetails;
    repo = &repository;  // Stores reference as pointer
}
```
- ✅ Receives USER_ACCOUNT
- ✅ Receives PRODUCT_REPO reference
- ✅ Stores repo as pointer member

### SELLER Constructor
```cpp
SELLER::SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository) {
    user_acc = sDetails;
    repo = &repository;  // Stores reference as pointer
}
```
- ✅ Receives USER_ACCOUNT
- ✅ Receives PRODUCT_REPO reference
- ✅ Stores repo as pointer member

### ADMIN Constructor
```cpp
ADMIN::ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc) 
    : passcode(pass) {
    repo = &repository;
    auth_service = &auth_svc;  // Stores references as pointers
}
```
- ✅ Receives passcode string
- ✅ Receives PRODUCT_REPO reference
- ✅ Receives AUTHORITY_SERVICE reference
- ✅ Stores both as pointer members

---

## 3. METHOD PARAMETER ANALYSIS

### AUTHORITY_SERVICE::login() - CRITICAL ISSUE ❌
```cpp
USER* AUTHORITY_SERVICE::login(std::string username, std::string password) {
    // ...
    if (registered_user[i].getAuthority() == ClientBUYER) {
        return new BUYER(registered_user[i]);  // WRONG! Missing PRODUCT_REPO parameter
    }
    return new SELLER(registered_user[i]);     // WRONG! Missing PRODUCT_REPO parameter
}
```

**PROBLEM**: 
- BUYER and SELLER constructors require TWO parameters: `USER_ACCOUNT` and `PRODUCT_REPO&`
- The login() method is only passing ONE parameter: `USER_ACCOUNT`
- **This will cause compilation errors** - constructors expect 2 arguments but receive 1

**Current requirement**: Both BUYER and SELLER need reference to PRODUCT_REPO for:
- Accessing products in `viewProduct()`, `searchProduct()`
- Adding products in `addProduct()` (SELLER only)

### SYSTEM::handleUserLogin() 
```cpp
void SYSTEM::handleUserLogin() {
    USER* user = loginAccount(username, password);  // Returns user WITHOUT repo
    if (user->getAuthority() == ClientSELLER) {
        SELLER seller(user->getAccount(), repo);    // Creates NEW SELLER with repo
    } else if (user->getAuthority() == ClientBUYER) {
        BUYER buyer(user->getAccount(), repo);      // Creates NEW BUYER with repo
    }
}
```

**ISSUE**: 
- User object is created by `AUTHORITY_SERVICE::login()` without repo
- Then a NEW user object is created in handleUserLogin() with repo
- This means the first object (created during login) is never used!
- **Memory leak and inefficiency** - user object created in login() is replaced immediately

### SYSTEM::handleAdminLogin()
```cpp
void SYSTEM::handleAdminLogin() {
    if (!adminLogin(passcode)) { return; }
    ADMIN admin(adminPass, repo, auth);  // Correctly passes repo and auth
    admin.startSession();
    isAdminLogggedin = false;
}
```
- ✅ Correctly passes PRODUCT_REPO and AUTHORITY_SERVICE

---

## 4. PRODUCT_REPO DATABASE CONNECTIONS

### Is PRODUCT_REPO passed to BUYER?
- **Constructor**: YES - `BUYER(USER_ACCOUNT, PRODUCT_REPO&)`
- **Usage in SYSTEM::handleUserLogin()**: YES - Creates BUYER with repo reference
- **Methods using it**: 
  - `viewProduct()` → calls `repo->getAllProducts(false)`
  - `searchProduct()` → calls `repo->searchByName(keyword)`
  - `handleSearch()` → calls `repo->searchByName()`

### Is PRODUCT_REPO passed to SELLER?
- **Constructor**: YES - `SELLER(USER_ACCOUNT, PRODUCT_REPO&)`
- **Usage in SYSTEM::handleUserLogin()**: YES - Creates SELLER with repo reference
- **Methods using it**:
  - `viewProduct()` → calls `repo->getAllProducts(false)`
  - `searchProduct()` → calls `repo->searchByName()`
  - `addProduct()` → calls `repo->addProduct()` and `repo->saveToFile()`

### Is PRODUCT_REPO passed to ADMIN?
- **Constructor**: YES - `ADMIN(const string&, PRODUCT_REPO&, AUTHORITY_SERVICE&)`
- **Usage in SYSTEM::handleAdminLogin()**: YES - Creates ADMIN with repo reference
- **Methods using it**:
  - `handleProductOperations()` → calls `repo->getAllProducts(true)`

### Is PRODUCT_REPO passed via SYSTEM methods?
- **SYSTEM members**: 
  - Has `PRODUCT_REPO repo` as member
  - Has `PRODUCT_REPO& getRepo()` method
- **Direct SYSTEM methods**:
  - `addProduct()` → uses `repo.addProduct()`
  - `removeProduct()` → uses `repo.removeProduct()`
  - `updateProduct()` → uses `repo.updateProduct()`
  - `searchByName()` → uses `repo.searchByName()`
  - `getAllProducts()` → uses `repo.getAllProducts()`

---

## 5. AUTHORITY_SERVICE AUTHENTICATION

### Is AUTHORITY_SERVICE passed to BUYER?
- **Constructor parameters**: NO - only receives USER_ACCOUNT and PRODUCT_REPO
- **Usage in BUYER**: 
  - `authenticate(AUTHORITY_SERVICE& auth)` method expects parameter but receives nothing
  - Implementation: `return auth.verifyClient(user_acc.getUsername(), "");`
  - **ISSUE**: authenticate() method is called WITH auth parameter from somewhere, but no storage of auth in BUYER

### Is AUTHORITY_SERVICE passed to SELLER?
- **Constructor parameters**: NO - only receives USER_ACCOUNT and PRODUCT_REPO
- **Usage in SELLER**: 
  - `authenticate(AUTHORITY_SERVICE& auth)` method expects parameter
  - Implementation: `return auth.verifyClient(user_acc.getUsername(), "");`

### Is AUTHORITY_SERVICE passed to ADMIN?
- **Constructor parameters**: YES - receives `AUTHORITY_SERVICE&`
- **Usage in ADMIN**: 
  - Stores as member `AUTHORITY_SERVICE* auth_service`
  - Used in `handleUserManagement()` to get all users and delete users
  - Calls `auth_service->getAllRegisteredUsers()` and `auth_service->deleteUserByUsername()`

### How is AUTHORITY_SERVICE available to derived classes?
- BUYER/SELLER: Not stored - passed as parameter to `authenticate()` method when called
- ADMIN: Stored as member pointer
- **Pattern inconsistency**: BUYER/SELLER don't store auth, ADMIN does

---

## 6. SYSTEM CLASS INSTANTIATION & MANAGEMENT

### How SYSTEM creates/manages user instances:

**In SYSTEM constructor**: 
```cpp
SYSTEM::SYSTEM()
    : current_user(nullptr), repo(), isAdminLogggedin(false)
```
- Initializes empty current_user pointer
- Creates PRODUCT_REPO instance
- Creates AUTHORITY_SERVICE instance

**During normal user login** (SYSTEM::handleUserLogin()):
```cpp
USER* user = loginAccount(username, password);  // May be nullptr
if (!user) { cout << "Login failed"; return; }

cout << "Welcome, " << user->getUsername() << "!";

if (user->getAuthority() == ClientSELLER) {
    SELLER seller(user->getAccount(), repo);    // Creates new SELLER on LOCAL stack
    seller.startSession();
}
// ... SELLER goes out of scope, destroyed
logoutCurrentUser();  // Deletes the user from loginAccount
```

**Issues**:
1. `user` is created at heap (via loginAccount)
2. Temporary SELLER/BUYER is created on LOCAL STACK with separate instance
3. The heap `user` object is later deleted in logoutCurrentUser()
4. The temporary objects are destroyed when going out of scope
5. **Two different user objects are used!**

**During admin login** (SYSTEM::handleAdminLogin()):
```cpp
if (!adminLogin(passcode)) { return; }
ADMIN admin(adminPass, repo, auth);  // Local stack object
admin.startSession();
isAdminLogggedin = false;
```
- Creates local ADMIN object on stack
- ADMIN is destroyed after handleAdminLogin() returns

**Management strategy observations**:
- ✅ PRODUCT_REPO is created once in SYSTEM, reused throughout
- ✅ AUTHORITY_SERVICE is created once in SYSTEM, reused throughout
- ❌ User objects (BUYER/SELLER) are created twice - once unnecessary heap allocation, once on stack
- ⚠️ ADMIN object is local stack variable, not persistent manager
- ✅ current_user tracks login state for non-admin users

---

## 7. USER BASE CLASS - VIRTUAL METHODS

### Pure Virtual Methods defined in USER.h:
1. `virtual bool authenticate(AUTHORITY_SERVICE& auth) = 0`
2. `virtual void performAction() = 0`
3. `virtual std::string getUsername() const = 0`
4. `virtual void viewProduct(std::string) = 0`
5. `virtual void searchProduct(std::string) = 0`

### BUYER Implementation Status:
1. ✅ `authenticate()` - Implemented: calls `auth.verifyClient()`
2. ✅ `performAction()` - Implemented: prints "Buyer interacting"
3. ✅ `getUsername()` - Implemented: returns `user_acc.getUsername()`
4. ✅ `viewProduct()` - Implemented: displays all products via `repo->getAllProducts()`
5. ✅ `searchProduct()` - Implemented: searches via `repo->searchByName()`

### SELLER Implementation Status:
1. ✅ `authenticate()` - Implemented: calls `auth.verifyClient()`
2. ✅ `performAction()` - Implemented: prints "Seller interacting"
3. ✅ `getUsername()` - Implemented: returns `user_acc.getUsername()`
4. ✅ `viewProduct()` - Implemented: displays all products via `repo->getAllProducts()`
5. ✅ `searchProduct()` - Implemented: searches via `repo->searchByName()`

### ADMIN Implementation Status:
1. ✅ `authenticate()` - Implemented: calls `auth.verifyAdmin()` (using stored auth_service)
2. ✅ `performAction()` - Implemented: calls `AdminMenu()`
3. ✅ `getUsername()` - Implemented: returns "ADMIN"
4. ✅ `viewProduct()` - Implemented (override keyword present)
5. ✅ `searchProduct()` - Implemented (override keyword present)

**Status**: All derived classes ✅ properly implement required virtual methods

---

## 8. main.cpp ANALYSIS

```cpp
int main() {
    SYSTEM system;
    system.run();
    return 0;
}
```

- Creates single SYSTEM instance
- Calls run() which enters main menu loop
- SYSTEM manages all interactions with repo, auth, and user sessions

---

## INTERCONNECTION MAP

```
┌─────────────────────────────────────────────────────────────┐
│                    main.cpp                                 │
│              Creates SYSTEM and calls run()                 │
└────────────────────────┬────────────────────────────────────┘
                         │
                         v
        ┌────────────────────────────────────┐
        │        SYSTEM (Central Hub)         │
        ├────────────────────────────────────┤
        │ Members:                            │
        │ - PRODUCT_REPO repo ✅             │
        │ - AUTHORITY_SERVICE auth ✅        │
        │ - USER* current_user               │
        │ - bool isAdminLogggedin            │
        └────────┬──────────────┬────────────┘
                 │              │
        ┌────────v──────────┐   │
        │ PRODUCT_REPO      │   │
        ├───────────────────┤   │
        │ - vector products │   │
        │ - addProduct()    │   │
        │ - removeProduct() │   │
        │ - searchByName()  │   │
        │ - saveToFile()    │   │
        │ - loadFromFile()  │   │
        └───────────────────┘   │
                                │
        ┌────────────────────────v─────────────────┐
        │   AUTHORITY_SERVICE                      │
        ├──────────────────────────────────────────┤
        │ - vector<USER_ACCOUNT> registered_user   │
        │ - registerUser()                         │
        │ - login() ← CREATES USER* (ISSUE!)      │
        │ - verifyAdmin()                          │
        │ - getAllRegisteredUsers()                │
        │ - deleteUserByUsername()                 │
        └──────────────────────────────────────────┘
             │                 │                │
             │ Creates         │ Creates       │ Creates
             │ (buggy)         │ (buggy)       │ (ok)
             v                 v               v
        ┌──────────┐    ┌──────────┐    ┌──────────────────┐
        │  BUYER   │    │ SELLER   │    │ ADMIN            │
        │(derives) │    │(derives) │    │ (derives)        │
        ├──────────┤    ├──────────┤    ├──────────────────┤
        │ USER*    │    │ USER*    │    │ USER*            │
        │repo ✅   │    │repo ✅   │    │repo ✅           │
        │          │    │          │    │auth_service ✅   │
        │Methods:  │    │Methods:  │    │                  │
        │-search() │    │-search() │    │Methods:          │
        │-view()   │    │-view()   │    │-deleteUser()     │
        └──────────┘    └──────────┘    └──────────────────┘
             ^                ^
             │         Created locally    
             │   in handleUserLogin()
             │
        ┌────────────────────────────────┐
        │   USER (Base Class)             │
        ├────────────────────────────────┤
        │ Pure Virtual Methods:           │
        │ - authenticate()                │
        │ - performAction()               │
        │ - getUsername()                 │
        │ - viewProduct()                 │
        │ - searchProduct()               │
        │                                 │
        │ Protected: USER_ACCOUNT         │
        │ Private: CART* cart             │
        └────────────────────────────────┘
```

---

## DEPENDENCY SUMMARY TABLE

| Component | Depends On | How Passed | Status |
|-----------|-----------|-----------|--------|
| **SYSTEM** | PRODUCT_REPO | Member (created) | ✅ |
| | AUTHORITY_SERVICE | Member (created) | ✅ |
| **BUYER** | PRODUCT_REPO | Constructor param → member | ✅ |
| | USER_ACCOUNT | Constructor param → base member | ✅ |
| | AUTHORITY_SERVICE | Method param only | ⚠️ Not stored |
| **SELLER** | PRODUCT_REPO | Constructor param → member | ✅ |
| | USER_ACCOUNT | Constructor param → base member | ✅ |
| | AUTHORITY_SERVICE | Method param only | ⚠️ Not stored |
| **ADMIN** | PRODUCT_REPO | Constructor param → member | ✅ |
| | AUTHORITY_SERVICE | Constructor param → member | ✅ |
| | USER_ACCOUNT | Implied (from SYSTEM login) | ⚠️ Not shown |
| **AUTHORITY_SERVICE** | USER_ACCOUNT (vector) | Internal storage | ✅ |
| | BUYER/SELLER | Creates in login() | ❌ **BROKEN** |
| **PRODUCT_REPO** | PRODUCT (vector) | Internal storage | ✅ |

---

## CRITICAL ISSUES FOUND

### 🔴 **ISSUE 1: AUTHORITY_SERVICE::login() Constructor Mismatch**
- **Location**: `src/AUTHORITY_SERVICE.cpp`, line 250-257
- **Severity**: COMPILATION ERROR
- **Description**: `login()` method creates BUYER/SELLER objects but doesn't pass PRODUCT_REPO reference
  ```cpp
  return new BUYER(registered_user[i]);  // Missing PRODUCT_REPO parameter!
  return new SELLER(registered_user[i]); // Missing PRODUCT_REPO parameter!
  ```
- **Expected signature**: `BUYER(USER_ACCOUNT, PRODUCT_REPO&)`
- **Requirements**: AUTHORITY_SERVICE needs access to PRODUCT_REPO to pass to BUYER/SELLER

### 🔴 **ISSUE 2: Double User Object Creation**
- **Location**: `src/SYSTEM.cpp`, SYSTEM::handleUserLogin()
- **Severity**: LOGIC ERROR, Resource waste
- **Description**: 
  1. User is created by `loginAccount()` (returns USER* from AUTHORITY_SERVICE)
  2. NEW temporary BUYER/SELLER created immediately after in local scope
  3. Original user object is discarded after login
  4. Temporary object destroyed at end of handleUserLogin()
- **Impact**: Inefficient, potential memory leak, logic confusion

### ⚠️ **ISSUE 3: AUTHORITY_SERVICE not Available to BUYER/SELLER**
- **Location**: BUYER.h, SELLER.h - only method parameters
- **Severity**: DESIGN INCONSISTENCY
- **Description**: 
  - BUYER/SELLER implement `authenticate()` method that takes AUTHORITY_SERVICE parameter
  - But nowhere is this method called with the auth object
  - ADMIN stores AUTHORITY_SERVICE as member, but BUYER/SELLER don't
- **Impact**: Inconsistent design pattern, potential unused methods

### ⚠️ **ISSUE 4: CART Member Not Initialized**
- **Location**: USER.h
- **Severity**: POTENTIAL RUNTIME ISSUE
- **Description**: USER base class has `CART* cart` member but it's never initialized/allocated
- **Impact**: If cart is accessed without proper initialization, nullptr dereference

---

## RECOMMENDATIONS

1. **Fix AUTHORITY_SERVICE::login()** to pass PRODUCT_REPO:
   ```cpp
   // Need to store repo reference or accept as parameter
   USER* AUTHORITY_SERVICE::login(string username, string password, PRODUCT_REPO& repo) {
       // ...
       return new BUYER(registered_user[i], repo);
       return new SELLER(registered_user[i], repo);
   }
   ```

2. **Simplify user object handling** in SYSTEM::handleUserLogin():
   - Use the USER* object returned from login directly, or
   - Pass PRODUCT_REPO to AUTHORITY_SERVICE beforehand

3. **Standardize AUTHORITY_SERVICE passing**:
   - Either store in BUYER/SELLER like ADMIN does, or
   - Only use as method parameters consistently

4. **Initialize CART member** in USER constructor

5. **Add override keywords** to derived class methods for clarity

