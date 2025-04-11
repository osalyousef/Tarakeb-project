#include "AccountsMap.h"

AccountsMap::AccountsMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

int AccountsMap::hashFunction(int phoneNum) {
    return phoneNum % TABLE_SIZE;
}

void AccountsMap::insertAccount(Accounts* acc) {
    int key = acc->getPhoneNum();
    int index = hashFunction(key);
    
    AccountEntry* newEntry = new AccountEntry{key, acc, nullptr};
    
    if (table[index] == nullptr) {
        table[index] = newEntry;
    } else {
        AccountEntry* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newEntry;
    }
}

Accounts* AccountsMap::getAccount(int phoneNum) {
    int index = hashFunction(phoneNum);
    AccountEntry* current = table[index];
    
    while (current != nullptr) {
        if (current->account->getPhoneNum() == phoneNum) {
            return current->account;
        }
        current = current->next;
    }
    return nullptr;
}

void AccountsMap::printAllAccounts() {
    cout << "\n==== All Bank Accounts ====\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        AccountEntry* current = table[i];
        while (current != nullptr) {
            Accounts* acc = current->account;
            cout << "Name: " << acc->getName()
                 << " | Phone: " << acc->getPhoneNum()
                 << " | Account ID: " << acc->getAccountId()
                 << " | Balance: " << acc->getBalance()
                 << endl;
            current = current->next;
        }
    }
}
