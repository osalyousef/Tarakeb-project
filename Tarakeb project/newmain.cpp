#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

class Accounts {
private:
    float balance;
    string password, Fname, Lname;
    int accountId;
    int phoneNum;

    string typeOp[] = {"withdraw", "deposit", "transfer"};

    struct TransHistory {
        TransHistory* next;

        int amount;
        string type;           // ايداع , سحب , تحويل
        string nameSender[2];
        int last4Num_Id;           // last 4  number of account id
    };

    TransHistory* Historyhead;

public:
 // all functions :
     
   //counstructer :
    Accounts();
    Accounts(string password, string Fname, string Lname, int accountId, int phoneNum);
     
    //setter and getter :
    void setBalance(float balance);
    float getBalance();

    void setFname(string Fname);
    string getFname();

    void setLname(string Lname);
    string getLname();

    void setPassword(string password);
    string getPassword();

    void setAccountId(int accountId);
    int getAccountId();

    void setPhoneNum(int phoneNum);
    int getPhoneNum();

    // bank operaitons 
    void deposit(int amount);
    void withdraw(int amount);
    // int transfare(int amount);

    

};

Accounts::Accounts() {
    balance = 0;
    cout << endl;
    Historyhead = NULL;
}

Accounts::Accounts(string password, string Fname, string Lname, int accountId, int phoneNum) {
    this->password = password;
    this->Fname = Fname;
    this->Lname = Lname;
    this->accountId = accountId;
    this->phoneNum = phoneNum;
    this->balance = 0;  
    Historyhead = NULL;

}

void Accounts::setBalance(float balance) {
    this->balance = balance;
}

float Accounts::getBalance() {
    return this->balance;
}

void Accounts::setFname(string Fname) {
    this->Fname = Fname;
}

string Accounts::getFname() {
    return this->Fname;
}

void Accounts::setLname(string Lname) {
    this->Lname = Lname;
}

string Accounts::getLname() {
    return this->Lname;
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



void Accounts:: deposit(int amount){

    balance += amount;
    cout<<"You sucssufully Deposited : "<<amount<<endl;
    cout<<"Your cuurent money in bank is : "<<balance<<endl;


    string type = "deposit"; // to pass it to trans info

// should eneter Trans info here         

}

void Accounts:: withdraw(int amount){
         if(balance < 0 && (balance - amount) < 0 ){
            cout<<"Sorry , your withdraw is more then you have in bank"<<endl;
            cout<<"Your cuurent money in bank is : "<<balance<<endl;

            return;
         }
     
         
    cout<<"You sucssufully withdraw : "<<amount<<endl;
    cout<<"Your cuurent money in bank is : "<<balance<<endl;


    string type = "withdraw"; // to pass it to trans info

// should eneter Trans info here         

}




















// map(dictionary) global stroge for accounts here :






int main{



    return 0;
}