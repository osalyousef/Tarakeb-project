#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;

class Accounts {
private:
    float balance;
    string password, fullName;
    int accountId;
    int phoneNum;

    struct TransHistory {
        TransHistory* next;
        int amount;
        string type;
        string senderName;
        int last4Num_Id;
        string direction; // "from" or "to"
        string dateTime; // Date and time of the transaction
    };

    TransHistory* Historyhead;

public:
    Accounts() {
        balance = 0;
        Historyhead = NULL;
    }

    Accounts(string password, string firstName, string lastName, int phoneNum) {
        this->password = password;
        this->fullName = firstName + " " + lastName;  // Concatenate first and last name
        this->phoneNum = phoneNum;
        this->balance = 0;
        Historyhead = NULL;

        // Generate random accountId with 8 digits
        this->accountId = generateRandomAccountId();
    }

    int generateRandomAccountId() {
        return rand() % 90000000 + 10000000;  // Generate an 8-digit accountId
    }

    int getAccountId() { return accountId; }
    string getPassword() { return password; }
    float getBalance() { return balance; }
    string getName() { return fullName; }
    int getPhoneNum() { return phoneNum; }

    void deposit(int amount) {
        balance += amount;
        cout << "Deposited: " << amount << endl;
        addTrans(amount, "deposit");
    }

    void withdraw(int amount) {
        if (balance < amount) {
            cout << "Insufficient balance.\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << endl;
        addTrans(amount, "withdraw");
    }

    void transfer(int amount, Accounts& receiver, string direction) {
        if (balance < amount) {
            cout << "Insufficient balance.\n";
            return;
        }
        balance -= amount;
        receiver.balance += amount;

        // Add transaction for the sender (with last 4 digits of the receiver's account ID)
        addTrans(amount, "transfer", receiver.getName(), receiver.getAccountId(), "to");

        // Add transaction for the receiver (with last 4 digits of the sender's account ID)
        receiver.addTrans(amount, "transfer", getName(), getAccountId(), "from");

        cout << "Transferred " << amount << " to " << receiver.getName() << endl;
    }

    void addTrans(int amount, string type, string name = "", int idLast4 = 0, string direction = "") {
        // Get current date and time
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        string dateTime = ctime(&now);  // Convert time to string (includes a newline at the end)

        // Remove the trailing newline character added by ctime
        dateTime.pop_back();  // This removes the newline character at the end of the dateTime string

        // Get the last 4 digits of the account ID
        int last4 = idLast4 % 10000;  // This guarantees it will only show the last 4 digits

        // Create a new transaction
        TransHistory* temp = new TransHistory;
        temp->amount = amount;
        temp->type = type;
        temp->senderName = name;
        temp->last4Num_Id = last4;  // Store only the last 4 digits
        temp->direction = direction;
        temp->dateTime = dateTime;
        temp->next = NULL; // Set the next pointer to NULL initially

        if (Historyhead == NULL) {
            Historyhead = temp;  // If the list is empty, set the first element
        } else {
            TransHistory* current = Historyhead;
            while (current->next != NULL) {
                current = current->next;  // Traverse the list to find the last element
            }
            current->next = temp;  // Add the new transaction to the end
        }
    }

    void printTransHistory() {
        TransHistory* current = Historyhead;
        if (current == NULL) {
            cout << "No transaction history.\n";
            return;
        }

        // Traverse the linked list and print each transaction
        while (current != NULL) {
            cout << "[" << current->dateTime << "] ";  // Print date and time of the transaction

            if (current->type == "transfer") {
                cout << "Transfer " << current->direction << " (" << current->last4Num_Id << ") "
                     << current->senderName << ": " << current->amount << endl;
            } else {
                cout << "You " << current->type << ": " << current->amount << endl;
            }

            current = current->next;  // Move to the next transaction in the linked list
        }
    }
};

// ========== Hash Map Implementation ===========
const int TABLE_SIZE = 100;

struct AccountEntry {
    int accountId;
    Accounts account;
    AccountEntry* next;
};

class AccountMap {
private:
    AccountEntry* table[TABLE_SIZE];

    int hashFunction(int phoneNum) {
        return phoneNum % TABLE_SIZE;  // Use phone number as the key for hashing
    }

public:
    AccountMap() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    // Insert Account using phone number as the key
    void insertAccount(Accounts acc) {
        int key = acc.getPhoneNum();  // Use phone number as the key
        int index = hashFunction(key);

        AccountEntry* newEntry = new AccountEntry{ key, acc, nullptr };

        if (table[index] == nullptr) {
            table[index] = newEntry;
        } else {
            AccountEntry* current = table[index];
            while (current->next != nullptr)
                current = current->next;
            current->next = newEntry;
        }
    }

    // Get Account by phone number
    Accounts* getAccount(int phoneNum) {
        int index = hashFunction(phoneNum);  // Use phone number to calculate index
        AccountEntry* current = table[index];
        while (current != nullptr) {
            if (current->account.getPhoneNum() == phoneNum)  // Check if the phone number matches
                return &(current->account);  // Return the account object if match found
            current = current->next;
        }
        return nullptr;  // Account not found
    }
};

// Global AccountMap for storing accounts
AccountMap bankSystem;

// ========== UI Function ===========
void ui() {
    int choice;
    while (true) {
        cout << "\n===== Bank Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
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
                    // Transfer from the current account
                    acc->transfer(amount, *receiver, "to");
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
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    ui();  // Call the UI function
    return 0;
}
