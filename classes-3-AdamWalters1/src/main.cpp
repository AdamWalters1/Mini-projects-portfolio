#include "bankAccount.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void menu();
void submenu();
int search(bankAccount list[], int length, int acctNum);
void addCustomer(bankAccount list[], int& length);
void processCustomer(bankAccount list[], int length, int acctNum);
void printCustomersData(bankAccount list[],int length);

int main(){
    bankAccount customersList[10];

    int choice; 
    int numOfCustomers = 0;
    int acctNumber;
    char discard;

    cout << fixed << showpoint << setprecision(2);

    menu();
    cin >> choice;
    cin.get(discard);
    cout << endl;

    while(choice != 9){
        switch(choice){
            case 1:
                if(numOfCustomers <10)
                    addCustomer(customersList, numOfCustomers);
                else
                    cout << "Cannot add any new customer. List is full. " << endl;
                    break;
            case 2:
                cout << "Enter in your account number: ";
                cin >> acctNumber;
                cout << endl;

                processCustomer(customersList, numOfCustomers,acctNumber);
                break;
            case 3:
                printCustomersData(customersList,numOfCustomers);
                break;
            default:cout << "Invalid choice." << endl;

        }
        menu();
        cin >> choice;
        cout << endl;
    }
    return 0;
}

void menu(){
    cout << "1: Enter 1 to add a new customer." << endl;
    cout << "2 :Enter 2 for an existing customer." << endl;
    cout << "3: Enter 3 to print customers data." << endl;
    cout << "9: Enter 9 to exit the program." << endl;
}

void submenu(){
    cout << "1: Enter 1 to make a deposit." << endl;
    cout << "2: Enter 2 to make a withdrawl." << endl;
    cout << "3: Enter 3 to check balance." << endl;
    cout << "9: Enter 9 to exit." << endl;
}

int search(bankAccount list[], int length, int acctNum){
    for (int i = 0;i<length;i++)
        if(list[i].getAccountNumber()==acctNum)
            return i;
    return -1;
}


void addCustomer(bankAccount list[], int& length){
    string name;
    string acctType;
    double deposit;
    double interestRate;

    if (length <10){
        cout << "Enter customer's name: ";
        getline(cin, name);
        cout << endl;

        cout << "Enter account type (checking/savings)";
        cin >> acctType;

        cout << "Enter amount to be deposited to open account: ";
        cin >> deposit;
        cout << endl;

        cout << "Enter interest rate (as a percent): ";
        cin >> interestRate;
        cout << endl;

        list[length++].setdata(name,acctType,deposit,interestRate);
    }

    else{
        cout << "Customers' list is full. Cannot add another customer." << endl;
    }
}
void processCustomer(bankAccount list[], int length, int acctNum){
    double amount;
    int index = search(list,length,acctNum);
    if (index != -1){
        submenu();
        int selection;
        cin >> selection;
        cout << endl;

        while(selection != 9){
            switch(selection){
                case 1:
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    cout << endl;
                    list[index].deposit(amount);
                    cout << endl;
                    break;
                case 2:
                    cout << "Enter withdraw amount ";
                    cin >> amount;
                    cout << endl;
                    list[index].withdraw(amount);
                    cout << endl;
                    break;
                case 3:
                    list[index].print();
                    break;
                default:
                    cout << "Invalid Selection." << endl;

            }
            submenu();
            cin >> selection;
            cout << endl;
        }
    }

    else
        cout << "Invalid Customer" << endl;
}
void printCustomersData(bankAccount list[],int length){
    for(int i =0; i< length ; i++){
        list[i].print();
        cout << " ---------------------------" << endl;
    }
}
