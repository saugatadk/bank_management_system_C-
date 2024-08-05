#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <conio.h>

using namespace std;

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

class BankAccount {
public:
    int account_number;
    char account_holder[50];
    char password[50];
    int pin;
    float balance;

    BankAccount() {
        account_number = 0;
        pin = 0;
        balance = 0.0f;
        strcpy(account_holder, "");
        strcpy(password, "");
    }
};

class Bank {
private:
    BankAccount acc[100];
    int count;
    int num;
    int current_user_index;

public:
    Bank() : count(0), num(0), current_user_index(-1) {
        clearAccountData();
    }

    void loginMenu();
    void homeMenu();
    void create();
    void deposit();
    void withdraw();
    void transfer();
    void display();
    void transactionDetail();
    void adminMenu();
    void allTransactionDetails();
    void confidential();
    void deleteAccount();
    void clearAccountData();
    void divider();
    void logout();

    void mainMenu();
};

void Bank::divider() {
    for (int i = 0; i < 40; i++) {
        cout << "-";
    }
}

void Bank::clearAccountData() {
    ofstream ptr("bank.txt");
    ptr.close();
    ofstream ptr1("account.txt");
    ptr1.close();
}

void Bank::mainMenu() {
    while (true) {
        loginMenu();
        if (current_user_index != -1) {
            homeMenu();
        }
    }
}

void Bank::loginMenu() {
    int choice;

    while (true) {
        system("cls");
        cout << CYAN << "\n BANK MANAGEMENT SYSTEM \n" << RESET;
        divider();
        cout << GREEN << "\n1. Login\n";
        cout << "2. Sign Up\n" << BLUE;
        cout << "3. Admin Login\n" << RED;
        cout << "4. Exit\n" << RESET;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            for (int attempts = 0; attempts < 3; attempts++) {
                int acc_num;
                char acc_pass[50];
                char ch;
                cout << CYAN << "\nLOGIN\n" << RESET;
                divider();
                cout << endl;
                cout << RED "ONLY "<< 3-attempts <<" ATTEMPTS!" << endl << RESET;
                cout << "\nEnter account number: ";
                cin >> acc_num;
                cout << "Enter password: ";
                cin.ignore();
                cin.getline(acc_pass, 50);
                cout << "Press 'y' to continue and 'n' to go to main menu: ";
                cin >> ch;
                if(ch=='n'){
                    break;
                }

                for (int i = 0; i < num; i++) {
                    if (acc[i].account_number == acc_num && strcmp(acc[i].password, acc_pass) == 0) {
                        current_user_index = i;
                        return;
                    }
                }
                cout << RED << "Invalid credentials. Try again.\n" << RESET;
            }
            cout << RED << "Too many failed attempts. Returning to main menu.\n" << RESET;
            break;
        case 2:
            system("cls");
            create();
            break;
        case 3:
            system("cls");
            adminMenu();
            break;
        case 4:
            system("cls");
            cout << CYAN << "Exiting the program..." << RESET;
            exit(0);
            break;
        default:
            cout << RED << "INVALID INPUT.\n PLEASE TRY AGAIN\n" << RESET;
        }
    }
}

void Bank::homeMenu() {
    int choice;

    while (true) {
        system("cls");
        cout << CYAN << "\n ACCOUNT HOME MENU \n" << RESET;
        divider();
        cout << GREEN << "\n1. Deposit Funds\n";
        cout << "2. Withdraw Funds\n";
        cout << "3. Transfer Funds\n" << BLUE;
        cout << "4. Display Account Details\n";
        cout << "5. Transaction Details\n" << RED;
        cout << "6. Delete Account\n";
        cout << "7. Logout\n" << RESET;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            deposit();
            break;
        case 2:
            system("cls");
            withdraw();
            break;
        case 3:
            system("cls");
            transfer();
            break;
        case 4:
            system("cls");
            display();
            break;
        case 5:
            system("cls");
            transactionDetail();
            break;
        case 6:
            system("cls");
            deleteAccount();
            if (current_user_index == -1) {
                return;
            }
            break;
        case 7:
            system("cls");
            logout();
            return;
        default:
            cout << RED << "INVALID INPUT.\n PLEASE TRY AGAIN\n" << RESET;
        }
    }
}

