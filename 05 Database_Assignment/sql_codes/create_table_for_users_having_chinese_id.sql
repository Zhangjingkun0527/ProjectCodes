/* this procedure is defined to correct unreliable values in key columns */
SET GLOBAL log_bin_trust_function_creators = TRUE;
USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'cdsgus';
SET @target_table = 'users_owning_chinese_identity_card';
/*regelar expression for chinese id card which has 18 digits or 17digits with a letter*/
SET @chinese_id_18_numbers_regexp = '^[1-9][0-9]{5}(((18|19)[0-9]{2})|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}[0-9Xx]$';
SET @chinese_id_17_numbers_regexp = '^[1-9][0-9]{5}(((18|19)[0-9]{2})|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';
SET @chinese_id_15_numbers_regexp = '^[1-9][0-9]{5}[0-9]{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';

/*
 * this procedure is defined to create param table for verifying id
 */
DROP PROCEDURE IF EXISTS create_param_table;
DELIMITER //
CREATE PROCEDURE create_param_table()
BEGIN
	/*create validate table for verifying ids*/
	IF NOT EXISTS (SELECT TABLE_NAME FROM information_schema.`TABLES` WHERE TABLE_NAME = 'validate_params' AND TABLE_SCHEMA = @database_name) THEN
		CREATE TABLE validate_params (type VARCHAR(100) NOT NULL, CONSTRAINT PRIMARY KEY (type));
		/*we think that it's enough for adding 18 columns to the validate_params*/
		SET @count_of_columns = 17;
		WHILE @count_of_columns >= 0 DO
			SET @indexer = 18 - @count_of_columns;
			SET @column_name = CONCAT('param_', @indexer);
			IF NOT EXISTS (SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_SCHEMA = @database_name AND TABLE_NAME = 'validate_params' AND COLUMN_NAME = @column_name) THEN
				SET @add_column_statement = CONCAT('ALTER TABLE validate_params ADD COLUMN ', @column_name, ' VARCHAR(10)');
				PREPARE add_column_statement FROM @add_column_statement;
				EXECUTE add_column_statement;
				SET @count_of_columns = @count_of_columns - 1;
			END IF;
		END WHILE;
	END IF;
END//
DELIMITER ;
CALL create_param_table();



/*
 * this procedure is defined to calulate the verification code according to the 18 id numbers
 */
DROP PROCEDURE IF EXISTS calculate_verification_code_for_chinese_id;
DELIMITER //
CREATE PROCEDURE calculate_verification_code_for_chinese_id(IN id_number VARCHAR(17), OUT verification_code CHAR(1))
BEGIN
	IF id_number REGEXP @chinese_id_17_numbers_regexp THEN
		/*id has 17 numbers needed to be verified*/
			SET @indexer = 17;
			SET @sum_of_validate_numbers = 0;
			WHILE @indexer > 0 DO
				/*query param using dynamic sql*/
				SET @tmp_before_verifying = '';
				SET @verify_code = 18 - @indexer;
				SET @column_name_from_verify_code = CONCAT('param_', @verify_code);
				SET @query_param_statement = CONCAT('SELECT ', @column_name_from_verify_code,' INTO @tmp_before_verifying FROM validate_params WHERE type = \'chinese_id_18_before_verifying\'');
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
 * this function is defined to convert id having 15 numbers to 18numbers and if the 15numbers is not validated then   
 * return empty string
 */
DROP PROCEDURE IF EXISTS convert_15_to_18_for_id_number;
DELIMITER //
CREATE PROCEDURE convert_15_to_18_for_id_number (IN id_number VARCHAR(15), OUT result VARCHAR(18)) 
	BEGIN
		IF id_number REGEXP @chinese_id_15_numbers_regexp THEN
			/*insert 19 to the 15 id numbers*/
			SET @tmp = CONCAT(SUBSTRING(id_number, 1, 6), '19', SUBSTRING(id_number, 7));
			SET @verification_code = '';
			CALL calculate_verification_code_for_chinese_id(@tmp, @verification_code);
			SET @final_verification_code = '';
			SET @query_statement = CONCAT('SELECT param_', @verification_code, ' INTO @final_verification_code FROM validate_params WHERE type = \'chinese_id_18_for_verifying\'');
			PREPARE query_statement FROM @query_statement;
			EXECUTE query_statement;
			SET result = CONCAT(@tmp, @final_verification_code);
		ELSE
			SET result = '';
		END IF;
	END //
DELIMITER ;

SET @id_number = '410721940527001';
SET @tmp_result = '';
CALL convert_15_to_18_for_id_number(@id_number, @tmp_result);
SELECT @tmp_result;

/*
 * this function is defined to verify the id having 18 numbers or 17 numbers with a letter
 */
DROP PROCEDURE IF EXISTS is_id_18_numbers_validated;
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
			PREPARE get_param_statement FROM @get_param_statement;
			EXECUTE get_param_statement;
			DEALLOCATE PREPARE get_param_statement;
			
			/*compare query result and result of calculation*/
			SET @validate_number = SUBSTRING(id_number, 18, 1);
			SET result = @result_of_getting_param <=> IF(@validate_number <=> 'x', UPPER(@validate_number), @validate_number);
		ELSE
			SET result = FALSE;
		END IF;
	END//
DELIMITER ;



/*
 * secondly, define main procedure
 */
DROP PROCEDURE IF EXISTS correct_value_in_key_columns;
DELIMITER //
CREATE PROCEDURE correct_value_in_key_columns()
  BEGIN
    DECLARE flag INT DEFAULT FALSE;
    DECLARE tmp VARCHAR(255) DEFAULT '';
    /*get all column name of @table_name in database @database_name*/
    DECLARE result_cursor CURSOR FOR SELECT COLUMN_NAME
                                   FROM INFORMATION_SCHEMA.COLUMNS
                                   WHERE TABLE_NAME = @table_name AND TABLE_SCHEMA = @database_name;
    /*declare a continue handler, use finish while loop*/
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
    OPEN result_cursor;
    WHILE !flag DO
      FETCH result_cursor INTO tmp;
			/*processing all columns defined in @column_names*/
      IF !flag AND FIND_IN_SET(@column_names, tmp) THEN
      /*call the processing function*/
        CALL correct_value_by_inputing_column_name(tmp);
      END IF;
    END WHILE;
  END //
DELIMITER ;

/*CALL correct_value_in_key_columns();*/