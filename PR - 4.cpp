#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance;

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance\n";
    }

    double getBalance() {
        return balance;
    }

    void setBalance(double bal) {
        balance = bal;
    }

    virtual void displayAccountInfo() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << accountHolderName;
        cout << "\nBalance: " << balance << endl;
    }

    virtual void calculateInterest() {
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = getBalance() * interestRate / 100;
        cout << "Savings Account Interest: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount <= getBalance() + overdraftLimit)
            setBalance(getBalance() - amount);
        else
            cout << "Overdraft limit exceeded\n";
    }

    void checkOverdraft(double amount) {
        if (amount > getBalance())
            cout << "Overdraft used\n";
        else
            cout << "No overdraft used\n";
    }
};

class FixedDepositAccount : public BankAccount {
    int term;

public:
    FixedDepositAccount(int accNo, string name, double bal, int months)
        : BankAccount(accNo, name, bal) {
        term = months;
    }

    void calculateInterest() override {
        double interest = getBalance() * 0.07 * term / 12;
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

int main() {
    BankAccount* account = NULL;
    int choice;

    do {
        cout << "\n1. Create Savings Account";
        cout << "\n2. Create Checking Account";
        cout << "\n3. Create Fixed Deposit Account";
        cout << "\n4. Deposit";
        cout << "\n5. Withdraw";
        cout << "\n6. Display Account Info";
        cout << "\n7. Calculate Interest";
        cout << "\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            double bal, rate;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            account = new SavingsAccount(accNo, name, bal, rate);
        }

        else if (choice == 2) {
            int accNo;
            string name;
            double bal, limit;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Overdraft Limit: ";
            cin >> limit;
            account = new CheckingAccount(accNo, name, bal, limit);
        }

        else if (choice == 3) {
            int accNo, term;
            string name;
            double bal;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Term (months): ";
            cin >> term;
            account = new FixedDepositAccount(accNo, name, bal, term);
        }

        else if (choice == 4 && account) {
            double amt;
            cout << "Enter deposit amount: ";
            cin >> amt;
            account->deposit(amt);
        }

        else if (choice == 5 && account) {
            double amt;
            cout << "Enter withdrawal amount: ";
            cin >> amt;
            account->withdraw(amt);
        }

        else if (choice == 6 && account) {
            account->displayAccountInfo();
        }

        else if (choice == 7 && account) {
            account->calculateInterest();
        }

    } while (choice != 8);

    delete account;
    return 0;
}

/*
	output:
	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 1
	Enter Account Number: 2344
	Enter Account Holder Name: Shyam
	Enter Initial Balance: 100000
	Enter Interest Rate: 20

	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 3
	Enter Account Number: 24359
	Enter Account Holder Name: Dwarkesh
	Enter Initial Balance: 200000
	Enter Term (months): 1
	
	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 4
	Enter deposit amount: 20000
	
	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 5
	Enter withdrawal amount: 20000
	
	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 7
	Fixed Deposit Interest: 1166.67
	
	1. Create Savings Account
	2. Create Checking Account
	3. Create Fixed Deposit Account
	4. Deposit
	5. Withdraw
	6. Display Account Info
	7. Calculate Interest
	8. Exit
	Enter choice: 8
	*/