/* this procedure is defined to correct unreliable values in key columns */ 
/********Note: the main function is in the bottom of this file*******/
SET GLOBAL log_bin_trust_function_creators = TRUE;
USE test;
SET @database_name = 'test';
SET @table_name = 'cdsgus';
/*@base_column_name is judgment standard for split tabel, and alse the most important column*/
SET @base_column_name = 'CtfId';
SET @chinese_table = 'users_owning_chinese_identity_card';
SET @non_chinese_table = 'users_not_owning_chinese_identity_card';
SET @target_database = 'test';

/*this variable is the set of column names of origin table which splited by comma*/
SET @origin_column_names = 'Name, CtfId, Gender, Birthday, Address, Zip, Mobile, Tel, EMail, Nation, Version, id';
/*this variable is the set of column names of target table which splited by comma*/
SET @target_column_names = 'name, identity_number, gender, birthday, contact_address, zip, mobile, tel_number, email, nation, register_date, id_cdsgus';
/*these two variables is defined for verifying chinese id*/
SET @chinese_target_table = 'users_owning_chinese_identity_card';
SET @non_chinese_target_table = 'users_not_owning_chinese_identity_card';

/*regelar expression*/
SET @chinese_id_18_numbers_regexp = '^[1-9][0-9]{5}((19[0-9]{2})|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}[0-9Xx]$';

SET @chinese_id_17_numbers_regexp = '^[1-9][0-9]{5}((19[0-9]{2})|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';

SET @chinese_id_15_numbers_regexp = '^[1-9][0-9]{5}[0-9]{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';



/*
 * this procedure is defined to create param table for verifying id
 */
DROP PROCEDURE IF EXISTS create_param_table;
DELIMITER //
CREATE PROCEDURE create_param_table() 
BEGIN
	/*create validate table for verifying ids*/
	IF NOT EXISTS (SELECT TABLE_NAME FROM information_schema.`TABLES` WHERE TABLE_NAME = 'validate_params' AND TABLE_SCHEMA = @database_name ) THEN
		CREATE TABLE validate_params ( type VARCHAR ( 100 ) NOT NULL, CONSTRAINT PRIMARY KEY ( type ) );
		/*we think that it's enough for adding 18 columns to the validate_params*/
		SET @count_of_columns = 17;
		WHILE	@count_of_columns >= 0 DO
			SET @indexer = 18 - @count_of_columns;
			SET @column_name = CONCAT('param_', @indexer);
			IF NOT EXISTS (SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_SCHEMA = @database_name AND TABLE_NAME = 'validate_params' AND COLUMN_NAME = @column_name) THEN
				SET @add_column_statement = CONCAT('ALTER TABLE validate_params ADD COLUMN ', @column_name, ' VARCHAR(10)');
				PREPARE add_column_statement FROM	@add_column_statement;
				EXECUTE add_column_statement;
				
				SET @count_of_columns = @count_of_columns - 1;
			END IF;
		END WHILE;
	END IF;
END // 
DELIMITER ;
CALL create_param_table();



/*
 * this prodeure is trying to find the id number from other columns, this procedure is called by procedure find_id_number_from_other_columns
 */
DROP PROCEDURE IF	EXISTS find_id_number_from_other_columns_processing_function;
DELIMITER //
CREATE PROCEDURE find_id_number_from_other_columns_processing_function(IN column_value VARCHAR(255), OUT id_number VARCHAR(18)) 
for_leave_procedure : BEGIN
	/*clear the tmp string, because it may have some chars which are not digits or letter x*/
	SET @str_cleared = drop_non_digit_or_letter_x(column_value);
	SET @length_of_str_cleared = LENGTH(@str_cleared);
	IF @length_of_str_cleared >= 15 THEN
		SET @indexer = 1;
		/*extract the substr with 18 chars and verify it*/
		WHILE	@indexer <= @length_of_str_cleared - 17 DO
			SET @tmp_substr = SUBSTRING(@str_cleared, @indexer, 18);
			SET @result = FALSE;
			
			/*verify the substring*/
			CALL is_id_18_numbers_validated(@tmp_substr, @result);
			SELECT @tmp_substr;
			/*if the substr is a validated id number then leave the procedure*/
			IF @result THEN
				SET id_number = @tmp_substr;
				LEAVE for_leave_procedure;
			END IF;
			
			SET @indexer = @indexer + 1;
		END WHILE;
		
		/*if we do not find the validated id number having 18 numbers, then we should try to find the id number with 15 numbers and convert them to 18 id number*/
		SET @indexer = 1;
		WHILE	@indexer <= @length_of_str_cleared - 14 DO
			SET @tmp_substr = SUBSTRING( @str_cleared, @indexer, 15);
			IF is_id_15_numbers_validated(@tmp_substr) THEN
				CALL convert_15_to_18_for_id_number(@tmp_substr, id_number);
				LEAVE for_leave_procedure;
			END IF;
			
			SET @indexer = @indexer + 1;
		END WHILE;
	END IF;
END // 
DELIMITER ;



/*
 * this procedure is defined to query result by id in cdsgus, and put into tmp_view for realizing dynamic cursor
 */
