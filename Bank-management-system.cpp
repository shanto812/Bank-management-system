#include <iostream>
#include <string>
using namespace std;
class BankAccount
{
private:
    static const int MAX_ACCOUNTS = 1000;
    struct Account
    {
        string number;
        string password;
        string name;
       double balance;
    };
    Account accounts[MAX_ACCOUNTS];
     int accountCount=4;

    int changeACnumber = 0;
public:
    BankAccount()
    {
        initializeAccounts();

    }

    void initializeAccounts()
    {
        accounts[0] = {"01406501", "Rafi014", "Tahamid hasan rafi", 500000};
        accounts[1] = {"01795561", "Alvi017", "Alvi hasan", 401235};
        accounts[2] = {"01909419", "Hasib019", "Hasibul santo", 300000};
        accounts[3] = {"01630200", "Kamrul016", "Kamrul Hasan", 256321};
}

    void getData()
    {

        string response;
        cout << "---WELCOME NUB BANK---\nDo you have any Account in this bank?\n"
             << "'yes'  "
             << "or  "
             << "'no'\n";
        cin >> response;

        if (response == "yes" || response == "YES" || response == "Yes")
        {
            getExistingAccountData();
        }
        else if (response == "no" || response == "No" || response == "NO")
        {
            createNewAccount();
        }
        else
            {
            cout << "Type 'yes' or 'no'\n:";

            getData();
            }
    }
    void getExistingAccountData()
    {
        string enteredNumber, enteredPassword;
        cout << "Enter your AC number:";
        cin >> enteredNumber;
        cout << "Enter your Password:";
        cin >> enteredPassword;
        matchData(enteredNumber, enteredPassword);
    }
    void createNewAccount()
    {
        changeACnumber=changeACnumber+188;
        accountCount++;
        if (accountCount < MAX_ACCOUNTS)
        {
            int nid;
            int phone;
            string NomineeName;
            int NomineePhone;
            int index = accountCount;

            cout << "Enter your name:";
            cin >> ws;
            getline(cin, accounts[index].name);

            cout << "Enter your password:";
            cin >> accounts[index].password;
            cout << "Enter your phone number:";
            cin>>phone;
            cout << "Enter your NID number:";
            cin>>nid;
            cout << "Enter your nominee name:";
            cin >> ws;
            getline(cin, NomineeName);
            cout << "Enter your nominee phone number:";
            cin>>NomineePhone;

            accounts[index].number = generateAccountNumber();
            accounts[index].balance = 0;

            cout << "\n-After creating a new account-\n"
                 << "AC number: " << accounts[index].number << "\n"
                 << "AC name: " << accounts[index].name << "\n"
                 << "AC password: " << accounts[index].password << "\n"
                 << "New account balance: " << accounts[index].balance << "\n";
                cout << "for new account you can deposit.\n";

              deposit(index);


            cout << "-----THANK YOU!-----\n";

            getData();
        }
        else
        {
            cout << "Can't create a new account. Maximum limit you have reached.\n";
        }
    }

    string generateAccountNumber()
    {
        return "1" + to_string(changeACnumber) + "000";
    }

void handleTransaction(int accountIndex)
    {
        string transactionType;
        cout << "Your AC number: " << accounts[accountIndex].number << "\n"
             << "Your AC name: " << accounts[accountIndex].name << "\n"
             << "Your Balance: $" << accounts[accountIndex].balance << "\n";

        cout << "What do you want?\n"
             << "1) Withdraw\n"
             << "2) Deposit\n"
             << "3) Transfer\n"
             << "4) Exit\n"
             << "5) logout and new login\n"
             << "type 1 , 2 , 3 , 4 or 5:\n ";
        cin >> transactionType;

        if (transactionType == "1")
        {
            withdraw(accountIndex);
        }
        else if (transactionType == "2")
        {
            deposit(accountIndex);
        }
        else if (transactionType == "3")
        {

           transfer(accountIndex, accounts[accountIndex].balance );

        }
        else if(transactionType == "4")
        {
            exit();
             exit();
        }
        else if(transactionType == "5")
        {
            exit();
            getData();
        }
        else
        {
            cout << "Invalid transaction type: Please type '1' for withdrawal or '2' for deposit or '3' for transfer or '4' for exit and '5' for exit and new login\n";
            handleTransaction(accountIndex);
        }
    }
  void deposit(int accountIndex)
    {
        double amount;
            cout << "How much?";
            cin >> amount;

            if (amount > 0)
            {
                accounts[accountIndex].balance += amount;
                cout << "Deposit successful ! New balance: $" << accounts[accountIndex].balance << "\n";
                getData();
            }
            else
            {
                cout << "\nInvalid deposit amount : Amount must be greater than 0.\n";
                deposit(accountIndex);
            }

    }
    void matchData(string enteredNumber, string enteredPassword)
    {
        for (int i = 0; i <= accountCount; i++)
        {
            if (enteredNumber == accounts[i].number && enteredPassword == accounts[i].password)
            {
                handleTransaction(i);
                return;
            }
        }

        cout << "Account number and password do not match !! \n";
        cout << "Enter valid AC number and password:\n";
        getExistingAccountData();
    }

    int matchData(string transferId, int accountIndex, double mainACblace)
    {
        int e=0;
        double tb;
        for (int i = 0; i <= accountCount; i++)
        {
            if (transferId == accounts[i].number)
            {
                cout << "Transfer AC match! AC name:\n"<<accounts[i].name<<" \n Enter your transfer amount:";
                cin>>tb;

                if(tb>=0 && tb<=mainACblace)
                {
                    accounts[accountIndex].balance -= tb;
                    accounts[i].balance += tb;
                    cout << "Transfer successful!\n Now your balance: "<<mainACblace-tb;
                e++;
                }
               else{
                    cout << "Amount must be grater then 0 and less then Main amount.";
                    transfer(accountIndex, mainACblace);
                    }
            }

        }
        while(e==0)
        {
           cout << "No Account in this bank !!\n";
           e++;
        }


    }

    void withdraw(int accountIndex)
    {
        double amount;
        cout << "How much?";
        cin >> amount;

        if (amount > 0 && amount <= accounts[accountIndex].balance)
        {
            accounts[accountIndex].balance -= amount;
            cout << "Withdrawal successful ! \n New balance: $" << accounts[accountIndex].balance << "\n";
            getData();
        }
        else
        {
            cout << "\nInvalid withdrawal amount. Amount must be greater than 0 and less than or equal to the balance.\n";
            withdraw(accountIndex);
        }
    }
    void transfer(int accountIndex, double MainACbl)
 {
            string transferId;
            cout << "\nEnter transfer AC Number:\n";
            cin>>transferId;
            matchData(transferId, accountIndex, MainACbl);
            cout<< "\n";
            getData();
 }
 int exit()
 {
   return 0;
 }
};
int main()
{
    BankAccount B;
    B.getData();
    return 0;
}