#ifndef ADMIN_H
#define ADMIN_H

#include "Accounts.h"
#include "AccountsMap.h"
#include <iostream>
#include <vector>

class AccountsMap; // Forward declaration

class Admin {
private:
    AccountsMap* bankSystem;
    
public:
    Admin(AccountsMap* bankSystem);
    void viewAllAccounts();
    void undoLastTransaction(int phoneNumber);
    std::vector<Accounts*> getAllAccounts(); // New method to get all accounts
};

#endif