DROP PROCEDURE IF	EXISTS find_id_number_from_other_columns;
DELIMITER //
CREATE PROCEDURE find_id_number_from_other_columns(IN id INT, OUT id_number VARCHAR(18)) 
for_leave_procedure : BEGIN
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE tmp VARCHAR(255) DEFAULT '';
	/*get all columns in @table_name*/
	DECLARE columns_cursor CURSOR FOR SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_NAME = @table_name AND TABLE_SCHEMA = @database_name;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	/*for each column, we should query the value according to id, and put it into tmp_table*/
	OPEN columns_cursor;
	WHILE !flag DO
		FETCH columns_cursor INTO tmp;
		/*get value in each columns of @table_name according to id */
		IF !flag THEN
			SET @query_result = '';
			SET @query_statement = CONCAT('SELECT ', tmp, ' INTO @query_result FROM ', @table_name, ' WHERE id = ', id);
			PREPARE query_statement FROM @query_statement;
			EXECUTE query_statement;
			DEALLOCATE PREPARE query_statement;
			/*for id column, we dont need to concern it*/
			IF @query_result != 'id' THEN
				SET @id_number_extracted = '';				
				CALL find_id_number_from_other_columns_processing_function(@query_result, @id_number_extracted);
				
				/*if the @id_number_extracted is not null, then mission is completed*/
				IF !ISNULL(@id_number_extracted) AND LENGTH(TRIM(@id_number_extracted)) THEN
					SET id_number = @id_number_extracted;
					LEAVE for_leave_procedure;
				END IF;
			END IF;
		END IF;
	END WHILE;
	SET id_number = '';
END // 
DELIMITER ;

/* 
 *  this procedure is the main processing part in main procedure. The cause of creation is to 
 reduce the complexity of main procedure
 */
DROP PROCEDURE IF EXISTS processing_id_numbers_and_do_insertion;
DELIMITER //
CREATE PROCEDURE processing_id_numbers_and_do_insertion(IN id INT, IN str VARCHAR(255))
BEGIN
	SET @is_a_validated_id_number_having_18_numbers = FALSE;
	CALL is_id_18_numbers_validated(str, @is_a_validated_id_number_having_18_numbers);
	/*firstly, we need to judge whether the string is a 18 id number, according to regular expression*/
	IF @is_a_validated_id_number_having_18_numbers THEN
		/*if the it's validated, then we will add the record into the new table*/
		CALL insert_one_record_to_target_table_using_column_names(@origin_column_names, @target_column_names, id, @chinese_table, @target_database, @table_name, @database_name);
	ELSE
		/*if the id number is not a 18 id number, and we need to judge whether the id number is a 15 id number*/
		IF is_id_15_numbers_validated(str) THEN
			/*if the id numbr is a 15 id number according to regular expression*/
			SET @converted_to_18_numbers = '';
			CALL convert_15_to_18_for_id_number(str, @converted_to_18_numbers);
			CALL update_single_column_with_id(id, @converted_to_18_numbers, @base_column_name, @table_name, @database_name);
			CALL insert_one_record_to_target_table_using_column_names(@origin_column_names, @target_column_names, id, @chinese_table, @target_database, @table_name, @database_name);
		ELSE
			/*if the value is not a validated id number, so we need to try to find value from other columns*/
			SET @corrected_value = '';
			CALL find_id_number_from_other_columns(@max_number, @corrected_value);
			/*if we find the proper value ,then update the origin table, and insert it into the chinese table*/
			IF !ISNULL(@corrected_value) AND LENGTH(TRIM(@corrected_value)) > 0 THEN
				CALL update_single_column_with_id(id, @corrected_value, @base_column_name, @table_name, @database_name);
				CALL insert_one_record_to_target_table_using_column_names(@origin_column_names, @target_column_names, id, @chinese_table, @target_database, @table_name, @database_name);
			ELSE
			/*if we do not find the proper value , we will insert it into the non chinese table*/
				CALL insert_one_record_to_target_table_using_column_names(@origin_column_names, @target_column_names, id, @non_chinese_table, @target_database, @table_name, @database_name);
			END IF;
		END IF;
	END IF;
END //
DELIMITER ;


/*
 * main procedure
 */
DROP PROCEDURE IF EXISTS split_table_to_chinese_and_non_chinese;
DELIMITER //
CREATE PROCEDURE split_table_to_chinese_and_non_chinese() 
BEGIN
	/*get max id*/
	SET @max_number = 0;
	SET @query_statement = CONCAT('SELECT MAX(id) INTO @max_number FROM ', @table_name);
	PREPARE query_statement FROM @query_statement;
	EXECUTE query_statement;
	DEALLOCATE PREPARE query_statement;

	/*according to @max_number, do correcting action for each tuple*/
	WHILE @max_number >= 0 DO
		SET @query_result = '';
		SET @get_record_statement = CONCAT('SELECT ', @base_column_name,' INTO @query_result FROM ', @table_name, ' WHERE id = ', @max_number);
		PREPARE get_record_statement FROM @get_record_statement;
		EXECUTE get_record_statement;
		DEALLOCATE PREPARE get_record_statement;
		
		/*if the result queried is not null value, then we need to */
		IF !ISNULL(@query_result) AND LENGTH(TRIM(@query_result)) > 0 THEN
			CALL processing_id_numbers_and_do_insertion(@max_number, @query_result);
		END IF;
	SET @max_number = @max_number - 1;
	END WHILE;
END // 
DELIMITER ;



/*
 * the entrance of whole procedure
 */
CALL split_table_to_chinese_and_non_chinese();