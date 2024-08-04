#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // For rand()

using namespace std;

int total_saving_accounts = 0;
int total_current_accounts = 0;

class account {
public:
    string name_of_account_holder;
    string name_of_joint_account_holder;
    long long int account_number;
    int balance;
    string type_of_account;
    string pin;

public:
    // In case of single holder account
    account(string accholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
        name_of_joint_account_holder = "No Joint Holder in this account";
    }

    // In case of multiple holder account
    account(string accholdername, string jointholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        name_of_joint_account_holder = jointholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
    }
};

vector<account> accts;

void display_details(long long int accnum) {
    bool acc_exists = false;
    for (const auto& it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            cout << "\nAccount Number : " << it.account_number;
            cout << "\nAccount Holder Name : " << it.name_of_account_holder;
            cout << "\nJoint Holder Name : " << it.name_of_joint_account_holder;
            cout << "\nBalance in your account : " << it.balance;
            cout << "\nType of Account : " << it.type_of_account;
            return;
        }
    }
    cout << "Account doesn't exist with the given Account Number.";
}

bool create_account(vector<account>& accts) {
    string accholder_name;
    cout << "\nENTER YOUR DETAILS HERE : ";
    cout << "\nName of Account Holder : ";
    cin >> accholder_name;

    string str;
    cout << "\nDo you want to have a joint holder account? Type YES/NO : ";
    cin >> str;

    string joint_holder = "No Joint Holder in this account";
    if (str == "YES") {
        cout << "Enter the name of Joint Holder : ";
        cin >> joint_holder;
    }

    string pin;
    cout << "\nEnter the pin : ";
    cin >> pin;

    string typeofacc;
    cout << "\nEnter the type of account : ";
    int choice;
    cout << "1 - Savings Account\n";
    cout << "2 - Current Account\n";
    cout << "Enter your choice here : ";
    cin >> choice;
    typeofacc = (choice == 1) ? "Savings" : "Current";

    int balance;
    cout << "\nEnter the balance you want to have initially in your account : ";
    cin >> balance;

    // If it is savings account
    if (typeofacc == "Savings") {
        account ob(accholder_name, joint_holder, balance, typeofacc, pin);
        total_saving_accounts++;
        accts.push_back(ob);
        cout << "\nACCOUNT CREATED SUCCESSFULLY\n";
        display_details(ob.account_number);
        return true;
    }

    // If it is current account with sufficient balance
    if (typeofacc == "Current" && balance >= 10000) {
        account ob(accholder_name, joint_holder, balance, typeofacc, pin);
        total_current_accounts++;
        accts.push_back(ob);
        cout << "\nACCOUNT CREATED SUCCESSFULLY\n";
        display_details(ob.account_number);
        return true;
    }

    cout << "\nINSUFFICIENT BALANCE\n";
    return false;
}

bool change_pin() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string oldpin;
            cout << "Enter the old pin : ";
            cin >> oldpin;

            if (oldpin == it.pin) {
                string newpin;
                cout << "Enter new pin : ";
                cin >> newpin;
                it.pin = newpin;
                display_details(it.account_number);
                return true;
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }

    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool deposit_into_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string pinfordepo;
            cout << "Enter the pin : ";
            cin >> pinfordepo;

            if (pinfordepo == it.pin) {
                int deposit_amount;
                cout << "Enter the amount you want to deposit : ";
                cin >> deposit_amount;
                it.balance += deposit_amount;
                cout << "Your Updated details : ";
                display_details(it.account_number);
                return true;
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }

    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool withdraw_from_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string pinfordepo;
            cout << "Enter the pin : ";
            cin >> pinfordepo;

            if (pinfordepo == it.pin) {
                int withdrawl_amount;
                cout << "Enter the amount you want to withdraw : ";
                cin >> withdrawl_amount;

                if (it.balance - withdrawl_amount >= 0) {
                    it.balance -= withdrawl_amount;
                    cout << "Your Updated details : ";
                    display_details(it.account_number);
                    return true;
                } else {
                    cout << "Insufficient Balance";
                    return false;
                }
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }

    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool balance_inquiry() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;

    for (const auto& it : accts) {
        if (it.account_number == accnum) {
            cout << "The balance in your account is : " << it.balance;
            return true;
        }
    }

    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool close_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;

    for (auto it = accts.begin(); it != accts.end(); ++it) {
        if (it->account_number == accnum) {
            accts.erase(it);
            cout << "Account closed successfully.";
            return true;
        }
    }

    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool view_account_details() {
    if (accts.empty()) {
        cout << "No accounts to display.";
        return false;
    }

    for (const auto& it : accts) {
        display_details(it.account_number);
    }
    return true;
}

void admin_menu() {
    int option;
    cout << "\nChoose your option: ";
    cout << "\n1) View Total Number of Accounts";
    cout << "\n2) View Account Details";
    cout << "\nEnter your choice here : ";
    cin >> option;

    switch (option) {
        case 1:
            cout << "Total Number of Accounts : " << accts.size();
            break;
        case 2:
            view_account_details();
            break;
        default:
            cout << "Invalid Option";
            break;
    }
}

void user_menu() {
    int choice;
    do {
        cout << "\nChoose your option: ";
        cout << "\n1) Create a New Account";
        cout << "\n2) Change your pin";
        cout << "\n3) Deposit Money";
        cout << "\n4) Withdraw Money";
        cout << "\n5) Balance Inquiry";
        cout << "\n6) Close Account";
        cout << "\n7) Display Account Details";
        cout << "\n8) Exit";
        cout << "\nEnter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                create_account(accts);
                break;
            case 2:
                change_pin();
                break;
            case 3:
                deposit_into_account();
                break;
            case 4:
                withdraw_from_account();
                break;
            case 5:
                balance_inquiry();
                break;
            case 6:
                close_account();
                break;
            case 7: {
                long long int account_number;
                cout << "Enter the account number for details to be displayed : ";
                cin >> account_number;
                display_details(account_number);
                break;
            }
            case 8:
                return;
            default:
                cout << "Invalid choice, please try again.";
                break;
        }
    } while (choice != 8);
}

void welcome() {
    int choice;
    cout << "\nWELCOME TO BANKING SYSTEM";
    cout << "\n1) ADMINISTRATOR";
    cout << "\n2) USER";
    cout << "\n3) EXIT";
    cout << "\nEnter your choice : ";
    cin >> choice;

    switch (choice) {
        case 1:
            admin_menu();
            break;
        case 2:
            user_menu();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice, please try again.";
            break;
    }
}

int main() {
    welcome();
    return 0;
}
