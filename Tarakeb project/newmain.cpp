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
    string password, fullName;
    int accountId;
    int phoneNum;

               //transefare;
    struct TransHistory {
        TransHistory* next;

        int amount;
        string type;           // ايداع , سحب , تحويل
        string senderName;
        int last4Num_Id;           // last 4  number of account id
    };

    TransHistory* Historyhead;

public:
 // all functions :
     
   //counstructer :
    Accounts();
    Accounts::Accounts(string password, string fullName, int accountId, int phoneNum);
     
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
    void addTrans(int amount , string type); // for deposit and with draw
    void addTrans(int amount, string type, string Fullname, int idLast4);
    void printTransHistory();
};

Accounts::Accounts() {
    balance = 0;
    cout << endl;
    Historyhead = NULL;
}

Accounts::Accounts(string password, string fullName, int accountId, int phoneNum) {
    this->password = password;
    this->fullName = fullName;
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
Accounts::addTrans(amount,type);

}

void Accounts:: withdraw(int amount){
         if(balance > 0 && (balance - amount) < 0 ){
            cout<<"Sorry , your withdraw is more then you have in bank"<<endl;
            cout<<"Your cuurent money in bank is : "<<balance<<endl;

            return;
         }
     
         
    cout<<"You sucssufully withdraw : "<<amount<<endl;
    cout<<"Your cuurent money in bank is : "<<balance<<endl;


    string type = "withdraw"; // to pass it to trans info

// should eneter Trans info here         
 
 Accounts::addTrans(amount,type);
}



void Accounts::addTrans(int amount , string type){
    TransHistory *temp = new TransHistory;

    TransHistory *current = Historyhead;

    
    temp->amount = amount;
    temp->type = type;
    temp->next = NULL;


    if(current == NULL){
    Historyhead = temp;
    return;
    }
      
    while (current->next !=NULL)
    {
        current = current->next;
    }
    
      current->next = temp;



}







void  Accounts:: addTrans(int amount , string type , string Fullname , int idLast4) {

    TransHistory *temp = new TransHistory;

    TransHistory *current = Historyhead;

    
    temp->amount = amount;
    temp->type = type;
    temp->last4Num_Id = idLast4;
    temp->senderName = Fullname;
    temp->next = NULL;


    if(current == NULL){
    Historyhead = temp;
    return;
    }
      
    while (current->next !=NULL)
    {
        current = current->next;
    }
    
      current->next = temp;



}

void Accounts:: printTransHistory(){

    TransHistory *current = Historyhead;
    if(current == NULL){
        cout<<"empty history .."<<endl;
        return;
        }

        while (current !=NULL)
        {
         if(current->type =="transefare"){
          cout<<"transefaration from ("<<current->last4Num_Id<<") sender '"<<current->senderName<<"\nAmount : "<<current->amount<<"SAR"<<endl;

          current = current->next;
          continue;
         }
        cout<<"you "<<current->type<<" : "<<current->amount<<endl;


            current = current->next;
        }
        
          
}










// map(dictionary) global stroge for accounts here :






int main(){



    return 0;
}