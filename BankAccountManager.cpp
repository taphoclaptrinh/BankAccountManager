#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Transaction class
class Transaction {
public:
    enum Type { DEPOSIT, WITHDRAWAL, TRANSFER };

private:
    double amount;
    Type type;
    string date;

public:
    // Constructor m?c d?nh
    Transaction() : amount(0.0), type(DEPOSIT), date("") {}

    // Constructor có tham s?
    Transaction(double amt, Type t) : amount(amt), type(t) {
        time_t now = time(0);
        date = ctime(&now);
    }

    // Getter
    double getAmount() const { return amount; }
    Type getType() const { return type; }
    string getDate() const { return date; }
 	
    // Setter
    void setAmount(double amt) { amount = amt; }
    void setType(Type t) { type = t; }
    void setDate(const string& d) { date = d; }

    // Hi?n th? lo?i giao d?ch
    string getTypeString() const {
        switch (type) {
            case DEPOSIT: return "Deposit";
            case WITHDRAWAL: return "Withdrawal";
            case TRANSFER: return "Transfer";
            default: return "Unknown";
        }
    }

    // Hi?n th? thông tin giao d?ch
    void display() const {
        cout << "Transaction: " << getTypeString()
             << " | Amount: $" << amount
             << " | Date: " << date;
    }

    // So sánh giao d?ch
    bool operator==(const Transaction& other) const {
        return amount == other.amount && type == other.type && date == other.date;
    }
};


// Base Account class
class Account {
protected:
    string ownerName;
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    // Constructor m?c d?nh
    Account() : ownerName(""), accountNumber(0), balance(0.0) {}

    // Constructor có tham s?
    Account(string name, int number, double initialBalance = 0.0)
        : ownerName(name), accountNumber(number), balance(initialBalance) {}

    virtual ~Account() {}

    // N?p ti?n
    virtual void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction(amount, Transaction::DEPOSIT));
    }

    // Rút ti?n
    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction(amount, Transaction::WITHDRAWAL));
    }

    // Hi?n th? thông tin
    virtual void displayInfo() const {
        cout << "Account #" << accountNumber << " | Owner: " << ownerName << " | Balance: $" << balance << "\n";
    }

    // N?p ch?ng toán t? += d? thêm giao d?ch
    Account& operator+=(const Transaction& t) {
        if (t.getType() == Transaction::DEPOSIT) deposit(t.getAmount());
        else if (t.getType() == Transaction::WITHDRAWAL) withdraw(t.getAmount());
        return *this;
    }

    // So sánh s? du
    bool operator==(const Account& other) const {
        return this->balance == other.balance;
    }

    // Getter
    string getOwnerName() const { return ownerName; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    vector<Transaction> getHistory() const { return history; }

    // Setter
    void setOwnerName(const string& name) { ownerName = name; }
    void setAccountNumber(int number) { accountNumber = number; }
    void setBalance(double amount) { balance = amount; }
};


// Derived SavingsAccount class
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Constructor m?c d?nh
    SavingsAccount() : Account("", 0, 0.0), interestRate(0.0) {}

    // Constructor có tham s?
    SavingsAccount(string name, int number, double rate, double initialBalance = 0.0)
        : Account(name, number, initialBalance), interestRate(rate) {}

    // Getter cho interestRate
    double getInterestRate() const {
        return interestRate;
    }

    // Setter cho interestRate
    void setInterestRate(double rate) {
        interestRate = rate;
    }

    // Áp d?ng lãi su?t
    void applyInterest() {
        double interest = balance * interestRate / 100;
        deposit(interest);
        cout << "Interest of $" << interest << " applied.\n";
    }

    // Ghi dè phuong th?c rút ti?n
    void withdraw(double amount) override {
        if (amount > balance) {
            cout << "Withdrawal denied. Savings account cannot be overdrawn.\n";
            return;
        }
        if (amount > 1000) {
            cout << "Withdrawal exceeds limit for savings account.\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction(amount, Transaction::WITHDRAWAL));
    }
};


