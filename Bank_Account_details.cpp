// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <iomanip>
#include<bits/stdc++.h>
using namespace std;

class Transaction {
private:
    double amount;
    string mode;

public:
    Transaction(double amount, const string& mode = "deposit") : amount(amount), mode(mode) {}

    double getAmount() const { return amount; }
    string getMode() const { return mode; }
};

class Customer {
private:
      string name;
    int accountNumber;
    double balance;
      vector<double> openingBalance;
      vector<double> closingBalance;
      vector<Transaction> transactions;

public:
    Customer(const string& name, int accountNumber, double initialAmount)
        : name(name), accountNumber(accountNumber), balance(initialAmount) {
        openingBalance.push_back(0.0);
        closingBalance.push_back(initialAmount);
        transactions.push_back(Transaction(initialAmount));
    }

    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        transactions.push_back(Transaction(amount, "deposit"));
        openingBalance.push_back(balance);
        balance += amount;
        closingBalance.push_back(balance);
        cout << amount << " deposited to A/C Number " << accountNumber << ".\n";
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            transactions.push_back(Transaction(amount, "withdraw"));
            openingBalance.push_back(balance);
            balance -= amount;
            closingBalance.push_back(balance);
            cout << amount << " withdrawn from A/C Number " << accountNumber << ".\n";
        } else {
            cout << "Transaction unsuccessful. Available balance is " << balance
                      << " but transaction amount was " << amount << ".\n";
        }
    }

    void getTransactionsDetails() const {
          cout << setw(20) << "Opening Balance"
                  << setw(20) << "Transaction Mode"
                  << setw(20) << "Transaction Amount"
                  << setw(20) << "Closing Balance\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            cout << setw(20) << openingBalance[i]
                      << setw(20) << transactions[i].getMode()
                      << setw(20) << transactions[i].getAmount()
                      << setw(20) << closingBalance[i] << "\n";
        }
    }
};

class Branch {
private:
    string name;
      vector<Customer> customers;

public:
    Branch(const   string& name) : name(name) {}

      string getName() const { return name; }

      vector<Customer>& getCustomers() { return customers; }

    void addNewCustomer(const   string& customerName, int customerAccountNumber, double initialAmount) {
        if (findCustomer(customerAccountNumber) == nullptr) {
            customers.push_back(Customer(customerName, customerAccountNumber, initialAmount));
              cout << "Customer added successfully.\n";
        } else {
              cout << "Customer with A/C Number " << customerAccountNumber << " already exists.\n";
        }
    }

    void addNewCustomer(const Customer& customer) {
        if (findCustomer(customer.getAccountNumber()) == nullptr) {
            customers.push_back(customer);
              cout << "Customer added successfully.\n";
        } else {
              cout << "Customer with A/C Number " << customer.getAccountNumber() << " already exists.\n";
        }
    }

    Customer* findCustomer(int customerAccountNumber) {
        for (auto& customer : customers) {
            if (customer.getAccountNumber() == customerAccountNumber) {
                return &customer;
            }
        }
        return nullptr;
    }

    void getCustomersList(bool showTransactions = false) const {
          cout << "\nCustomers in branch (" << name << ")\n";
          cout <<   setw(20) << "Name"
                  <<   setw(20) << "A/C Number"
                  <<   setw(20) << "Balance\n";
        for (const auto& customer : customers) {
              cout <<   setw(20) << customer.getName()
                      <<   setw(20) << customer.getAccountNumber()
                      <<   setw(20) << customer.getBalance() << "\n";
            if (showTransactions) {
                cout<<"Transactions details are.....\n";
                customer.getTransactionsDetails();
                  cout << "\n";
            }
        }
    }

    void getCustomersList(const   string& customerName) const {
          cout << "\nSearching for customers with the name " << customerName << " in branch (" << name << "):\n";
          cout <<   setw(20) << "Name"
                  <<   setw(20) << "A/C Number"
                  <<   setw(20) << "Balance\n";
        for (const auto& customer : customers) {
            if (customer.getName() == customerName) {
                  cout <<   setw(20) << customer.getName()
                          <<   setw(20) << customer.getAccountNumber()
                          <<   setw(20) << customer.getBalance() << "\n";
            }
        }
    }

