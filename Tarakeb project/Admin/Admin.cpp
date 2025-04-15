#include "Admin.h"
#include <iostream>
#include "AccInfo.h"

using namespace std;

Admin::Admin(AccountMap* bankSystem) : bankSystem(bankSystem) {}

void Admin::adminPanel() {
    int adminOption;
    
    while (true) {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. View All Accounts\n";
        cout << "2. Undo Last Operation (by phone number)\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> adminOption;
        
        switch (adminOption) {
            case 1:
                viewAllAccounts();
                break;
            case 2: {
                int phone;
                cout << "Enter phone number of account to undo last operation: ";
                cin >> phone;
                undoLastTransaction(phone);
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid admin option.\n";
        }
    }
}

void Admin::viewAllAccounts() {
    if (!bankSystem) {
        cout << "Error: Bank system not initialized.\n";
        return;
    }
    
    int accountCount = 0;
    
    for (int i = 0; i < bankSystem->getTableSize(); i++) {
        AccountEntry* current = bankSystem->getTableEntry(i);
        while (current != nullptr) {
            accountCount++;
            cout << "Account #" << accountCount << ":" << endl;
            cout << "  ID: " << current->account.getAccountId() << endl;
            cout << "  Name: " << current->account.getName() << endl;
            cout << "  Phone: " << current->account.getPhoneNum() << endl;
            cout << "  Balance: $" << current->account.getBalance() << endl;
            cout << "  -------------------" << endl;
            current = current->next;
        }
    }
    
    if (accountCount == 0) {
        cout << "No accounts in the system.\n";
    } else {
        cout << "Total accounts: " << accountCount << endl;
    }
}

void Admin::undoLastTransaction(int phoneNumber) {
    if (!bankSystem) {
        cout << "Error: Bank system not initialized.\n";
        return;
    }
    
    Accounts* account = bankSystem->getAccount(phoneNumber);
    if (!account) {
        cout << "Account not found.\n";
        return;
    }
    
    // Get history head
    Accounts::TransHistory* head = account->getHistoryHead();
    if (!head) {
        cout << "No transactions to undo.\n";
        return;
    }
    
    // If there's only one transaction
    if (head->next == NULL) {
        // Reverse the transaction effect on balance
        if (head->type == "deposit") {
            account->adjustBalance(-head->amount);
            cout << "Undid deposit of " << head->amount << endl;
        } else if (head->type == "withdraw") {
            account->adjustBalance(head->amount);
            cout << "Undid withdrawal of " << head->amount << endl;
        } else if (head->type == "transfer") {
            // For transfer, we only handle simple undos here
            // A proper implementation might need to update the other account too
            if (head->direction == "to") {
                account->adjustBalance(head->amount);
                cout << "Undid outgoing transfer of " << head->amount << endl;
            } else {
                account->adjustBalance(-head->amount);
                cout << "Undid incoming transfer of " << head->amount << endl;
            }
        }
        
        // Delete the transaction record
        delete head;
        account->setHistoryHead(NULL);
        return;
    }
    
    // Find the second-to-last transaction
    Accounts::TransHistory* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    // Get the last transaction
    Accounts::TransHistory* lastTrans = current->next;
    
    // Reverse the last transaction effect on balance
    if (lastTrans->type == "deposit") {
        account->adjustBalance(-lastTrans->amount);
        cout << "Undid deposit of " << lastTrans->amount << endl;
    } else if (lastTrans->type == "withdraw") {
        account->adjustBalance(lastTrans->amount);
        cout << "Undid withdrawal of " << lastTrans->amount << endl;
    } else if (lastTrans->type == "transfer") {
        if (lastTrans->direction == "to") {
            account->adjustBalance(lastTrans->amount);
            cout << "Undid outgoing transfer of " << lastTrans->amount << endl;
        } else { // "from"
            account->adjustBalance(-lastTrans->amount);
            cout << "Undid incoming transfer of " << lastTrans->amount << endl;
        }
    }
    
    // Delete the last transaction and update the linked list
    delete lastTrans;
    current->next = NULL;
}
