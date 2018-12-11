/* 
 *  this file is created for some self-defined query functions
 */
SET GLOBAL log_bin_trust_function_creators = TRUE;

DROP PROCEDURE IF EXISTS insert_into_target_table_single_value;
DELIMITER //
CREATE PROCEDURE insert_into_target_table_single_value(IN insert_value VARCHAR(255), IN target_column VARCHAR(255), IN target_database VARCHAR(255), IN target_table VARCHAR(255))
BEGIN
	SET @insert_statement = CONCAT('INSERT INTO ', target_database,'.', target_table, ' (', target_column,')'
	, ' VALUES (', insert_value, ')');
	PREPARE insert_statement FROM @insert_statement;
	EXECUTE insert_statement;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS update_single_column_with_id;
DELIMITER //
CREATE PROCEDURE update_single_column_with_id(IN id INT, IN update_value VARCHAR(255), IN target_column_name VARCHAR(255), IN target_table VARCHAR(255), IN target_database VARCHAR(255))
BEGIN
	SET @update_statement = CONCAT('UPDATE ', target_table,' SET ', target_column_name, ' = ', update_value, ' WHERE id = ', id);
	PREPARE update_statement FROM @update_statement;
	EXECUTE update_statement;
END //
DELIMITER ;

/*
 *  this procedure is defined to insert one record, according to id, into the target table, using column names defiend in table column_names_for_insertion, this table stores the target column names, which are one-to-one to the target table columns by positive sequence
 */
DROP PROCEDURE IF EXISTS insert_one_record_to_target_table_using_column_names;
DELIMITER //
CREATE PROCEDURE insert_one_record_to_target_table_using_column_names(IN origin_columns_arr VARCHAR(1000), IN target_columns_arr VARCHAR(1000), IN id INT, IN target_table VARCHAR(255), IN target_database VARCHAR(255), IN origin_table VARCHAR(255), IN origin_database VARCHAR(255))
BEGIN
	SET @tmp_origin_columns_arr = origin_columns_arr;
	SET @tmp_target_columns_arr = target_columns_arr;
	SET @insert_statement_part_1 = CONCAT('INSERT INTO ', target_database, '.', target_table, ' (');
	SET @insert_statement_part_2 = CONCAT(' VALUES (');
	SET @flag = TRUE;
	WHILE @flag DO
		/*extact column name in origin table*/
		SET @index_of_split_symbol_origin = LOCATE(',', @tmp_origin_columns_arr);
		SET @origin_column_name = '';
		IF @index_of_split_symbol_origin THEN
			SET @origin_column_name = TRIM(SUBSTRING(@tmp_origin_columns_arr, 1, @index_of_split_symbol_origin - 1));
			SET @tmp_origin_columns_arr = SUBSTRING(@tmp_origin_columns_arr, @index_of_split_symbol_origin + 1);
		ELSE
			SET @origin_column_name = TRIM(@tmp_origin_columns_arr);
			SET @flag = FALSE;
		END IF;
		SET @value_from_origin_table = '';
		
		/*query the value of origin column, and joint it into insert statement*/
		SET @query_statement = CONCAT('SELECT CAST(', @origin_column_name, ' AS CHAR) INTO @value_from_origin_table FROM ', origin_database, '.', origin_table, ' WHERE id = ', id);
		PREPARE query_statement FROM @query_statement;
		EXECUTE query_statement;
		DEALLOCATE PREPARE query_statement;
		SET @insert_statement_part_2 = CONCAT(@insert_statement_part_2, '\'', @value_from_origin_table, '\',');
		
		/*extact column name in target table*/
		SET @index_of_split_symbol_target = LOCATE(',', @tmp_target_columns_arr);
		SET @target_column_name = '';
		IF @index_of_split_symbol_target THEN
			SET @target_column_name = TRIM(SUBSTRING(@tmp_target_columns_arr, 1, @index_of_split_symbol_target - 1));
			SET @tmp_target_columns_arr = SUBSTRING(@tmp_target_columns_arr, @index_of_split_symbol_target + 1);
		ELSE
			SET @target_column_name = TRIM(@tmp_target_columns_arr);
		END IF;
		
		/*joint the target column name into insert statement*/
		SET @insert_statement_part_1 = CONCAT(@insert_statement_part_1, @target_column_name, ',');
	END WHILE;
	/*remove the last comma and joint the jacket*/
	SET @insert_statement_part_1 = CONCAT(LEFT(@insert_statement_part_1, CHAR_LENGTH(@insert_statement_part_1) - 1),') ');
	SET @insert_statement_part_2 = CONCAT(LEFT(@insert_statement_part_2, CHAR_LENGTH(@insert_statement_part_2) - 1), ')');
	/*execute the final insert statement*/
	SET @insert_statement = CONCAT(@insert_statement_part_1, @insert_statement_part_2);
	PREPARE insert_statement FROM @insert_statement;
	EXECUTE insert_statement;
END //
DELIMITER ;
