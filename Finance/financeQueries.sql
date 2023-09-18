CREATE DATABASE finance;

USE finance;

CREATE TABLE Transactions(
    transactionID INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
    category VARCHAR(30),
    transactionDescription VARCHAR(255),
    amount FLOAT,
    transactionDate DATETIME
);

CREATE TABLE Budget(
    budgetName VARCHAR(30) PRIMARY KEY NOT NULL,
    spendingLimit FLOAT,
    amountSpent FLOAT
);

ALTER TABLE Transactions ADD transactionType VARCHAR(10) AFTER transactionID;

DELETE FROM Transactions;

ALTER TABLE Transactions ADD FOREIGN KEY (category) REFERENCES budget(budgetName);

SELECT SUM(IF(transactionType = 'Income', amount, 0)) AS total_income,SUM(IF(transactionType = 'Expense', amount, 0)) AS total_expense  FROM transactions;

SELECT * FROM budget; WHERE transactionType = 'Expense' AND amount > 200;
SELECT * FROM transactions;
ALTER TABLE Transactions AUTO_INCREMENT = 1;

ALTER TABLE Transactions MODIFY transactionDate DATE;

DELETE FROM budget;

DROP TABLE budget;