// Customer class
class Customer {
private:
    string name;
    int customerID;
    vector<Account*> accounts;

public:
    // Constructor m?c d?nh
    Customer() : name(""), customerID(0) {}

    // Constructor có tham s?
    Customer(string n, int id) : name(n), customerID(id) {}

    // Getter cho name
    string getName() const {
        return name;
    }

    // Setter cho name
    void setName(const string& newName) {
        name = newName;
    }

    // Getter cho customerID
    int getID() const {
        return customerID;
    }

    // Setter cho customerID
    void setID(int newID) {
        customerID = newID;
    }

    // Getter cho danh sách tài kho?n
    vector<Account*> getAccounts() const {
        return accounts;
    }

    // Thêm tài kho?n
    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }

    // Hi?n th? thông tin tài kho?n
    void displayAccounts() const {
        cout << "Customer: " << name << " | ID: " << customerID << "\n";
        for (auto* acc : accounts) {
            acc->displayInfo();
        }
    }

    // Tính t?ng s? du
    double totalBalance() const {
        double total = 0.0;
        for (auto acc : accounts) {
            total += acc->getBalance();
        }
        return total;
    }
    
    Customer& operator+=(Account* acc) {
    accounts.push_back(acc);
    return *this;
	}

};


void menu() {
    cout << "\n========== BANK ACCOUNT MANAGEMENT ==========\n";
    cout << "1. Tao khach hang moi\n";
    cout << "2. Tao tai khoan moi (thuong hoac tiet kiem)\n";
    cout << "3. Nap tien vao tai khoan\n";
    cout << "4. Rut tien tu tai khoan\n";
    cout << "5. Chuyen tien giua hai tai khoan\n";
    cout << "6. Ap dung lai suat cho tai khoan tiet kiem\n";
    cout << "7. Hien thi thong tin tai khoan\n";
    cout << "8. Hien thi thong tin khach hang\n";
    cout << "9. So sanh hai tai khoan (==)\n";
    cout << "10. Them giao dich bang toan tu +=\n";
    cout << "0. Thoat\n";
    cout << "=============================================\n";
    cout << "Chon chuc nang: ";
}


#include <map> // de luu khach hang theo ID

