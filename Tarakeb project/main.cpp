#include <iostream>
#include "AccInfo.h"
#define MAX_ACCOUNTS 10
using namespace std;
int AccountsNumber = 0;


void UI();
void NewUser();
AccountsInformations *Accounts = new AccountsInformations[MAX_ACCOUNTS];
// Globally declared
// MADE MAX ACCOUNTS SO THAT THE APP CAN HAVE MORE THAN 2 ACCOUNTS AS BEFORE - os
// AccountsNumber + 1 ماتقدر تسوي الا حسابين بس - os

int main(){
    UI();
    cout << "Working";
    return 0;
}




// functions
void UI(){
    int choice = 0;
    while (choice != 5) { // So it loops until input is 5
        
        
        cout << "=================Main Menu=================" << endl;
        cout << "1- Transaction" << endl;
        cout << "2- Withdrawl" << endl;
        cout << "3- New account" << endl;
        cout << "4- See account info" << endl;
        cout << "5- Exit" << endl;
        
        cout << "Choice: ";
        
        cin >> choice;
        switch(choice){
            case 1: break;
                
            case 2: break;
                
                
            case 3: NewUser();
                break;
                
            case 4:
                if (AccountsNumber > 0) {
                    for (int i = 0; i < AccountsNumber; i++) {
                        // loop through the account
                        Accounts[i].Print();
                        cout << "-------------------------" << endl;
                    }
                } else {
                    cout << "No account is created" << endl;
                }
                Accounts[AccountsNumber].Print();
                break;
            case 5:
                exit(0);
                break;
        }
    }
}
void NewUser() {
    int NewUserChoice = 0;
    cout << "=================New user=================" << endl;
    cout << "1. Create new account" << endl;
    cout << "2. Use default values" << endl;
    cout << "Choice: ";
    
    while (!(cin >> NewUserChoice) || (NewUserChoice != 1 && NewUserChoice != 2)) { // if the user entered anything other than 1 or 2 the condition is true (error)
        cout << "wrong input";
    }

    switch (NewUserChoice) {
        case 1:
            Accounts[AccountsNumber].AccCreation();
            AccountsNumber++;
            break;
        case 2:
            Accounts[AccountsNumber].DefaultValues();
            cout << "Default account" << endl;
            Accounts[AccountsNumber].Print();
            AccountsNumber++;
            break;
    }
    
    UI();
}
    

