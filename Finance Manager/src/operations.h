// operations.h

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


void addTransaction(sql::Connection* con);
void viewTransaction(sql::Connection* con);
void addBudgetCategory(sql::Connection* con);
void editBudgetCategory(sql::Connection* con);
void deleteBudgetCategory(sql::Connection* con);
void allocateBudget(sql::Connection* con);
void viewReport(sql::Connection* con);

#endif
