#ifndef ACCOUNTS_H
#define ACCOUNTS_H

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
        string direction;
        string dateTime;
    };

    TransHistory* Historyhead;

public:
    Accounts();
    Accounts(string password, string firstName, string lastName, int phoneNum);
    
    int generateRandomAccountId();
    void setBalance(float balance);
    void setPassword(string password);
    void setAccountId(int accountId);
    void setPhoneNum(int phoneNum);
    
    int getAccountId();
    string getPassword();
    float getBalance();
    string getName();
    int getPhoneNum();
    
    void deposit(int amount);
    void withdraw(int amount);
    void transfer(int amount, Accounts& receiver);
    void addTrans(int amount, string type, string name = "", int idLast4 = 0, string direction = "");
    void printTransHistory();
    void undoLastTransaction();
};

#endif
