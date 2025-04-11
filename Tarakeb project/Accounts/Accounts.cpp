#include "accounts.h"
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

Accounts::Accounts() {
    balance = 0;
    Historyhead = NULL;
}

Accounts::Accounts(string password, string firstName, string lastName, int phoneNum) {
    this->password = password;
    this->fullName = firstName + " " + lastName;
    this->phoneNum = phoneNum;
    this->balance = 0;
    Historyhead = NULL;
    this->accountId = generateRandomAccountId();
}

int Accounts::generateRandomAccountId() {
    srand(time(0));
    return 100000 + (rand() % 900000); // 6-digit number
}

void Accounts::setBalance(float balance) {
    this->balance = balance;
}

float Accounts::getBalance() {
    return this->balance;
}

void Accounts::setPassword(string password) {
    this->password = password;
}

string Accounts::getPassword() {
    return this->password;
}

void Accounts::setAccountId(int accountId) {
    this->accountId = accountId;
}

int Accounts::getAccountId() {
    return this->accountId;
}

void Accounts::setPhoneNum(int phoneNum) {
    this->phoneNum = phoneNum;
}

int Accounts::getPhoneNum() {
    return this->phoneNum;
}

string Accounts::getName() {
    return this->fullName;
}

void Accounts::deposit(int amount) {
    balance += amount;
    cout << "You successfully deposited: " << amount << endl;
    cout << "Your current balance is: " << balance << endl;

    addTrans(amount, "deposit");
}

void Accounts::withdraw(int amount) {
    if(balance <= 0 || (balance - amount) < 0) {
        cout << "Sorry, you don't have sufficient funds" << endl;
        cout << "Your current balance is: " << balance << endl;
        return;
    }
    
    balance -= amount;
    cout << "You successfully withdrew: " << amount << endl;
    cout << "Your current balance is: " << balance << endl;

    addTrans(amount, "withdraw");
}

void Accounts::transfer(int amount, Accounts& receiver) {
    if(balance <= 0 || (balance - amount) < 0) {
        cout << "Sorry, you don't have sufficient funds" << endl;
        cout << "Your current balance is: " << balance << endl;
        return;
    }
    
    balance -= amount;
    receiver.balance += amount;
    
    // Get current time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string timeStr = to_string(1900 + ltm->tm_year) + "-" +
                    to_string(1 + ltm->tm_mon) + "-" +
                    to_string(ltm->tm_mday) + " " +
                    to_string(ltm->tm_hour) + ":" +
                    to_string(ltm->tm_min) + ":" +
                    to_string(ltm->tm_sec);

    // Add transaction to both accounts
    addTrans(amount, "transfer", receiver.getName(), receiver.getAccountId() % 10000, "outgoing");
    receiver.addTrans(amount, "transfer", this->getName(), this->getAccountId() % 10000, "incoming");
    
    cout << "You successfully transferred: " << amount << " to " << receiver.getName() << endl;
    cout << "Your current balance is: " << balance << endl;
}

void Accounts::addTrans(int amount, string type, string name, int idLast4, string direction) {
    TransHistory* temp = new TransHistory;
    TransHistory* current = Historyhead;

    // Get current time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string timeStr = to_string(1900 + ltm->tm_year) + "-" +
                    to_string(1 + ltm->tm_mon) + "-" +
                    to_string(ltm->tm_mday) + " " +
                    to_string(ltm->tm_hour) + ":" +
                    to_string(ltm->tm_min) + ":" +
                    to_string(ltm->tm_sec);

    temp->amount = amount;
    temp->type = type;
    temp->senderName = name;
    temp->last4Num_Id = idLast4;
    temp->direction = direction;
    temp->dateTime = timeStr;
    temp->next = NULL;

    if(current == NULL) {
        Historyhead = temp;
        return;
    }
    
    while(current->next != NULL) {
        current = current->next;
    }
    
    current->next = temp;
}

void Accounts::printTransHistory() {
    TransHistory* current = Historyhead;
    if(current == NULL) {
        cout << "No transaction history available." << endl;
        return;
    }

    cout << "Transaction History:" << endl;
    cout << "-------------------" << endl;
    
    while(current != NULL) {
        if(current->type == "transfer") {
            cout << "[" << current->dateTime << "] ";
            cout << "Transfer " << current->direction << ": ";
            cout << current->amount << " SAR ";
            if(current->direction == "outgoing") {
                cout << "to " << current->senderName;
            } else {
                cout << "from " << current->senderName;
            }
            cout << " (ID: " << current->last4Num_Id << ")" << endl;
        } else {
            cout << "[" << current->dateTime << "] ";
            cout << current->type << ": " << current->amount << " SAR" << endl;
        }
        current = current->next;
    }
}

void Accounts::undoLastTransaction() {
    if(Historyhead == NULL) {
        cout << "No transactions to undo." << endl;
        return;
    }

    TransHistory* last = Historyhead;
    TransHistory* prev = NULL;

    // Find the last transaction
    while(last->next != NULL) {
        prev = last;
        last = last->next;
    }

    // Undo the transaction
    if(last->type == "deposit") {
        balance -= last->amount;
        cout << "Undid deposit of " << last->amount << " SAR" << endl;
    }
    else if(last->type == "withdraw") {
        balance += last->amount;
        cout << "Undid withdrawal of " << last->amount << " SAR" << endl;
    }
    else if(last->type == "transfer") {
        // For simplicity, we'll just adjust balance
        // In a real system, you'd need to find the other account too
        if(last->direction == "outgoing") {
            balance += last->amount;
            cout << "Undid outgoing transfer of " << last->amount << " SAR" << endl;
        } else {
            balance -= last->amount;
            cout << "Undid incoming transfer of " << last->amount << " SAR" << endl;
        }
    }

    // Remove the transaction from history
    if(prev != NULL) {
        prev->next = NULL;
    } else {
        Historyhead = NULL;
    }
    delete last;

    cout << "Current balance: " << balance << " SAR" << endl;
}
