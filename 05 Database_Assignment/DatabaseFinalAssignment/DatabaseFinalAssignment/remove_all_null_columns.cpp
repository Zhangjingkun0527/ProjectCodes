#include "pch.h"
#include "mysql_util.h"
#include "data_cleaning.h"
void delete_all_null_columns()
{
	const auto all_columns = find_all_columns();
	const auto null_columns = find_all_null_columns(all_columns);
	string sql= "ALTER TABLE course DROP COLUMN ";
	for(auto i = 0; i < null_columns.size(); ++i)
	{
		sql += null_columns[i] + (i == null_columns.size() - 1 ? "" : ",");
	}
	const auto delete_result = insert_update_delete_query(sql);
	if(delete_result)
	{
		printf("Successfully delete all null columns!");
	}
	else
	{
		printf("There is something wrong with delete operation, please rollback your database!");
	}
}

vector<string> find_all_null_columns(vector<string> all_columns)
{
	vector<string> result;
	if (all_columns.size() == 0) return result;
	//create sql statement
	string sql = "SELECT ";
	const string count_sql = "COUNT(";
	for(auto i = 0; i < all_columns.size(); ++i)
	{
		sql += count_sql + all_columns[i] + ") ";
		sql += "AS count_" + all_columns[i];
		sql += i == all_columns.size() - 1 ? "" : ",";
	}
	sql += " FROM course";

	//find null columns
	const auto result_in_map = select_query(sql);
	for(auto it = result_in_map.begin(); it != result_in_map.end(); ++it)
	{
		if (it->second.size() == 0) continue;
		if (it->second[0] != "0")continue;
		result.push_back(it->first);
	}

	return result;
}

vector<string> find_all_columns()
{
	vector<string> result;
	//let us get just one tuple, and find all columns
	const string sql = "SELECT * FROM course LIMIT 1";
	//the key is the columns in the table cdsgus
	auto result_in_map =  select_query(sql);
	for (auto it = result_in_map.begin(); it != result_in_map.end(); ++it)
		result.push_back(it->first);

	return result;
}