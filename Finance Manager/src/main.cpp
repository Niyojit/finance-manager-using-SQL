#include<bits/stdc++.h>
#include "operations.h"
using namespace std;

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";

void budgetMenu(sql::Connection* con) {
	bool bm = true;
	while (bm) {
		cout << "1. Add Budget Category" << endl;
		cout << "2. Edit Budget Category" << endl;
		cout << "3. Delete Budget Category" << endl;
		cout << "4. Previous Menu" << endl;
		cout << endl << "Choose an operation: ";
		int budKey;
		cin >> budKey;
		switch (budKey) {
		case 1:
			addBudgetCategory(con);
			break;
		case 2:
			editBudgetCategory(con);
			break;
		case 3:
			deleteBudgetCategory(con);
			break;
		case 4:
			bm = false;
			break;
		default:
			cout << "Please Choose appropriate operation" << endl;
			break;
		}
		cout << endl;
	}
}

int main() {
	// Driver forms the connection to the database and execute queries stored in stmt. pstmt are fixed queries where
    // only parameters change and not the structure of query.
    sql::Driver* driver;
    sql::Connection* con;
    /*sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* resultSet;*/

    // connecting to server and trying to avoid error using try-catch statement
    try
    {
        driver = get_driver_instance();
		string username, password;
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		cout << endl;
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    //selecting the database. IMP: Database must be present already.
    con->setSchema("finance");

	//###############################################################################################
	
	
	cout << "Welcome to Finance Manager.\nHow may I help you?" << endl << endl;
	bool mainMenu = true;
	while (mainMenu) {
		cout << "1. Add Transaction" << endl;
		cout << "2. View Past Transactions" << endl;
		cout << "3. Manage Budget Categories" << endl;
		cout << "4. Allocate Budget" << endl;
		cout << "5. View Report" << endl;
		cout << "6. Quit" << endl;
		cout << endl << "Choose an operation: ";
		int mainKey;
		cin >> mainKey;
		switch (mainKey) {
		case 1:
			addTransaction(con);
			break;
		case 2:
			viewTransaction(con);
			break;
		case 3:
			cout << endl;
			budgetMenu(con);
			break;
		case 4:
			allocateBudget(con);
			break;
		case 5:
			viewReport(con);
			break;
		case 6:
			mainMenu = false;
			break;
		default:
			cout << "Please Choose appropriate operation" << endl;
			break;
		}
		cout << endl;
	}
	cout << "Thank You!!" << endl;
	return 0;
}