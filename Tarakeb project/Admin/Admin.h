#ifndef ADMIN_H
#define ADMIN_H

#include "AccountsMap.h"
#include <vector>

using namespace std;

class Admin {
private:
    AccountsMap* bankSystem;
    
public:
    Admin(AccountsMap* bankSystem);
    void adminPanel();
    void viewAllAccounts();
    void undoLastTransaction(int phoneNumber);
};

#endif
