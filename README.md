# 🏦 Bank Account Management System – OOP Assignment
## 📌 Overview

This Bank Account Management System is built using Object-Oriented Programming (OOP) principles in C++. The system allows for managing:

Accounts: Standard and Savings accounts, including functionality for interest calculation on Savings accounts.

Customers: Each customer can own multiple accounts.

Transactions: Includes basic operations such as Deposit, Withdraw, and Transfer between accounts. Interest is applied to Savings accounts.

The implementation demonstrates key OOP principles such as encapsulation, inheritance, polymorphism, and operator overloading.

## ⚙️ Build & Run Instructions
### On Linux / macOS / WSL:
``` bash
g++ BankAccountManager.cpp -o bank
./bank
```
```bash
### On Windows (MinGW g++):
g++ BankAccountManager.cpp -o bank.exe
bank.exe
```
## 🧩 Features

Customer Management: Auto-generates unique customer IDs and creates customer profiles.

Account Types: Supports both Standard Accounts and Savings Accounts with configurable interest rates.

Transaction Operations:

Deposit: Add funds to an account.

Withdraw: Remove funds from an account (with restrictions for Savings accounts).

Transfer: Transfer funds between different accounts.

Interest Application: Savings accounts can have interest applied automatically.

Transaction History: Each account maintains a history of transactions (deposit, withdrawal, transfer).

Bank Statistics: The system calculates the total number of customers, accounts, and the overall balance in the bank.

Operator Overloading:

+=: Used to add transaction amounts directly to an account, updating both the balance and the transaction history.

==: Compares two accounts based on their balance to check equality.

## 📐 UML Diagrams
Class Diagram

Sequence Diagram (Transaction Example)

## 🤖 AI Disclosure

Author: Nguyen Minh Thanh - 24110132
Used ChatGPT for:

Brainstorming class design and inheritance (Account → SavingsAccount).

Suggestions for operator overloading (+=, ==).

Structuring input validation and the overall menu-driven interface.

All the code was implemented, tested, and refined by myself before submission.

## 📝 Reflection

This assignment allowed me to apply Object-Oriented Programming principles to simulate a real-world banking system. The project helped me understand the following key concepts:

Inheritance: Creating a base Account class and deriving the SavingsAccount class enabled me to extend the functionality of account types while minimizing redundancy in the code.

Operator Overloading: By overloading the += and == operators, I was able to make transactions more intuitive and improve code readability.

Encapsulation: I learned how to encapsulate account information and transaction histories within the class, ensuring data is properly protected and managed.

Polymorphism: The handling of withdrawal limits and interest application through method overriding in the SavingsAccount class was an example of polymorphism in action.

Challenges:

Ensuring that the input validation works correctly to prevent invalid transactions.

Implementing safe transfers between accounts, especially for transactions involving Savings accounts that may have additional constraints.

Future Improvements:

Persistent Data Storage: Save the account data to files or a database to retain the information after the program ends.

Authentication & Permissions: Implement customer authentication and different access levels (e.g., customers, admins) for better security.

Support for Additional Features: For example, integrating loan accounts, credit limits, and more complex interest schedules.

This project improved my ability to design scalable applications using OOP and gave me hands-on experience with real-world financial system simulations.


