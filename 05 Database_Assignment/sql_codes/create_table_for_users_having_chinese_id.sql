/* this procedure is defined to correct unreliable values in key columns */ 
/********Note: the main function is in the bottom of this file*******/
SET GLOBAL log_bin_trust_function_creators = TRUE;
USE test;
SET @database_name = 'test';
SET @table_name = 'student';
SET @target_table = 'users_owning_chinese_identity_card';

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
				SET @add_column_statement = CONCAT( 'ALTER TABLE validate_params ADD COLUMN ', @column_name, ' VARCHAR(10)' );
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
 * this procedure is defined to calulate the verification code according to the 18 id numbers
 */
DROP PROCEDURE IF	EXISTS calculate_verification_code_for_chinese_id;
DELIMITER //
CREATE PROCEDURE calculate_verification_code_for_chinese_id(IN id_number VARCHAR(17), OUT verification_code CHAR(1)) 
BEGIN
	IF id_number REGEXP @chinese_id_17_numbers_regexp THEN
		/*id has 17 numbers needed to be verified*/
		SET @indexer = 17;
		SET @sum_of_validate_numbers = 0;
		
		WHILE	@indexer > 0 DO
			/*query param using dynamic sql*/
			SET @tmp_before_verifying = '';
			SET @verify_code = 18 - @indexer;
			
			SET @column_name_from_verify_code = CONCAT('param_', @verify_code);
			SET @query_param_statement = CONCAT('SELECT ', @column_name_from_verify_code, ' INTO @tmp_before_verifying FROM validate_params WHERE type = \'chinese_id_18_before_verifying\'');
			PREPARE query_param_statement FROM @query_param_statement;
			EXECUTE query_param_statement;
			DEALLOCATE PREPARE query_param_statement;
		
			/*calculate the sum using for verification*/
			SET @tmp_value = CAST(@tmp_before_verifying AS UNSIGNED INTEGER);
			SET @each_number_in_id = CAST(SUBSTRING(id_number, 18 - @indexer, 1) AS UNSIGNED INTEGER);
			SET @sum_of_validate_numbers = @sum_of_validate_numbers + @tmp_value * @each_number_in_id;
			SET @indexer = @indexer - 1;
		END WHILE;
		
		/*this is the verification code by calculating*/
		SET verification_code = MOD(@sum_of_validate_numbers, 11) + 1;
	ELSE 
		SET verification_code = '';
	END IF;
END // 
DELIMITER ;



/*
 * this function is defined to determine whether the id_number with numbers is validated
 */
DROP FUNCTION IF EXISTS is_id_15_numbers_validated;
DELIMITER //
CREATE FUNCTION is_id_15_numbers_validated(id_number VARCHAR(15)) 
RETURNS SMALLINT 
BEGIN
	IF id_number REGEXP @chinese_id_15_numbers_regexp THEN
		/*get the city code and verify it*/
		SET @city_code_str = SUBSTRING( id_number, 1, 6 );
		SET @city_code = CAST( @city_code_str AS UNSIGNED INT );
		IF EXISTS (SELECT * FROM city_codes_chn WHERE `code` = @city_code) THEN
			RETURN TRUE;
		ELSE 
			RETURN FALSE;
		END IF;
	ELSE 
		RETURN FALSE;
	END IF;
END // 
DELIMITER ;



/*
 * this function is defined to convert id having 15 numbers to 18numbers and if the 15numbers is not validated then   
 * return empty string
 */
