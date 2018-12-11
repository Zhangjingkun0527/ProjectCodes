/*
 *  this query is created for verifying chinese id number, which difined some useful relevant procedures or functions
 */

SET GLOBAL log_bin_trust_function_creators = TRUE;
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
 * this function is defined to convert id having 15 numbers to 18numbers and if the 15numbers is not validated then return empty string
 * 
 */
DROP PROCEDURE IF	EXISTS convert_15_to_18_for_id_number;
DELIMITER //
CREATE PROCEDURE convert_15_to_18_for_id_number(IN id_number VARCHAR(15), OUT result VARCHAR(18)) 
BEGIN
	IF id_number REGEXP @chinese_id_15_numbers_regexp THEN
		/*insert 19 to the 15 id numbers*/
		SET @tmp = CONCAT(SUBSTRING(id_number, 1, 6), '19', SUBSTRING( id_number, 7));
		SET @verification_code = '';
		CALL calculate_verification_code_for_chinese_id(@tmp, @verification_code);
		
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