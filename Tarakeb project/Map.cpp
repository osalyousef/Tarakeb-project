#include "Accounts.h"
#include "AccountsMap.h"
#include "Admin.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

AccountsMap bankSystem;

void ui() {
    int choice;
    while (true) {
        cout << "\n===== Bank Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "4. Admin Panel\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            string firstName, lastName, pass;
            int phone;
            cout << "Enter First Name: ";
            cin.ignore();
            getline(cin, firstName);
            cout << "Enter Last Name: ";
            getline(cin, lastName);
            cout << "Enter Password: ";
            getline(cin, pass);
            cout << "Enter Phone Number: ";
            cin >> phone;

            if (bankSystem.getAccount(phone)) {
                cout << "Account already exists.\n";
                continue;
            }

            Accounts* newAcc = new Accounts(pass, firstName, lastName, phone);
            bankSystem.insertAccount(newAcc);
            cout << "Account created successfully. Your Account ID is: " << newAcc->getAccountId() << endl;

        } else if (choice == 2) {
            int phone;
            string pass;
            cout << "Enter Phone Number: ";
            cin >> phone;
            cout << "Enter Password: ";
            cin.ignore();
            getline(cin, pass);

            Accounts* acc = bankSystem.getAccount(phone);
            if (!acc || acc->getPassword() != pass) {
                cout << "Invalid credentials.\n";
                continue;
            }

            int subChoice;
            while (true) {
                cout << "\n--- Welcome, " << acc->getName() << " ---\n";
                cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View History\n5. Logout\nChoose: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    int amount;
                    cout << "Amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                } else if (subChoice == 2) {
                    int amount;
                    cout << "Amount to withdraw: ";
                    cin >> amount;
                    acc->withdraw(amount);
                } else if (subChoice == 3) {
                    int toPhone, amount;
                    cout << "Receiver's Phone Number: ";
                    cin >> toPhone;
                    cout << "Amount: ";
                    cin >> amount;

                    Accounts* receiver = bankSystem.getAccount(toPhone);
                    if (!receiver) {
                        cout << "Receiver not found.\n";
                        continue;
                    }
                    acc->transfer(amount, *receiver);
                } else if (subChoice == 4) {
                    acc->printTransHistory();
                } else if (subChoice == 5) {
                    break;
                } else {
                    cout << "Invalid option.\n";
                }
            }

        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else if (choice == 4) {
            Admin admin(&bankSystem);
            admin.adminPanel();
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    srand(time(0));
    ui();
    return 0;
}
