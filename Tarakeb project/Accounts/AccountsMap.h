// accountmap.h
#ifndef ACCOUNTMAP_H
#define ACCOUNTMAP_H

#include "Accounts.h"

const int TABLE_SIZE = 100;

struct AccountEntry {
    int phoneKey;
    Accounts* account;
    AccountEntry* next;
};

class AccountMap {
private:
    AccountEntry* table[TABLE_SIZE];
    int hashFunction(int phoneNum);

public:
    AccountMap();
    void insertAccount(Accounts* acc);
    Accounts* getAccount(int phoneNum);
    void printAllAccounts();
};

#endif