DROP PROCEDURE IF	EXISTS convert_15_to_18_for_id_number;
DELIMITER //
CREATE PROCEDURE convert_15_to_18_for_id_number(IN id_number VARCHAR(15), OUT result VARCHAR(18)) 
BEGIN
	IF id_number REGEXP @chinese_id_15_numbers_regexp THEN
		/*insert 19 to the 15 id numbers*/
		SET @tmp = CONCAT(SUBSTRING(id_number, 1, 6), '19', SUBSTRING( id_number, 7));
		SET @verification_code = '';
		CALL calculate_verification_code_for_chinese_id (@tmp, @verification_code);
		
		SET @final_verification_code = '';
		SET @query_statement = CONCAT( 'SELECT param_', @verification_code, ' INTO @final_verification_code FROM validate_params WHERE type = \'chinese_id_18_for_verifying\'' );
		PREPARE query_statement FROM @query_statement;
		EXECUTE query_statement;
		
		/*return the final result*/
		SET result = CONCAT(@tmp, @final_verification_code);
	ELSE 
		SET result = '';
	END IF;
END // 
DELIMITER ;



/*
 * this function is defined to verify the id having 18 numbers or 17 numbers with a letter
 */
DROP PROCEDURE IF	EXISTS is_id_18_numbers_validated;
DELIMITER //
CREATE PROCEDURE is_id_18_numbers_validated(IN id_number VARCHAR(18), OUT result SMALLINT(1)) 
BEGIN
	/*if the id_number is not a validated id having 18 numbers, then return false*/
	IF id_number REGEXP @chinese_id_18_numbers_regexp THEN
		SET @verify_code = '';
		CALL calculate_verification_code_for_chinese_id(SUBSTRING(id_number, 1, 17), @verify_code);
		
		/*get the verify code*/
		SET @column_name_from_verify_code = CONCAT('param_', @verify_code);
		SET @result_of_getting_param = '';
		SET @get_param_statement = CONCAT('SELECT ', @column_name_from_verify_code, ' INTO @result_of_getting_param FROM validate_params WHERE type = \'chinese_id_18_for_verifying\'');
		PREPARE get_param_statement	FROM @get_param_statement;
		EXECUTE get_param_statement;
		DEALLOCATE PREPARE get_param_statement;
		
		/*compare query result and result of calculation*/
		SET @validate_number = SUBSTRING(id_number, 18, 1);
		SET result = @result_of_getting_param <=> IF(@validate_number <=> 'x', UPPER(@validate_number), @validate_number);
	ELSE 
		SET result = FALSE;
	END IF;
END // 
DELIMITER ;


/*
 *this function is defined for remove elements which are not digit or letter x
 */
DROP FUNCTION IF EXISTS drop_non_digit_or_letter_x;
DELIMITER //
CREATE FUNCTION drop_non_digit_or_letter_x(str VARCHAR(255)) 
RETURNS VARCHAR(255) 
BEGIN
	/*get the string trimmed*/
	SET @tmp_str_trimmed = TRIM(str);
	SET @length_of_tmp = LENGTH(@tmp_str_trimmed);
	SET @indexer = 1;
	SET @result = '';
	
	/*remove the elements which are not digit or letter x */
	WHILE	@indexer <= @length_of_tmp DO
		SET @tmp = SUBSTRING(str, @indexer, 1);
		IF @tmp REGEXP '^[0-9Xx]' THEN
			SET @result = CONCAT(@result, @tmp);
		END IF;
		SET @indexer = @indexer + 1;
	END WHILE;

	RETURN @result;
END // 
DELIMITER ;

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
 * main procedure
 */
DROP PROCEDURE IF EXISTS create_table_for_users_having_chinese_id;
DELIMITER //
CREATE PROCEDURE create_table_for_users_having_chinese_id() 
BEGIN
	/*get max id*/
	SET @max_number = 0;
	SET @query_statement = CONCAT('SELECT MAX(id) INTO @max_number FROM ', @table_name);
	PREPARE query_statement FROM @query_statement;
	EXECUTE query_statement;
	DEALLOCATE PREPARE query_statement;
	
	/*according to @max_number, do correcting action for each tuple*/
	WHILE @max_number >= 0 DO
		
	END WHILE;
END // 
DELIMITER ;
/*CALL correct_value_in_key_columns();*/