    void withdraw(int customerAccountNumber, double amount) {
        Customer* existingCustomer = findCustomer(customerAccountNumber);
        if (existingCustomer != nullptr) {
            existingCustomer->withdraw(amount);
        } else {
              cout << "\nCustomer not found with the A/C Number(" << customerAccountNumber << ")\n";
        }
    }

    void deposit(int customerAccountNumber, double amount) {
        Customer* existingCustomer = findCustomer(customerAccountNumber);
        if (existingCustomer != nullptr) {
            existingCustomer->deposit(amount);
        } else {
              cout << "\nCustomer not found with the A/C Number(" << customerAccountNumber << ")\n";
        }
    }

    void removeCustomer(int customerAccountNumber) {
        auto it =   remove_if(customers.begin(), customers.end(),
                                 [customerAccountNumber](const Customer& customer) {
                                     return customer.getAccountNumber() == customerAccountNumber;
                                 });
        if (it != customers.end()) {
            customers.erase(it, customers.end());
              cout << "Customer with A/C Number " << customerAccountNumber << " removed.\n";
        } else {
              cout << "Customer with A/C Number " << customerAccountNumber << " does not exist.\n";
        }
    }
};

class Bank {
private:
      string name;
      vector<Branch> branches;

public:
    Bank(const   string& name) : name(name) {}

      string getName() const { return name; }

    void addBranch(const   string& branchName) {
        if (findBranch(branchName) == nullptr) {
            branches.push_back(Branch(branchName));
              cout << "Branch (" << branchName << ") added successfully.\n";
        } else {
              cout << "Branch (" << branchName << ") already exists.\n";
        }
    }

    void addBranch(const Branch& branch) {
        if (findBranch(branch.getName()) == nullptr) {
            branches.push_back(branch);
              cout << "Branch (" << branch.getName() << ") added successfully.\n";
        } else {
              cout << "Branch (" << branch.getName() << ") already exists.\n";
        }
    }

    Branch* findBranch(const string & branchName) {
        for (auto& branch : branches) {
            if (branch.getName() == branchName) {
                return &branch;
            }
        }
        return nullptr;
    }

    void addCustomer(const   string& branchName, const   string& customerName, int customerAccountNumber, double amount) {
        Branch* existingBranch = findBranch(branchName);
        if (existingBranch != nullptr) {
            existingBranch->addNewCustomer(customerName, customerAccountNumber, amount);
        } else {
              cout << "A/C creation is unsuccessful. Branch " << branchName << " doesn't exist.\n";
        }
    }

    void addCustomer(const   string& branchName, const Customer& customer) {
        Branch* existingBranch = findBranch(branchName);
        if (existingBranch != nullptr) {
            existingBranch->addNewCustomer(customer);
              cout << "A/C created successfully.\n";
        } else {
              cout << "A/C creation is unsuccessful. Branch " << branchName << " does not exist.\n";
        }
    }

    void getCustomersList(bool showTransactions = false) const {
        for (const auto& branch : branches) {
            branch.getCustomersList(showTransactions);
        }
    }

    void getCustomersListByCustomerName(const   string& customerName) const {
        for (const auto& branch : branches) {
            branch.getCustomersList(customerName);
        }
    }

    void viewBranchSummary(const   string& branchName) {
        Branch* branch = findBranch(branchName);
        if (branch != nullptr) {
            int customerCount = branch->getCustomers().size();
            double totalBalance = 0.0;
            for (const auto& customer : branch->getCustomers()) {
                totalBalance += customer.getBalance();
            }
              cout << "\nBranch Summary for " << branchName << ":\n";
              cout << "Number of Customers: " << customerCount << "\n";
              cout << "Total Balance: " << totalBalance << "\n";
        } else {
              cout << "Branch " << branchName << " does not exist.\n";
        }
    }

