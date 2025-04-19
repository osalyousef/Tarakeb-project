#include "Admin.h"
#include "AccInfo.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <fstream>  //this for ifstream
#include <sstream>  //this for stringstream

using namespace std;
void ui() {
    Admin admin(&bankSystem); // Create the admin object
    
    int choice;
    while (true) {
        cout << "\n===== Bank Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Log In\n";
        cout << "3. Admin Panel\n";  // Added admin option
        cout << "4. Exit\n";
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
            bool isNumber = false;
            do {
                if (cin >> phone) {
                    isNumber = true;
                }
                else {
                    cout << "Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                }
            } while (!isNumber);
            
            if (bankSystem.getAccount(phone)) {
                cout << "Account already exists.\n";
                continue;
            }

            Accounts newAcc(pass, firstName, lastName, phone);
            bankSystem.insertAccount(newAcc);
            cout << "Account created successfully. Your Account ID is: " << newAcc.getAccountId() << endl;

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
                cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View History\n5. View My Balance\n6. Logout\nChoose: ";
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
                    // Transfer from the current account
                    acc->transfer(amount, *receiver, "to");
                } else if (subChoice == 4) {
                    acc->printTransHistory();
                } else if (subChoice == 5) {
                    cout << "Your balance is: " << acc->getBalance() << endl;
                }
                    else if (subChoice == 6) {
                        break;
                    }
                 else {
                    cout << "Invalid option.\n";
                }
            
            }
        } else if (choice == 3) {
            // Admin access
            admin.adminPanel();
        } else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void processCommand(const string& line) {
    stringstream ss(line);
    string command;
    ss >> command;

    if (command == "CREATE") {
        int phone;
        string firstName, lastName, password;
        ss >> phone >> firstName >> lastName >> password;
        
        if (bankSystem.getAccount(phone)) {
            cout << "Account already exists.\n";
            return;
        }

        Accounts newAcc(password, firstName, lastName, phone);
        bankSystem.insertAccount(newAcc);
        cout << "Account created successfully. Account ID: " << newAcc.getAccountId() << endl;
    }
    else if (command == "LOGIN") {
        int phone;
        string password;
        ss >> phone >> password;

        Accounts* acc = bankSystem.getAccount(phone);
        if (!acc || acc->getPassword() != password) {
            cout << "Invalid credentials.\n";
            return;
        }
        cout << "Successfully logged in as " << acc->getName() << endl;
    }
    else if (command == "LOGOUT") {
        cout << "Successfully logged out.\n";
    }
    else if (command == "DEPOSIT") {
        int phone, amount;
        ss >> phone >> amount;
        
        Accounts* acc = bankSystem.getAccount(phone);
        if (acc) {
            acc->deposit(amount);
        } else {
            cout << "Account not found.\n";
        }
    }
    else if (command == "WITHDRAW") {
        int phone, amount;
        ss >> phone >> amount;
        
        Accounts* acc = bankSystem.getAccount(phone);
        if (acc) {
            acc->withdraw(amount);
        } else {
            cout << "Account not found.\n";
        }
    }
    else if (command == "TRANSFER") {
        int fromPhone, toPhone, amount;
        ss >> fromPhone >> toPhone >> amount;
        
        Accounts* sender = bankSystem.getAccount(fromPhone);
        Accounts* receiver = bankSystem.getAccount(toPhone);
        
        if (sender && receiver) {
            sender->transfer(amount, *receiver, "to");
        } else {
            cout << "One or both accounts not found.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    FILE* logFile = fopen("transactions.log", "a");
    if (logFile) {
        fileStack.push(logFile);
    } else {
        cout << "Warning: Could not open transactions.log" << endl;
    }

    if (argc > 1) {
        ifstream inputFile(argv[1]);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                cout << "Processing command: " << line << endl;
                processCommand(line);
            }
            inputFile.close();
        } else {
            cout << "Could not open input file" << endl;
        }
    }
    
    ui();
    FILE* f = fileStack.pop();
    if (f) fclose(f);
    
    return 0;
}
