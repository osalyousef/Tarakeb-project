#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <string>
using namespace std;

class Accounts {
private:
    float balance;
    string password, fullName;
    int accountId;
    int phoneNum;


public:
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

    Accounts();
    Accounts(string password, string firstName, string lastName, int phoneNum);

    int generateRandomAccountId();
    int getAccountId();
    string getPassword();
    float getBalance();
    string getName();
    int getPhoneNum();

    void deposit(int amount);
    void withdraw(int amount);
    void transfer(int amount, Accounts& receiver, string direction);
    void addTrans(int amount, string type, string name = "", int idLast4 = 0, string direction = "");
    void printTransHistory();
    
    // For Admin class to access
    TransHistory* getHistoryHead() { return Historyhead; }
    void setHistoryHead(TransHistory* head) { Historyhead = head; }
    void adjustBalance(float amount) { balance += amount; }
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
    int hashFunction(int phoneNum);

public:
    AccountMap();
    void insertAccount(Accounts acc);
    Accounts* getAccount(int phoneNum);
    
    // To allow Admin class to access table
    AccountEntry* getTableEntry(int index) { return table[index]; }
    int getTableSize() { return TABLE_SIZE; }
};
// Add this after the AccountMap class definition - marwan

class FileStack {
private:
    struct Node {
        FILE* file;
        Node* next;
    };
    Node* top;
public:
    FileStack() : top(nullptr) {}
    void push(FILE* f) {
        Node* newNode = new Node{f, top};
        top = newNode;
    }
    FILE* pop() {
        if (!top) return nullptr;
        Node* temp = top;
        FILE* f = temp->file;
        top = top->next;
        delete temp;
        return f;
    }
    FILE* getTop() {
        return top ? top->file : nullptr;
    }
    ~FileStack() {
        while (top) {
            FILE* f = pop();
            if (f) fclose(f);
        }
    }
};

extern FileStack fileStack;

// Global AccountMap declaration
extern AccountMap bankSystem;

// UI Function declaration
void ui();

#endif 
