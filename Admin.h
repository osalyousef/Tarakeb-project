#ifndef ADMIN_H
#define ADMIN_H

#include "AccInfo.h"
#include <vector>
using namespace std;
class AccountMap; 
class Admin {
private:
    AccountMap* bankSystem;
    
public:
    Admin(AccountMap* bankSystem);
    void adminPanel();
    void viewAllAccounts();
    void undoLastTransaction(int phoneNumber);
};

#endif // ADMIN_H