#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ================= TRANSACTION CLASS =================
class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() const {
        cout << left << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << details << endl;
    }
};

// ================= ACCOUNT CLASS =================
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;

        transactions.push_back(
            Transaction("Deposit", amount, "Money deposited")
        );

        cout << "Deposit successful!\n";
        cout << "New Balance: Rs. " << balance << endl;
    }

    // Withdraw money
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction("Withdraw", amount, "Money withdrawn")
        );

        cout << "Withdrawal successful!\n";
        cout << "New Balance: Rs. " << balance << endl;

        return true;
    }

    // Add transfer transaction
    void addTransferTransaction(double amount, string details) {
        transactions.push_back(
            Transaction("Transfer", amount, details)
        );
    }

    // Display account information
    void displayAccount() const {
        cout << "\n========== ACCOUNT INFORMATION ==========\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Balance        : Rs. "
             << fixed << setprecision(2) << balance << endl;
    }

    // Display transaction history
    void displayTransactions() const {
        cout << "\n========== TRANSACTION HISTORY ==========\n";

        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        cout << left << setw(15) << "Type"
             << setw(12) << "Amount"
             << "Details" << endl;

        cout << "------------------------------------------\n";

        for (const auto &t : transactions) {
            t.display();
        }
    }
};

// ================= CUSTOMER CLASS =================
class Customer {
private:
    int customerId;
    string name;
    string phone;
    vector<Account> accounts;

public:
    Customer(int id, string n, string p) {
        customerId = id;
        name = n;
        phone = p;
    }

    int getCustomerId() const {
        return customerId;
    }

    // Create a new account
    void createAccount(int accountNumber) {
        accounts.push_back(Account(accountNumber));

        cout << "Account created successfully!\n";
        cout << "Account Number: " << accountNumber << endl;
    }

    // Find account
    Account* findAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }

        return nullptr;
    }

    // Display customer information
    void displayCustomer() const {
        cout << "\n========== CUSTOMER INFORMATION ==========\n";
        cout << "Customer ID : " << customerId << endl;
        cout << "Name        : " << name << endl;
        cout << "Phone       : " << phone << endl;

        cout << "\nAccounts:\n";

        if (accounts.empty()) {
            cout << "No accounts available.\n";
        } else {
            for (const auto &account : accounts) {
                cout << "Account No: "
                     << account.getAccountNumber()
                     << " | Balance: Rs. "
                     << fixed << setprecision(2)
                     << account.getBalance() << endl;
            }
        }
    }
};

// ================= BANKING SYSTEM =================
class BankingSystem {
private:
    vector<Customer> customers;
    int nextCustomerId = 1001;
    int nextAccountNumber = 5001;

public:

    // Create customer
    void createCustomer() {
        string name, phone;

        cout << "\n========== CREATE CUSTOMER ==========\n";

        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

        customers.push_back(
            Customer(nextCustomerId, name, phone)
        );

        cout << "Customer created successfully!\n";
        cout << "Customer ID: " << nextCustomerId << endl;

        nextCustomerId++;
    }

    // Create account
    void createAccount() {
        int customerId;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {

                customer.createAccount(nextAccountNumber);

                nextAccountNumber++;
                return;
            }
        }

        cout << "Customer not found!\n";
    }

    // Deposit
    void depositMoney() {
        int customerId, accountNumber;
        double amount;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {

                Account *account =
                    customer.findAccount(accountNumber);

                if (account != nullptr) {
                    cout << "Enter deposit amount: Rs. ";
                    cin >> amount;

                    account->deposit(amount);
                } else {
                    cout << "Account not found!\n";
                }

                return;
            }
        }

        cout << "Customer not found!\n";
    }

    // Withdraw
    void withdrawMoney() {
        int customerId, accountNumber;
        double amount;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {

                Account *account =
                    customer.findAccount(accountNumber);

                if (account != nullptr) {
                    cout << "Enter withdrawal amount: Rs. ";
                    cin >> amount;

                    account->withdraw(amount);
                } else {
                    cout << "Account not found!\n";
                }

                return;
            }
        }

        cout << "Customer not found!\n";
    }

    // Transfer money
    void transferMoney() {
        int fromCustomer, fromAccount;
        int toCustomer, toAccount;
        double amount;

        cout << "\nEnter Sender Customer ID: ";
        cin >> fromCustomer;

        cout << "Enter Sender Account Number: ";
        cin >> fromAccount;

        cout << "Enter Receiver Customer ID: ";
        cin >> toCustomer;

        cout << "Enter Receiver Account Number: ";
        cin >> toAccount;

        cout << "Enter amount to transfer: Rs. ";
        cin >> amount;

        Account *sender = nullptr;
        Account *receiver = nullptr;

        // Find sender account
        for (auto &customer : customers) {
            if (customer.getCustomerId() == fromCustomer) {
                sender = customer.findAccount(fromAccount);
            }

            if (customer.getCustomerId() == toCustomer) {
                receiver = customer.findAccount(toAccount);
            }
        }

        if (sender == nullptr) {
            cout << "Sender account not found!\n";
            return;
        }

        if (receiver == nullptr) {
            cout << "Receiver account not found!\n";
            return;
        }

        if (amount <= 0) {
            cout << "Invalid transfer amount!\n";
            return;
        }

        if (sender->getBalance() < amount) {
            cout << "Insufficient balance!\n";
            return;
        }

        // Withdraw from sender
        sender->withdraw(amount);

        // Deposit to receiver
        receiver->deposit(amount);

        // Add transfer records
        sender->addTransferTransaction(
            amount,
            "Transferred to A/C " +
            to_string(toAccount)
        );

        receiver->addTransferTransaction(
            amount,
            "Received from A/C " +
            to_string(fromAccount)
        );

        cout << "\nTransfer successful!\n";
    }

    // Display account information
    void showAccount() {
        int customerId, accountNumber;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {

                Account *account =
                    customer.findAccount(accountNumber);

                if (account != nullptr) {
                    account->displayAccount();
                } else {
                    cout << "Account not found!\n";
                }

                return;
            }
        }

        cout << "Customer not found!\n";
    }

    // Display transaction history
    void showTransactions() {
        int customerId, accountNumber;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {

                Account *account =
                    customer.findAccount(accountNumber);

                if (account != nullptr) {
                    account->displayTransactions();
                } else {
                    cout << "Account not found!\n";
                }

                return;
            }
        }

        cout << "Customer not found!\n";
    }

    // Display customer
    void showCustomer() {
        int customerId;

        cout << "\nEnter Customer ID: ";
        cin >> customerId;

        for (auto &customer : customers) {
            if (customer.getCustomerId() == customerId) {
                customer.displayCustomer();
                return;
            }
        }

        cout << "Customer not found!\n";
    }
};

// ================= MAIN FUNCTION =================
int main() {
    BankingSystem bank;
    int choice;

    do {
        cout << "\n\n====================================\n";
        cout << "       BANKING MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Funds\n";
        cout << "6. Account Information\n";
        cout << "7. Transaction History\n";
        cout << "8. Customer Information\n";
        cout << "9. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                bank.createCustomer();
                break;

            case 2:
                bank.createAccount();
                break;

            case 3:
                bank.depositMoney();
                break;

            case 4:
                bank.withdrawMoney();
                break;

            case 5:
                bank.transferMoney();
                break;

            case 6:
                bank.showAccount();
                break;

            case 7:
                bank.showTransactions();
                break;

            case 8:
                bank.showCustomer();
                break;

            case 9:
                cout << "\nThank you for using the Banking System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}