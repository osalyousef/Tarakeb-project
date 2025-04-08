#ifndef ACCINFO_H
#define ACCINFO_H
#include <iostream>
#define MAX_ACCOUNTS 10
using namespace std;

extern int AccountsNumber;

class AccountsInformations{
    private:
    float AccountBalance;
    string Password, Fname, Lname;
    int AccountId;

    struct TransctionsHistory{
        TransctionsHistory *link;

        struct TransctionsInfos{
            int sender, Reciver;
            float Amount;
        };

        TransctionsInfos infos;
    };

    TransctionsHistory *History;

    public:
    AccountsInformations(){
        AccountBalance = 0;
        Fname = Lname = "NULL";
        Password = "0000";
    }

    void SetAccBalance(float AC){
        AccountBalance = AC;
    }
    
    float GetAccBalance(){
        return AccountBalance;
    }

    void SetFname(string FN){
        Fname = FN;
    }

    string GetFname(){
        return Fname;
    }

    void SetLname(string LN){
        Lname = LN;
    }

    string GetLname(){
       return Lname;
    }

    void SetPassword(string PD){
        Password = PD;
    }

    string GetPassword(){
       return Password;
    }

    void AccCreation(){
        cout << "Enter your first name: ";
        cin >> Fname;
        cout << endl;

        cout << "Enter your last name: ";
        cin >> Lname;
        cout << endl;

        cout << "Enter your password: ";
        cin >> Password;
        cout << endl;

        AccountBalance = 1000;
        AccountId = AccountsNumber + 1;
        AccountsNumber++;
    }

    void Print(){
        if (Fname == "NULL" && Lname == "NULL" && Password == "0000" && AccountBalance == 0) {
            return;
        }
        cout << "----------Account info-------------" << endl;
        cout << "Name: " << Fname + " " + Lname << endl;
        cout  << "Account ID: "<< AccountId << endl;
        cout << "Balance: "<< AccountBalance << endl;

    } // reworked this to print all details and ignore construct - os
    
    void DefaultValues() { // to test - os
        Password = "1234";
        Fname = "Mohammed";
        Lname = "Khaled";
        AccountId = 12345;
        AccountBalance = 1000;
    }
};
#endif
