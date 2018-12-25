/*
 * this file is created for defining some utility functions
 */
SET GLOBAL log_bin_trust_function_creators = TRUE;

/*
 *  this function is defined to remove all illegal character defined by mysql in a string
 */
DROP FUNCTION IF EXISTS drop_illegal_character;
DELIMITER //
CREATE FUNCTION drop_illegal_character(str VARCHAR(500))
RETURNS VARCHAR(500)
BEGIN
	DECLARE str_cleared VARCHAR(500);
	SET str_cleared = REPLACE(str, '\'', '');
	SET str_cleared = REPLACE(str_cleared, '"', '');
	SET str_cleared = REPLACE(str_cleared, '\\', '');
	SET str_cleared = REPLACE(str_cleared, ' ', '');
	RETURN str_cleared;
END //
DELIMITER ;

/*
 * extact function, which can extract param from params jointed with commas.
 */
DROP PROCEDURE IF EXISTS extract_params_jointed_by_comma;
DELIMITER //
CREATE PROCEDURE extract_params_jointed_by_comma(IN param_before_extract VARCHAR(1000), OUT param_after_extect VARCHAR(1000), OUT param VARCHAR(255))BEGIN
	DECLARE indexer INT;
	
	SET indexer = LOCATE(',', TRIM(param_before_extract));
	SET param = SUBSTRING(param_before_extract, 1, indexer - 1);
	SET param_after_extect = SUBSTRING(param_before_extract, indexer + 1);
END //
DELIMITER ;


/*
 * this procedure is defined to create indexes, the params must satisfy some rules like this:
 * column_names: name1, name2, and so on. namely, the params should be seperated by comma.
 * table_names and database_names is the same as this. And the tables_names and database_names should be
 * corresponding to each other.
 */
DROP PROCEDURE IF EXISTS create_index_for_columns;
DELIMITER //
CREATE PROCEDURE create_index_for_columns(IN column_names VARCHAR(1000), IN table_names VARCHAR(1000),
IN database_names VARCHAR(10000))
BEGIN
	DECLARE flag SMALLINT DEFAULT TRUE;
	DECLARE tmp_column_name VARCHAR(255);
	DECLARE tmp_table_name VARCHAR(255);
	DECLARE tmp_database_name VARCHAR(255);
	
	DECLARE tmp_column_name_arr VARCHAR(255);
	DECLARE tmp_table_name_arr VARCHAR(255);
	DECLARE tmp_database_name_arr VARCHAR(255);
	
	SET tmp_column_name_arr = TRIM(column_names);
	SET tmp_table_name_arr = TRIM(table_names);
	SET tmp_database_name_arr = TRIM(database_names);
	
	WHILE flag DO
		IF LOCATE(',', tmp_column_name_arr) > 0 THEN
			CALL extract_params_jointed_by_comma(tmp_column_name_arr, tmp_column_name_arr, tmp_column_name);
			CALL extract_params_jointed_by_comma(tmp_table_name_arr, tmp_table_name_arr, tmp_table_name);
			CALL extract_params_jointed_by_comma(tmp_database_name_arr, tmp_database_name_arr, tmp_database_name);
		ELSE
			SET flag = FALSE;
			SET tmp_column_name = tmp_column_name_arr;
			SET tmp_table_name = tmp_table_name_arr;
			SET tmp_database_name = tmp_database_name_arr;
		END IF;
		
		IF NOT EXISTS (SELECT * FROM information_schema.STATISTICS 
											WHERE COLUMN_NAME = tmp_column_name AND
														TABLE_NAME = tmp_table_name AND
														TABLE_SCHEMA = tmp_database_name) THEN
				
				SET @add_index_sql = CONCAT('CREATE INDEX ', tmp_column_name, ' ON ');
				SET @add_index_sql = CONCAT(@add_index_sql, tmp_table_name,'(', tmp_column_name, ')');
				PREPARE add_index_sql FROM @add_index_sql;
				EXECUTE add_index_sql;
		END IF;
	END WHILE;

END //
DELIMITER ;

DROP PROCEDURE IF EXISTS create_tmp_view_with_column_names_for_cursor;
DELIMITER //
CREATE PROCEDURE create_tmp_view_with_column_names_for_cursor(IN column_names VARCHAR(255), IN table_name VARCHAR(255), IN condition_exp VARCHAR(1000))
BEGIN
	DROP VIEW IF EXISTS tmp_view;
	SET @create_view_sql = CONCAT('CREATE VIEW tmp_view AS SELECT ', column_names, ' FROM ', table_name);
	IF !ISNULL(condition_exp) AND CHAR_LENGTH(TRIM(condition_exp)) > 0 THEN
		SET @create_view_sql = CONCAT(@create_view_sql, ' WHERE ', condition_exp);
	END IF;
	
	PREPARE create_view_sql FROM @create_view_sql;
	EXECUTE create_view_sql;
END //
DELIMITER ;


DROP FUNCTION IF EXISTS is_column_value_null_or_empty_string;
DELIMITER //
CREATE FUNCTION is_column_value_null_or_empty_string(column_value VARCHAR(1000))
RETURNS SMALLINT
BEGIN
	RETURN ISNULL(column_value) OR CHAR_LENGTH(TRIM(column_value)) < 1;
END //
DELIMITER ;

DROP FUNCTION IF EXISTS remove_brackets;
DELIMITER //
CREATE FUNCTION remove_brackets(str VARCHAR(255))
RETURNS VARCHAR(255)
BEGIN
	DECLARE str_cleared VARCHAR(255);
	SET str_cleared = REPLACE(str, '(', '');
	SET str_cleared = REPLACE(str_cleared, ')', '');
	SET str_cleared = REPLACE(str_cleared, '（', '');
	SET str_cleared = REPLACE(str_cleared, '）', '');
	RETURN str_cleared;
END //
DELIMITER ;