#include<bits/stdc++.h>
#include "operations.h"
using namespace std;

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>



void addTransaction(sql::Connection* con) {

    string transactionType;
    string category;
    string transactionDescription;
    float amount;
    string date;

    sql::PreparedStatement *pstmt_insert, *pstmt_update1, * pstmt_update2;
    pstmt_insert = con->prepareStatement("INSERT INTO transactions(transactionType, category, transactionDescription, amount, transactionDate) VALUES(?,?,?,?,?);");
    pstmt_update1 = con->prepareStatement("UPDATE budget SET amountSpent = amountSpent + ? WHERE budgetName = ? AND ? = 'Expense';");
    pstmt_update2 = con->prepareStatement("UPDATE budget SET spendingLimit = spendingLimit + ? WHERE budgetName = ? AND ? = 'Income';");
    
    cout << "Enter Type (Income/Expense): ";
    cin >> transactionType;
    pstmt_insert->setString(1, transactionType);
    pstmt_update1->setString(3, transactionType);
    pstmt_update2->setString(3, transactionType);

    cout << "Enter Category: ";
    cin >> category;
    pstmt_insert->setString(2, category);
    pstmt_update1->setString(2, category);
    pstmt_update2->setString(2, category);

    cout << "Enter Description: ";
    cin.ignore();
    getline(cin, transactionDescription);
    pstmt_insert->setString(3, transactionDescription);

    cout << "Enter Amount: ";
    cin >> amount;
    pstmt_insert->setDouble(4, amount);
    pstmt_update1->setDouble(1, amount);
    pstmt_update2->setDouble(1, amount);

    
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;
    pstmt_insert->setString(5, date);

    
    try {
        string income = "Income";
        if (transactionType == income) pstmt_update2->execute();
        else pstmt_update1->execute();

        pstmt_insert->execute();
    }
    catch (sql::SQLException e)
    {
        cout << "Please enter apporpriate details. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    cout << endl << "Transaction added successfully." << endl;
    cout << "--------------------------------------------------------------" << endl;
    delete pstmt_insert;  // Remember to clean up resources
    delete pstmt_update1;
    delete pstmt_update2;
    return;
}


void viewTransaction(sql::Connection* con) {
    string start, end;
    cout << "Enter starting date (YYYY-MM-DD): ";
    cin >> start;
    cout << "Enter ending date (YYYY-MM-DD): ";
    cin >> end;

    sql::ResultSet* resultSet;
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("SELECT * FROM transactions WHERE transactionDate BETWEEN ? AND ?");
    pstmt->setString(1, start);
    pstmt->setString(2, end);
    resultSet = pstmt->executeQuery();

    int id;
    string transactionType;
    string category;
    string transactionDescription;
    float amount;
    string date;
    int count = resultSet->rowsCount();
    cout << "--------------------------------------------------------------" << endl;
    cout << "Number of Transactions: " << count << endl;
    cout << "--------------------------------------------------------------" << endl;
    while (resultSet->next()) {

        id = resultSet->getInt("transactionID");
        transactionType = resultSet->getString("transactionType");
        category = resultSet->getString("category");
        transactionDescription = resultSet->getString("transactionDescription");
        amount = resultSet->getDouble("amount");
        date = resultSet->getString("transactionDate");

        cout << endl;
        cout << "Transaction ID: " << id << endl;
        cout << "Transaction Type: " << transactionType << endl;
        cout << "Transaction Category: " << category << endl;
        cout << "Transaction Description: " << transactionDescription << endl;
        cout << "Transaction amount: " << amount << endl;
        cout << "Transaction Date: " << date << endl;
    }

    cout << "--------------------------------------------------------------" << endl;
    delete pstmt;
    return;
}


void addBudgetCategory(sql::Connection* con){
    string category;
    cout << "Enter Budget Category: ";
    cin >> category;
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("INSERT INTO budget(budgetName, spendingLimit, amountSpent) VALUES(?,?,?);");

    pstmt->setString(1, category);
    pstmt->setDouble(2, 0);
    pstmt->setDouble(3, 0);

    pstmt->execute();

    cout << endl << "Category created successfully." << endl;
    cout << "--------------------------------------------------------------" << endl;
    delete pstmt;  // Remember to clean up resources

}


void editBudgetCategory(sql::Connection* con) {
    string oldCategory, newCategory;
    cout << "Enter old category name: ";
    cin >> oldCategory;
    cout << "Enter new category name: ";
    cin >> newCategory;
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("UPDATE budget SET budgetName = ? WHERE budgetName = ?;");

    pstmt->setString(1, newCategory);
    pstmt->setString(2, oldCategory);

    pstmt->execute();

    cout << endl << "Category edited successfully." << endl;
    cout << "--------------------------------------------------------------" << endl;
    delete pstmt;  // Remember to clean up resources
}


void deleteBudgetCategory(sql::Connection* con){

}


void allocateBudget(sql::Connection* con) {

}


void viewReport(sql::Connection* con) {

}








//class addTransaction {
//private:
//    
//
//public:
//    // Constructor
//    addTransaction(){
//        
//    }
//
//    // Getter methods
//    int getTransactionId() const { return transactionId; }
//    string getDescription() const { return transactionDescription; }
//    float getAmount() const { return amount; }
//    string getDate() const { return date; }
//
//    // Example method: Print transaction details
//    void printTransaction() const {
//        cout << "Transaction ID: " << transactionId << "\n"
//            << "Description: " << transactionDescription << "\n"
//            << "Amount: $" << amount << "\n"
//            << "Date: " << date << "\n";
//    }
//
//    // Example method: Calculate tax for transaction
//    double calculateTax(double taxRate) const {
//        return amount * (taxRate / 100.0);
//    }
//
//    string getCategory() const {
//        return (amount < 0) ? "Expense" : "Income";
//    }
//
//    // Example method: Check if transaction is within a date range
//    bool isWithinDateRange(const string& startDate, const string& endDate) const {
//        return (date >= startDate) && (date <= endDate);
//    }
//
//    // Example method: Update transaction description
//    void updateDescription(const string& newDesc) {
//        this->transactionDescription = newDesc;
//    }
//
//    // Example method: Calculate discounted amount based on a discount rate
//    double calculateDiscountedAmount(double discountRate) const {
//        if (amount < 0) { // Only apply discounts to expenses
//            return amount * (1 - discountRate / 100.0);
//        }
//        return amount;
//    }
//};

/******************************************************************************************/

//class Budget {
//private:
//    string budgetName;
//    float spendingLimit;
//    float amountSpent;
//    string allocationFrequency;
//
//public:
//    // Constructor
//    Budget(string name, float limit, float spent, string freq){
//        this->budgetName = name;
//        this->spendingLimit = limit;
//        this->amountSpent = spent;
//        this->allocationFrequency = freq;
//    }
//
//    // Getter methods
//    string getName() const { return budgetName; }
//    double getLimit() const { return spendingLimit; }
//    double getSpent() const { return amountSpent; }
//
//    // Method to add an expense to the budget
//    void addExpense(double expenseAmount) {
//        amountSpent += expenseAmount;
//    }
//
//    // Method to check if the budget is exceeded
//    bool isExceeded() const {
//        return amountSpent > spendingLimit;
//    }
//
//    // Method to reset the spent amount to zero
//    void resetSpent() {
//        amountSpent = 0.0;
//    }
//
//    // Method to calculate remaining budget
//    double calculateRemainingBudget() const {
//        return spendingLimit - amountSpent;
//    }
//
//    void updateLimit(double newLimit) {
//        spendingLimit = newLimit;
//    }
//
//    // Method to check if the budget is close to being exceeded
//    bool isCloseToExceeded(double threshold) const {
//        return (amountSpent / spendingLimit) >= (1.0 - threshold / 100.0);
//    }
//
//    // Method to allocate budget for a specific expense category
//    void allocateExpense(const string& expenseCategory, double expenseAmount) {
//        if (budgetName == expenseCategory) {
//            amountSpent += expenseAmount;
//        }
//    }
//
//    // Method to transfer funds between budgets
//    void transferFundsTo(Budget& targetBudget, double transferAmount) {
//        if (transferAmount <= amountSpent) {
//            amountSpent -= transferAmount;
//            targetBudget.addExpense(transferAmount);
//        }
//    }
//};

/*****************************************************************************************************/

//class Wallet {
//private:
//    double balance;
//    vector<Transaction> transactions;
//
//public:
//    // Constructor
//    Wallet(double initialBalance) : balance(initialBalance) {}
//
//    // Method to add a transaction to the wallet
//    void addTransaction(const Transaction& transaction) {
//        transactions.push_back(transaction);
//        balance += transaction.getAmount();
//    }
//
//    // Method to get the current balance of the wallet
//    double getBalance() const {
//        return balance;
//    }
//
//    // Method to print all transactions in the wallet
//    void printTransactions() const {
//        cout << "Wallet Transactions:\n";
//        for (const Transaction& transaction : transactions) {
//            transaction.printTransaction();
//            cout << "\n";
//        }
//    }
//
//    // Example method: Calculate total expenses in the wallet
//    double calculateTotalExpenses() const {
//        double totalExpenses = 0.0;
//        for (const Transaction& transaction : transactions) {
//            if (transaction.getAmount() < 0) {
//                totalExpenses += transaction.getAmount();
//            }
//        }
//        return -totalExpenses; // Return positive value
//    }
//
//    double calculateTotalIncome() const {
//        double totalIncome = 0.0;
//        for (const Transaction& transaction : transactions) {
//            if (transaction.getAmount() > 0) {
//                totalIncome += transaction.getAmount();
//            }
//        }
//        return totalIncome;
//    }
//
//    // Example method: Get all transactions within a date range
//    vector<Transaction> getTransactionsInRange(const string& startDate, const string& endDate) const {
//        vector<Transaction> transactionsInRange;
//        for (const Transaction& transaction : transactions) {
//            if (transaction.isWithinDateRange(startDate, endDate)) {
//                transactionsInRange.push_back(transaction);
//            }
//        }
//        return transactionsInRange;
//    }
//
//    // Example method: Get transactions by category (expense/income)
//    vector<Transaction> getTransactionsByCategory(const string& category) const {
//        vector<Transaction> categorizedTransactions;
//        for (const Transaction& transaction : transactions) {
//            if ((category == "Expense" && transaction.getAmount() < 0) ||
//                (category == "Income" && transaction.getAmount() > 0)) {
//                categorizedTransactions.push_back(transaction);
//            }
//        }
//        return categorizedTransactions;
//    }
//};

/*********************************************************************************************/

//class ExpenseCategory {
//private:
//    string name;
//    string description;
//    vector<ExpenseCategory> subcategories;
//
//public:
//    ExpenseCategory(const string& n, const string& desc)
//        : name(n), description(desc) {}
//
//    void addSubcategory(const ExpenseCategory& subcategory) {
//        subcategories.push_back(subcategory);
//    }
//
//    string getName() const {
//        return name;
//    }
//
//    string getDescription() const {
//        return description;
//    }
//
//    // Method to print subcategories (recursive)
//    void printSubcategories(int depth = 0) const {
//        string indentation(depth * 4, ' ');
//        cout << indentation << name << " - " << description << "\n";
//        for (const ExpenseCategory& subcategory : subcategories) {
//            subcategory.printSubcategories(depth + 1);
//        }
//    }
//};




