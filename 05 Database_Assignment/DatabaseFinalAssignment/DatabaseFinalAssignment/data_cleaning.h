#pragma once
#include "pch.h"

/*
 * the definitions of all remove_all_null_columns' functions
 */

 /*
  * this function is defined for find the all names of null column
  * @return(vector<string>) column name
  */
vector<string> find_all_columns();

/*
 * this function could find all null columns from the columns we queried from table
 * @param(vector<string>) function<find_all_columns>'s return
 * @return(vector<string>) column name
 */
vector<string> find_all_null_columns(vector<string> all_columns);

/*
 * this function could delete all null columns in @param columns
 * #return(int) the number of columns deleted successfully
 */
void delete_all_null_columns();