int main() {
    map<int, Customer*> customers;
    map<int, Account*> accounts;
    int choice;
    
    Account* accThuong1 = new Account("Nguyen Van A", 1001, 5000.0);
	Account* accThuong2 = new Account("Tran Thi B", 1002, 3000.0);
	
	SavingsAccount* accTietKiem1 = new SavingsAccount("Le Van C", 2001, 3.5, 10000.0);
	SavingsAccount* accTietKiem2 = new SavingsAccount("Pham Thi D", 2002, 4.0, 8000.0);



    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int id;
                cout << "Nhap ten khach hang: ";
                cin.ignore(); getline(cin, name);
                cout << "Nhap ID khach hang: ";
                cin >> id;
                customers[id] = new Customer(name, id);
                cout << "Khach hang da duoc tao.\n";
                break;
            }
            case 2: {
                int id, accNum;
                string type;
                double balance, rate = 0;
                cout << "Nhap ID khach hang: ";
                cin >> id;
                if (customers.find(id) == customers.end()) {
                    cout << "Khach hang khong ton tai.\n";
                    cout << "Tao khach hang moi. \n";
                    cout << "Nhap ten khach hang. \n";
                    string name;cin.ignore(); getline(cin, name);
                    customers[id] = new Customer(name,id);
                }
                cout << "Nhap loai tai khoan (thuong/tietkiem): ";
                cin >> type;
                cout << "Nhap so tai khoan: ";
                cin >> accNum;
                cout << "Nhap so du ban dau: ";
                cin >> balance;
                Account* acc;
                if (type == "tietkiem") {
                    cout << "Nhap lai suat (%): ";
                    cin >> rate;
                    acc = new SavingsAccount(customers[id]->getName(), accNum, rate, balance);
                } else {
                    acc = new Account(customers[id]->getName(), accNum, balance);
                }
                customers[id]->operator+=(acc);
                accounts[accNum] = acc;
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Nhap so tai khoan: ";
                cin >> accNum;
                cout << "Nhap so tien nap: ";
                cin >> amount;
                if (accounts.find(accNum) != accounts.end()) {
                    accounts[accNum]->deposit(amount);
                } else {
                    cout << "Tai khoan khong ton tai.\n";
                }
                break;
            }
            case 4: {
                int accNum;
                double amount;
                cout << "Nhap so tai khoan: ";
                cin >> accNum;
                cout << "Nhap so tien rut: ";
                cin >> amount;
                if (accounts.find(accNum) != accounts.end()) {
                    accounts[accNum]->withdraw(amount);
                } else {
                    cout << "Tai khoan khong ton tai.\n";
                }
                break;
            }
            case 5: {
                int fromAcc, toAcc;
                double amount;
                cout << "Nhap tai khoan gui: ";
                cin >> fromAcc;
                cout << "Nhap tai khoan nhan: ";
                cin >> toAcc;
                cout << "Nhap so tien chuyen: ";
                cin >> amount;
                if (accounts.find(fromAcc) == accounts.end() || accounts.find(toAcc) == accounts.end()) {
                    cout << "Mot trong hai tai khoan khong ton tai.\n";
                    break;
                }
                if (accounts[fromAcc]->getBalance() < amount) {
                    cout << "Khong du tien de chuyen.\n";
                    break;
                }
                accounts[fromAcc]->withdraw(amount);
                accounts[toAcc]->deposit(amount);
                cout << "Chuyen tien thanh cong.\n";
                break;
            }
            case 6: {
                int accNum;
                cout << "Nhap so tai khoan tiet kiem: ";
                cin >> accNum;
                SavingsAccount* sa = dynamic_cast<SavingsAccount*>(accounts[accNum]);
                if (sa) {
                    sa->applyInterest();
                } else {
                    cout << "Tai khoan khong phai tiet kiem hoac khong ton tai.\n";
                }
                break;
            }
            case 7: {
                int accNum;
                cout << "Nhap so tai khoan: ";
                cin >> accNum;
                if (accounts.find(accNum) != accounts.end()) {
                    accounts[accNum]->displayInfo();
                } else {
                    cout << "Tai khoan khong ton tai.\n";
                }
                break;
            }
            case 8: {
                int id;
                cout << "Nhap ID khach hang: ";
                cin >> id;
                if (customers.find(id) != customers.end()) {
                    customers[id]->displayAccounts();
                } else {
                    cout << "Khach hang khong ton tai.\n";
                }
                break;
            }
            case 9: {
                int acc1, acc2;
                cout << "Nhap so tai khoan 1: ";
                cin >> acc1;
                cout << "Nhap so tai khoan 2: ";
                cin >> acc2;
                if (accounts.find(acc1) != accounts.end() && accounts.find(acc2) != accounts.end()) {
                    if (*accounts[acc1] == *accounts[acc2])
                        cout << "Hai tai khoan co so du bang nhau.\n";
                    else
                        cout << "Hai tai khoan co so du khac nhau.\n";
                } else {
                    cout << "Mot trong hai tai khoan khong ton tai.\n";
                }
                break;
            }
            case 10: {
                int accNum;
                double amount;
                string type;
                cout << "Nhap so tai khoan: ";
                cin >> accNum;
                cout << "Nhap loai giao dich (Deposit/Withdrawal): ";
                cin >> type;
                cout << "Nhap so tien: ";
                cin >> amount;
                if (accounts.find(accNum) != accounts.end()) {
                    Transaction::Type tType = (type == "Deposit") ? Transaction::DEPOSIT : Transaction::WITHDRAWAL;
                    *accounts[accNum] += Transaction(amount, tType);
                } else {
                    cout << "Tai khoan khong ton tai.\n";
                }
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);

    for (auto& pair : customers) delete pair.second;
    for (auto& pair : accounts) delete pair.second;

    return 0;
}

