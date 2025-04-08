#include <iostream>
using namespace std;

int AccountsNumber = 0; 

class AccountsInformations{
    private : 
    float AccountBalance ; 
    string Password , Fname , Lname ; 
    int AccountId ; 


    struct TransctionsHistory{
    
        TransctionsHistory *link ; 

        struct TransctionsInfos{
          int Sender , Reciver  ; 
          float Amount ;  
        };

     TransctionsInfos infos ;

    };

    TransctionsHistory *History ; 

    public  :

    AccountsInformations(){
        AccountBalance = 0 ; 
        string Fname , Lname = "USER" ; 
        string Password = "0000" ; 
    }  

    void SetAccBalance( float AC ){
        AccountBalance = AC ;     
    }
    
    float SetAccBalance(){
        return AccountBalance ;     
    }

    void SetFname( string FN ){
        Fname = FN ;     
    }

    string GetFname(){
        return Fname ; 
    }

    void SetLname( string LN ){
        Lname = LN ;     
    }

    string GetLname(){
       return Lname ;     
    }

    void SetPassword( string PD ){
        Password = PD ; 
    }

    string GetPassword(){
       return Password ; 
    }

    void AccCreation(){
        
      cout << "Enter your first name : " ; 
      cin >> Fname ; 
      cout << endl; 

      cout << "Enter your last name : " ; 
      cin >> Lname ; 
      cout << endl; 

      cout << "Enter your password : " ; 
      cin >> Password ; 
      cout << endl; 


      AccountBalance = 0 ; 
      AccountId = AccountsNumber + 1 ; 
      AccountsNumber++ ; 
    }

    void Print(){
       cout << Fname << endl ;     
       cout << Lname << endl ; 
    }


};

void UI() ; 
   
AccountsInformations *Accounts = new AccountsInformations[AccountsNumber + 1] ; // Globally decleared 

int main(){
   
   UI() ; 
      



    cout << "Working" ; 



 //     delete[] ptr ; 
    return 0 ; 
}



void UI(){
    int choice = 0 ; 
   cout << "=================Main Menu=================" << endl  ; 
   cout << "1- Login" << endl  ;
   cout << "2- Sign in" << endl ; 
   cout << "3- Exit" << endl  ;
    
  cin >> choice ; 
   switch(choice){
    case 1 : break ; 
    case 2 : Accounts[AccountsNumber].AccCreation() ;
             Accounts[AccountsNumber].Print() ;
   }


}
