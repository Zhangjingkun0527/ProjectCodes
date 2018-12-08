#pragma once

#include "pch.h"
#include <winsock.h>
#include <mysql.h>



#define HOST "localhost"
#define USER "root"
#define PASSWORD "sq592147"
#define DEFAULT_DATABASE "test"

/*
 * execute sql query through a self-defined statement(only one)
 * @param statement(string) query statement
 * @param attributes(vector<string>) the attribute those will be added to result for being keys, so you must ensure the sequence of attributes is same as query columns
 * @return map<string, vector<string>> the return value is formatted as a map struct, whose keys are attributes
 * and values are put into a vector
 */
map<string, vector<string>> select_query(string statement);

/*
 * execute a insert, delete or update query statement
 * @param statement(string) query statement
 */
bool insert_update_delete_query(string statement);

/*
 * this function is the common codes for initializing mysql and querying
 * @param statement(string) query statement
 * #return (MYSQL_RES *) return type is the struct defined in <mysql.h>
 */
MYSQL_RES *init_and_query(string statement);

/*
 * this function is defined for closing database connection
 */
void close_database(MYSQL *connection);