#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to manage Customer details
class Customer {
public:
    string name, customerID, address, phone;

    Customer(string n, string id, string addr, string ph)
        : name(n), customerID(id), address(addr), phone(ph) {}
};

// Class to manage Account details
class Account {
public:
    string accountNumber, customerID, accountType;
    double balance;

    Account(string accNum, string custID, string accType, double bal)
        : accountNumber(accNum), customerID(custID), accountType(accType), balance(bal) {}
};

// Class to manage Transaction details
class Transaction {
public:
    string accountNumber, transactionType;
    double amount;

    Transaction(string accNum, string type, double amt)
        : accountNumber(accNum), transactionType(type), amount(amt) {}
};

// Banking system class to handle services
class BankingSystem {
private:
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;

public:
    void AddCustomer() {
        string name, id, addr, phone;
        cout << "Enter Customer Name: ";
        cin >> name;
        cout << "Enter Customer ID: ";
        cin >> id;
        cout << "Enter Address: ";
        cin >> addr;
        cout << "Enter Phone: ";
        cin >> phone;

        customers.push_back(Customer(name, id, addr, phone));
        cout << "Customer added successfully!\n";
    }

   void ViewCustomers() {
    if (customers.empty()) {
        cout << "No customers available.\n";
        return;
    }
    cout << "\nCustomer List:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << "Name: " << customers[i].name
             << ", ID: " << customers[i].customerID
             << ", Address: " << customers[i].address
             << ", Phone: " << customers[i].phone << "\n";
    }
}
    void CreateAccount() {
        string accNum, custID, accType;
        double bal;
        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Enter Customer ID: ";
        cin >> custID;
        cout << "Enter Account Type (Savings/Current): ";
        cin >> accType;
        cout << "Enter Initial Balance: ";
        cin >> bal;

        accounts.push_back(Account(accNum, custID, accType, bal));
        cout << "Account created successfully!\n";
    }

    void ViewAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }
    cout << "\nAccount List:\n";
    
    // Using indexed for-loop
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << "Account Number: " << accounts[i].accountNumber
             << ", Customer ID: " << accounts[i].customerID
             << ", Account Type: " << accounts[i].accountType
             << ", Balance: " << accounts[i].balance << "\n";
    }
}

    void Deposit() {
    string accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    // Using indexed for-loop
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == accNum) {
            accounts[i].balance += amount;
            transactions.push_back(Transaction(accNum, "Deposit", amount));
            cout << "Deposit successful! New Balance: " << accounts[i].balance << "\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

 void Withdraw() {
    string accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    // Using indexed for-loop
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == accNum) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                transactions.push_back(Transaction(accNum, "Withdraw", amount));
                cout << "Withdrawal successful! New Balance: " << accounts[i].balance << "\n";
            } else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

    void Transfer() {
    string sourceAcc, destAcc;
    double amount;
    cout << "Enter Source Account Number: ";
    cin >> sourceAcc;
    cout << "Enter Destination Account Number: ";
    cin >> destAcc;
    cout << "Enter Amount to Transfer: ";
    cin >> amount;

    Account *source =NULL , *destination = NULL;

    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == sourceAcc) {
            source = &accounts[i];
        }
        if (accounts[i].accountNumber == destAcc) {
            destination = &accounts[i];
        }
    }

    if (source && destination) {
        if (source->balance >= amount) {
            source->balance -= amount;
            destination->balance += amount;

            transactions.push_back(Transaction(sourceAcc, "Transfer Out", amount));
            transactions.push_back(Transaction(destAcc, "Transfer In", amount));
            cout << "Transfer successful! New Balance of Source Account: " << source->balance << "\n";
        } else {
            cout << "Insufficient balance in source account.\n";
        }
    } else {
        cout << "One or both accounts not found.\n";
    }
}

  void ViewTransactions() {
    if (transactions.empty()) {
        cout << "No transactions available.\n";
        return;
    }
    cout << "\nTransaction History:\n";
    for (size_t i = 0; i < transactions.size(); ++i) {
        cout << "Account: " << transactions[i].accountNumber
             << ", Type: " << transactions[i].transactionType
             << ", Amount: " << transactions[i].amount << "\n";
    }
}


void ViewAccountInfo() {
    string accNum;
    cout << "Enter Account Number to view details: ";
    cin >> accNum;

    // Find the account using a traditional loop
    bool found = false;
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == accNum) {
            found = true;
            cout << "\n--- Account Information ---\n";
            cout << "Account Number: " << accounts[i].accountNumber << "\n";
            cout << "Customer ID: " << accounts[i].customerID << "\n";
            cout << "Account Type: " << accounts[i].accountType << "\n";
            cout << "Balance: " << accounts[i].balance << "\n";

            // Display recent transactions for the account
            cout << "\nRecent Transactions:\n";
            for (size_t j = 0; j < transactions.size(); ++j) {
                if (transactions[j].accountNumber == accNum) {
                    cout << "Type: " << transactions[j].transactionType
                         << ", Amount: " << transactions[j].amount << "\n";
                }
            }
            return;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
    }
}

};
int main() {
    BankingSystem bank;
    int choice;

    do {
        cout << "\nBanking System Menu:";
        cout << "\n1. Add Customer\n2. View Customers\n3. Create Account\n4. View Accounts\n5. Deposit";
        cout << "\n6. Withdraw\n7. Transfer\n8. View Transactions\n9. View Account Info\n10. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bank.AddCustomer();
            break;
        case 2:
            bank.ViewCustomers();
            break;
        case 3:
            bank.CreateAccount();
            break;
        case 4:
            bank.ViewAccounts();
            break;
        case 5:
            bank.Deposit();
            break;
        case 6:
            bank.Withdraw();
            break;
        case 7:
            bank.Transfer();
            break;
        case 8:
            bank.ViewTransactions();
            break;
        case 9:
            bank.ViewAccountInfo();
            break;
        case 10:
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 10);

    return 0;
}


