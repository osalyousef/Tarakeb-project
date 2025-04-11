#include "Admin.h"

using namespace std;

Admin::Admin(AccountsMap* bankSystem) : bankSystem(bankSystem) {}

void Admin::adminPanel() {
    int adminOption;
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

void Admin::viewAllAccounts() {
    if (bankSystem) {
        bankSystem->printAllAccounts();
    } else {
        cout << "Error: Bank system not initialized.\n";
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

    account->undoLastTransaction();
}


