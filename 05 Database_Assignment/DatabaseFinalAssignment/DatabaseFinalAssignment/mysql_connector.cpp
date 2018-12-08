#include "pch.h"
#include "mysql_util.h"
//state a mysql struct for connection
static MYSQL mysql;
map<string, vector<string>> select_query(const string statement)
{
	//define the map struct for storing data
	map<string, vector<string>> result;
	const auto query_result = init_and_query(statement);
	if (query_result == nullptr) return result;
	//extract rows from res
	MYSQL_ROW row;
	auto fields = mysql_fetch_fields(query_result);
	while ((row = mysql_fetch_row(query_result)))
	{
		for (auto i = 0; i < sizeof(fields)/sizeof(MYSQL_FIELD); ++i)
		{
			if (result.find(fields[i].name) != result.end())
			{
				result.at(fields[i].name).push_back(row[i]);
			}
			else
			{
				vector<string> temp;
				temp.push_back(row[i]);
				result.insert(pair<string, vector<string>>(fields[i].name, temp));
			}
		}
	}
	//free result
	mysql_free_result(query_result);
	close_database(&mysql);
	return result;
}

bool insert_update_delete_query(const string statement)
{
	auto res = init_and_query(statement);
	close_database(&mysql);
	return true;
}

MYSQL_RES* init_and_query(string statement)
{
	try
	{
		//query result, which is actually a char **
		MYSQL_ROW row;

		//open connection
		mysql_init(&mysql);
		//set the encoding way
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

		//test if the database can be connected by program
		if (mysql_real_connect(&mysql, HOST, USER, PASSWORD, DEFAULT_DATABASE, 3306, nullptr, 0) == nullptr)
			printf("connect failed£¡\n");
		//execute query
		mysql_query(&mysql, statement.data());
		//get query result
		return mysql_store_result(&mysql);
	}
	catch (exception e)
	{
		printf("encountered a connection exception!");
		return nullptr;
	}
}

void close_database(MYSQL *connection)
{
	//close sql connection
	mysql_close(connection);
}