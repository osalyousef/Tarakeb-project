#ifndef ACCOUNTSMAP_H
#define ACCOUNTSMAP_H

#include "Accounts.h"
#include <iostream>

using namespace std;

const int TABLE_SIZE = 100;

struct AccountEntry {
    int phoneKey;
    Accounts* account;
    AccountEntry* next;
};

class AccountsMap {
private:

public:
    AccountEntry* table[TABLE_SIZE];
    int hashFunction(int phoneNum);
    AccountsMap();
    void insertAccount(Accounts* acc);
    Accounts* getAccount(int phoneNum);
    void printAllAccounts();
};

#endif
