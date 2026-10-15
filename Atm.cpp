#include <iostream>
#include <iomanip>

using namespace std;

// Function declarations (الدوال المستخدمة)
void showMenu();
void checkBalance(double balance);
double depositMoney(double balance);
double withdrawMoney(double balance);
bool changePin(int &currentPin);

int main() {
    int userPin = 1234; // الرمز الافتراضي
    int enteredPin;
    int attempts = 0;
    bool authenticated = false;
    
    double balance = 1000.0; // الرصيد الافتراضي
    int choice;

    cout << "========================================\n";
    cout << "     Welcome to the ATM System          \n";
    cout << "========================================\n";

    // التحقق من رمز الـ PIN (3 محاولات)
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPin;

        if (enteredPin == userPin) {
            authenticated = true;
            break;
        } else {
            attempts++;
            cout << "Incorrect PIN! Attempts remaining: " << (3 - attempts) << "\n";
        }
    }

    if (!authenticated) {
        cout << "\nToo many incorrect attempts. Card locked!\n";
        return 0;
    }

    // القائمة الرئيسية للنظام
    do {
        showMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        cout << fixed << setprecision(2); // لتنسيق الأرقام العشرية

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = depositMoney(balance);
                break;
            case 3:
                balance = withdrawMoney(balance);
                break;
            case 4:
                if (changePin(userPin)) {
                    cout << "PIN changed successfully! Please log in again.\n";
                    return 0; // إنهاء الجلسة بعد تغيير الـ PIN
                }
                break;
            case 5:
                cout << "\nThank you for using our ATM. Goodbye!\n";
                break;
            default:
                cout << "Invalid option! Please select a choice between 1 and 5.\n";
        }
        cout << "\n----------------------------------------\n";
    } while (choice != 5);

    return 0;
}

void showMenu() {
    cout << "\n--- ATM Main Menu ---\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Change PIN\n";
    cout << "5. Exit\n";
}

void checkBalance(double balance) {
    cout << "\nYour current balance is: $" << balance << "\n";
}

double depositMoney(double balance) {
    double amount;
    cout << "\nEnter amount to deposit: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount! Deposit must be greater than zero.\n";
    } else {
        balance += amount;
        cout << "Successfully deposited $" << amount << "\n";
        cout << "New balance: $" << balance << "\n";
    }
    return balance;
}

double withdrawMoney(double balance) {
    double amount;
    cout << "\nEnter amount to withdraw: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount!\n";
    } else if (amount > balance) {
        cout << "Insufficient funds! Your balance is only $" << balance << "\n";
    } else {
        balance -= amount;
        cout << "Successfully withdrawn $" << amount << "\n";
        cout << "Remaining balance: $" << balance << "\n";
    }
    return balance;
}

bool changePin(int &currentPin) {
    int oldPin, newPin, confirmPin;
    cout << "\nEnter your old PIN: ";
    cin >> oldPin;

    if (oldPin != currentPin) {
        cout << "Incorrect old PIN! Operation canceled.\n";
        return false;
    }

    cout << "Enter new 4-digit PIN: ";
    cin >> newPin;
    cout << "Confirm new 4-digit PIN: ";
    cin >> confirmPin;

    if (newPin != confirmPin) {
        cout << "PINs do not match! Operation canceled.\n";
        return false;
    }

    currentPin = newPin;
    return true;