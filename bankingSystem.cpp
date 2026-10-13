#include <iostream>
using namespace std;

class BankAccount
{
protected:
    string accountNumber;
    string accountHolderName;

private:
    double balance;

public:
    BankAccount(string accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

   void deposit(double amount)
    {
        if (amount > 0)
        {
            balance = balance + amount;
            cout << "Amount deposited successfully!\n";
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }

    virtual void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance = balance - amount;
            cout << "Amount withdrawn successfully!\n";
        }
        else
        {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    double getBalance()
    {
        return balance;
    }

    virtual void calculateInterest()
    {
        cout << "No interest for this account.\n";
    }

   void displayAccountInfo()
    {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << accountHolderName;
        cout << "\nBalance: " << balance << endl;
    }

    virtual ~BankAccount() {}
};


class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(string no, string name, double bal)
        : BankAccount(no, name, bal) {}

    void calculateInterest() override
    {
        double interest = getBalance() * 4 / 100;
        cout << "Savings Interest (4%): " << interest << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(string no, string name, double bal, double limit)
        : BankAccount(no, name, bal)
    {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override
    {
        if (amount > 0 && amount <= getBalance() + overdraftLimit)
        {
            double newBalance = getBalance() - amount;
            if (amount <= getBalance())
            {
                BankAccount::withdraw(amount);
            }
            else
            {
                double remaining = getBalance();
                if (remaining > 0)
                    BankAccount::withdraw(remaining);
                cout << "Overdraft used: "
                     << amount - remaining << endl;
            }
        }
        else
        {
            cout << "Overdraft limit exceeded!\n";
        }
    }

    void checkOverdraft()
    {
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};
class FixedDepositAccount : public BankAccount
{
private:
    int term;

public:
    FixedDepositAccount(string no, string name,
                        double bal, int months)
        : BankAccount(no, name, bal)
    {
        term = months;
    }

    void calculateInterest() override
    {
        double interest = getBalance() * 6 * term / 1200;
        cout << "Fixed Deposit Interest (6% annually): "
             << interest << endl;
    }
};

int main()
{
    SavingsAccount savings("101", "Khushi", 10000);
    CheckingAccount checking("102", "Riya", 5000, 2000);
    FixedDepositAccount fixed("103", "Priya", 20000, 12);

    BankAccount *accounts[3] = {&savings, &checking, &fixed};

    int choice, accountChoice;
    double amount;

    do
    {
        cout << "\n===== BANKING SYSTEM =====\n";
        cout << "1. Savings Account\n";
        cout << "2. Checking Account\n";
        cout << "3. Fixed Deposit Account\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> accountChoice;

        if (accountChoice == 4)
        {
            cout << "Thank you for using our bank!\n";
            break;
        }

        if (accountChoice < 1 || accountChoice > 3)
        {
            cout << "Invalid account choice!\n";
            continue;
        }

        BankAccount *account = accounts[accountChoice - 1];

        cout << "\n1. Display Account Information\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Calculate Interest\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account->displayAccountInfo();
            if (accountChoice == 2)
                checking.checkOverdraft();
            break;

        case 2:
            cout << "Enter deposit amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 3:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 4:
            account->calculateInterest();
            break;

        case 5:
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (true);

    return 0;
}