    void updateCustomerInfo(const   string& branchName, int customerAccountNumber, const   string& newCustomerName) {
        Branch* branch = findBranch(branchName);
        if (branch != nullptr) {
            Customer* customer = branch->findCustomer(customerAccountNumber);
            if (customer != nullptr) {
                customer->setName(newCustomerName);
                  cout << "Customer information updated successfully.\n";
            } else {
                  cout << "Customer with A/C Number " << customerAccountNumber << " not found.\n";
            }
        } else {
              cout << "Branch " << branchName << " does not exist.\n";
        }
    }

    void deleteCustomer(const   string& branchName, int customerAccountNumber) {
        Branch* branch = findBranch(branchName);
        if (branch != nullptr) {
            branch->removeCustomer(customerAccountNumber);
        } else {
              cout << "Branch " << branchName << " does not exist.\n";
        }
    }

    void deleteBranch(const   string& branchName) {
        auto it =   remove_if(branches.begin(), branches.end(),
                                 [branchName](const Branch& branch) {
                                     return branch.getName() == branchName;
                                 });
        if (it != branches.end()) {
            branches.erase(it, branches.end());
              cout << "Branch (" << branchName << ") removed successfully.\n";
        } else {
              cout << "Branch (" << branchName << ") does not exist.\n";
        }
    }

    void transferFunds(const string& fromBranchName, int fromAccountNumber,
                       const string& toBranchName, int toAccountNumber, double amount) {
        Branch* fromBranch = findBranch(fromBranchName);
        Branch* toBranch = findBranch(toBranchName);

        if (fromBranch != nullptr && toBranch != nullptr) {
            Customer* fromCustomer = fromBranch->findCustomer(fromAccountNumber);
            Customer* toCustomer = toBranch->findCustomer(toAccountNumber);

            if (fromCustomer != nullptr && toCustomer != nullptr) {
                if (fromCustomer->getBalance() >= amount) {
                    fromCustomer->withdraw(amount);
                    toCustomer->deposit(amount);
                      cout << "Funds transferred successfully from A/C " << fromAccountNumber 
                              << " to A/C " << toAccountNumber << ".\n";
                } else {
                      cout << "Transfer failed. Insufficient balance in A/C " << fromAccountNumber << ".\n";
                }
            } else {
                  cout << "Transfer failed. One or both accounts do not exist.\n";
            }
        } else {
              cout << "Transfer failed. One or both branches do not exist.\n";
        }
    }
};

int main() {
    Bank bank("SBI");

    bank.addBranch("LMP");

    bank.addCustomer("LMP", "Amar", 123456, 800.0);
    bank.addCustomer("LMP", "Gopal", 12345, 0.0);
    bank.addCustomer("LMP", "Amar", 78956, 100.0);

    Branch* branchPtr = bank.findBranch("LMP");
    if (branchPtr) {
        branchPtr->deposit(123456, 2000.0);
        branchPtr->withdraw(123456, 300.0);
    }

    Customer customer1("Amar", 123456, 0.0);
    bank.addCustomer("LMP", customer1);

    Customer customer2("DEEP", 789456, 0.0);
    bank.addCustomer("LMP", customer2);

    bank.getCustomersList();
      cout << "\n";
    bank.getCustomersListByCustomerName("Amar");
      cout << "\n";
    bank.getCustomersList(true);
      cout << "\n";

      cout << "...........\n";
    bank.getCustomersList();
      cout << "...........\n";
    bank.addBranch("LKO");
      cout << "...........\n";
    bank.getCustomersListByCustomerName("Gopal");

    // Test new functionalities
    bank.viewBranchSummary("LMP");
    bank.transferFunds("LMP", 123456, "LMP", 789456, 500.0);
    bank.updateCustomerInfo("LMP", 123456, "Amar DEEP");
    bank.deleteCustomer("LMP", 789456);
    bank.deleteBranch("LKO");

    return 0;
}