void Bank::logout() {
    current_user_index = -1;
    cout << GREEN << "Logged out successfully.\n" << RESET;
    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::create() {
    BankAccount newAccount;

    if (num >= 100) {
        cout << RED << "Cannot create more accounts. The maximum limit has been reached.\n" << RESET;
        return;
    }

    ofstream ptr("bank.txt", ios::app);
    ofstream ptr1("account.txt", ios::app);

    system("cls");
    cout << CYAN << "\nACCOUNT CREATION\n" << RESET;
    divider();
    cout << "\nEnter Account Number: ";
    cin >> newAccount.account_number;
    cout << "Enter Account Holder's Name: ";
    cin.ignore();
    cin.getline(newAccount.account_holder, 50);
    cout << "Enter Account Password: ";
    cin.getline(newAccount.password, 50);
    cout << "Enter 4-digit Pin For Transaction: ";
    cin >> newAccount.pin;
    cout << "Enter Initial Balance: ";
    cin >> newAccount.balance;

    acc[num] = newAccount;
    num++;

    ptr1 << "Account Number: " << newAccount.account_number << "\nAccount Holder's Name: " << newAccount.account_holder << "\nAccount Password: " << newAccount.password << "\n4-digit Pin: " << newAccount.pin << "\nInitial balance: " << newAccount.balance << "\n\n";
    ptr << "Initial balance for Account " << newAccount.account_number << " has been set to NPR " << newAccount.balance << "\n\n";
    ptr1.close();
    ptr.close();

    cout << GREEN << "\nAccount created successfully!\n" << RESET;
    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::deposit() {
    system("cls");
    cout << CYAN << "\nDEPOSITING AMOUNT\n" << RESET;
    divider();
    time_t tm;
    time(&tm);
    ofstream ptr("bank.txt", ios::app);
    float amt;

    cout << "\nEnter the amount to deposit: ";
    cin >> amt;

    acc[current_user_index].balance += amt;
    cout << GREEN << "Deposit Successful.\nUpdated balance: " << acc[current_user_index].balance << "\n" << RESET;
    ptr << "Your " << acc[current_user_index].account_number << "## has been Credited by NPR " << amt << " on " << ctime(&tm);
    ptr << "Remarks: Deposit. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n";
    ptr.close();
    count++;

    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::withdraw() {
    float amt;
    int pin;
    time_t tm;
    time(&tm);
    ofstream ptr("bank.txt", ios::app);

    system("cls");
    cout << CYAN << "\nWITHDRAWING AMOUNT\n" << RESET;
    divider();
    cout << endl;
    cout << "Enter amount to withdraw: ";
    cin >> amt;
    cout << "Enter your 4-digit pin: ";
    cin >> pin;

    if (acc[current_user_index].pin == pin) {
        if (amt > acc[current_user_index].balance) {
            cout << "Insufficient Balance.";
        } else {
            acc[current_user_index].balance -= amt;
            cout << GREEN << "Withdrawal Successful!\n";
            cout << "Updated balance is: " << acc[current_user_index].balance << "\n" << RESET;
        }
    } else {
        cout << RED << "INVALID PIN!\n" << RESET;
    }
    ptr << "Your " << acc[current_user_index].account_number << "## has been Debited by NPR " << amt << " on " << ctime(&tm);
    ptr << "Remarks: Withdraw. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n";
    ptr.close();
    count++;

    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::display() {
    system("cls");
    cout << CYAN << "\nACCOUNT DETAILS\n" << RESET;
    divider();
    cout << endl;
    cout << "Account Number: " << acc[current_user_index].account_number << "\n";
    cout << "Account Holder: " << acc[current_user_index].account_holder << "\n";
    cout << "Account Balance: " << acc[current_user_index].balance << "\n" << RESET;

    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::transfer() {
    int acc_rec;
    float amt;
    int pin;
    bool found = false;

    time_t tm;
    time(&tm);
    ofstream ptr("bank.txt", ios::app);

    system("cls");
    cout << CYAN << "\nTRANSFERRING MONEY\n" << RESET;
    divider();
    cout << endl;
    cout << "Enter the account number of receiver: ";
    cin >> acc_rec;
    cout << "Enter amount to transfer: ";
    cin >> amt;
    cout << "Enter your 4-digit pin: ";
    cin >> pin;

    if (acc[current_user_index].pin == pin) {
        if (amt > acc[current_user_index].balance) {
            cout << RED << "Insufficient Balance." << RESET;
        } else {
            acc[current_user_index].balance -= amt;
            cout << GREEN << "Transfer Successful to Account number " << acc_rec << ".\n";
            cout << "Updated balance is: " << acc[current_user_index].balance << "\n" << RESET;

            ptr << "Your " << acc[current_user_index].account_number << "## has been Debited by NPR " << amt << " on " << ctime(&tm);
            ptr << "Remarks: Transfer to acc " << acc_rec << "##. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n";
            count++;

            for (int i = 0; i < num; i++) {
                if (acc[i].account_number == acc_rec) {
                    acc[i].balance += amt;
                    ptr << "Your " << acc_rec << "## has been Credited by NPR " << amt << " on " << ctime(&tm);
                    ptr << "Remarks: Transfer from acc " << acc[current_user_index].account_number << "##. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n";
                    ptr.close();
                    break;
                }
            }
        }
    } else {
        cout << RED << "INVALID PIN!\n" << RESET;
    }

    cout << "\n";
    cout << "Press any key...";
    getch();
}

void Bank::transactionDetail() {
    ifstream ptr("bank.txt");

    system("cls");
    cout << CYAN << "\nTRANSACTION DETAILS\n" << RESET;
    divider();

    cout << "\nTOTAL TRANSACTIONS DONE: " << count << "\n\n";
    char ch;
    if (!(ptr >> ch)) {
        cout << RED << "No recent transactions\n" << RESET;
    } else {
        ptr.unget();
        while (ptr.get(ch)) {
            cout << ch;
        }
    }
    ptr.close();
    cout << "Press any key...";
    getch();
}

void Bank::adminMenu() {
    int pass;
    cout << CYAN << "\nADMIN LOGIN\n" << RESET;
    divider();
    cout << endl;
    cout << "Enter admin password: ";
    cin >> pass;

    if (pass == 404) {
        while (true) {
            int choice;

            system("cls");
            cout << CYAN << "\n ADMIN MENU \n" << RESET;
            divider();
            cout << GREEN << "\n1. View All Transaction Details\n";
            cout << "2. View Confidential Data\n" << RED;
            cout << "3. Logout\n" << RESET;

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                system("cls");
                allTransactionDetails();
                break;
            case 2:
                system("cls");
                confidential();
                break;
            case 3:
                return;
            default:
                cout << RED << "INVALID INPUT.\n PLEASE TRY AGAIN\n" << RESET;
            }
        }
    } else {
        cout << RED << "ACCESS DENIED!\n" << RESET;
        cout << "\n";
        cout << "Press any key...";
        getch();
    }
}

void Bank::allTransactionDetails() {
    ifstream ptr("bank.txt");

    system("cls");
    cout << CYAN << "\nALL TRANSACTION DETAILS\n" << RESET;
    divider();

    cout << "\nTOTAL TRANSACTIONS DONE: " << count << "\n\n";
    char ch;
    if (!(ptr >> ch)) {
        cout << RED << "No recent transactions\n" << RESET;
    } else {
        ptr.unget();
        while (ptr.get(ch)) {
            cout << ch;
        }
    }
    ptr.close();
    cout << "Press any key...";
    getch();
}

void Bank::confidential() {
    ifstream ptr1("account.txt");

    system("cls");
    cout << CYAN << "\nCONFIDENTIAL DATA\n" << RESET;
    divider();

    int pass;
    cout << "\nEnter password for ACCESS: ";
    cin >> pass;
    if (pass == 404) {
        char ch;
        if (!(ptr1 >> ch)) {
            cout << RED << "No data available\n" << RESET;
        } else {
            ptr1.unget();
            while (ptr1.get(ch)) {
                cout << ch;
            }
        }
        ptr1.close();
    } else {
        cout << RED << "ACCESS DENIED!\n" << RESET;
    }
    cout << "Press any key...";
    getch();
}

void Bank::deleteAccount() {
    int acc_num;
    cout << CYAN << "Enter account number to delete: " << RESET;
    cin >> acc_num;
    int found = -1;

    for (int i = 0; i < num; i++) {
        if (acc[i].account_number == acc_num) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < num - 1; i++) {
            acc[i] = acc[i + 1];
        }
        num--;
        cout << "Account " << acc_num << " deleted successfully!\n";

        if (acc[current_user_index].account_number == acc_num) {
            current_user_index = -1;
            logout();
        }
    } else {
        cout << RED << "Account not found. Please check the account number.\n" << RESET;
    }

    cout << "\n";
    cout << "Press any key...";
    getch();
}

int main() {
    Bank bank;
    bank.mainMenu();
    return 0;
}
