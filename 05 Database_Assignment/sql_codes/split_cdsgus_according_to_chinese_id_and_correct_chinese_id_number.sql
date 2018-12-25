/* this procedure is defined to correct unreliable values in key columns */ 
/********Note: the main function is in the bottom of this file*******/
SET GLOBAL log_bin_trust_function_creators = TRUE;
USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'users_not_owning_chinese_identity_card';
SET @target_database = ' kaifang';
/*@base_column_name is judgment standard for split tabel, and alse the most important column*/
SET @base_column_name = 'identity_number';
SET @birthday_column_name = 'Birthday';
SET @chinese_table = 'users_owning_chinese_identity_card_copy1';
SET @non_chinese_table = 'users_not_owning_chinese_identity_card_copy1';
SET @chinese_table_for_old_area_code = 'users_owning_old_chinese_identity_card_copy1';


SET @upper_bound_of_id = 1219032;
SET @lower_bound_of_id = 85960;


/*this variable is the set of column names of origin table which splited by comma*/
SET @origin_column_names = 'name, identity_number, gender, birthday, contact_address, zip, mobile, tel_number, email, nation, register_date, id_cdsgus';
/*this variable is the set of column names of target table which splited by comma*/
SET @target_column_names = 'name, identity_number, gender, birthday, contact_address, zip, mobile, tel_number, email, nation, register_date, id_cdsgus'; 

/*regelar expression*/
SET @chinese_id_18_numbers_regexp = '^[1-9][0-9]{5}((19[1-9][0-9])|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}[0-9Xx]$';

SET @chinese_id_17_numbers_regexp = '^[1-9][0-9]{5}((19[1-9][0-9])|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';

SET @chinese_id_15_numbers_regexp = '^[1-9][0-9]{5}[1-9][0-9]((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)[0-9]{3}$';

SET @the_yyyy_mm_dd_regexp = '^((19[1-9][0-9])|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)$';

SET @the_yy_mm_dd_regexp = '^[1-9][0-9]((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)$';

SET @fisrt_14_numbers_in_18_id_regexp = '^[1-9][0-9]{5}((19[1-9][0-9])|(200[0-9]))((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)$';

SET @first_12_numbers_in_15_id_regexp = '^[1-9][0-9]{5}[1-9][0-9]((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)$';

/*the enum of situation when verifying id having 18 numbers*/
SET @id_18_numbers_not_valid = 0;
SET @verification_code_not_valid = 1;
SET @id_18_numbers_valid = 2;

SET @repeat_character_for_filling = 'X';

/************************************************split line*********************************************************/
/*********************************below this line is the validation functions**************************************/

/*
 * this procedure is defined to calulate the verification code according to the 18 id numbers
 */
DROP PROCEDURE IF	EXISTS calculate_verification_code_for_chinese_id;
DELIMITER //
CREATE PROCEDURE calculate_verification_code_for_chinese_id(IN id_number VARCHAR(255), OUT verification_code VARCHAR(10)) 
BEGIN
	DECLARE indexer INT DEFAULT 17;
	DECLARE sum_of_validate_numbers INT DEFAULT 0;
	DECLARE verify_code INT;
	DECLARE column_name_from_verify_code VARCHAR(255);
	DECLARE tmp_value INT;
	DECLARE each_number_in_id INT;
	 
	IF id_number REGEXP @chinese_id_17_numbers_regexp THEN
		/*id has 17 numbers needed to be verified*/
		WHILE	indexer > 0 DO
			/*query param using dynamic sql*/
			SET verify_code = 18 - indexer;
			SET @tmp_before_verifying = '';
			SET column_name_from_verify_code = CONCAT('param_', verify_code);
			SET @query_param_statement = CONCAT('SELECT ', column_name_from_verify_code, ' INTO @tmp_before_verifying FROM validate_params WHERE type = \'chinese_id_18_before_verifying\'');
			PREPARE query_param_statement FROM @query_param_statement;
			EXECUTE query_param_statement;
			DEALLOCATE PREPARE query_param_statement;
			
			/*calculate the sum using for verification*/
			SET tmp_value = CAST(@tmp_before_verifying AS UNSIGNED INTEGER);
			SET each_number_in_id = CAST(SUBSTRING(id_number, 18 - indexer, 1) AS UNSIGNED INTEGER);
			SET sum_of_validate_numbers = sum_of_validate_numbers + tmp_value * each_number_in_id;
			SET indexer = indexer - 1;
		END WHILE;
		SET verification_code = MOD(sum_of_validate_numbers, 11) + 1;
		
		/*get the verify code*/
		SET column_name_from_verify_code = CONCAT('param_', verification_code);
		SET @result_of_getting_param = '';
		SET @get_param_statement = CONCAT('SELECT ', column_name_from_verify_code, ' INTO @result_of_getting_param FROM validate_params WHERE type = \'chinese_id_18_for_verifying\'');
		PREPARE get_param_statement	FROM @get_param_statement;
		EXECUTE get_param_statement;
		DEALLOCATE PREPARE get_param_statement;
		
		/*this is the verification code by calculating*/
		SET verification_code = @result_of_getting_param;
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
CREATE FUNCTION is_id_15_numbers_validated(id_number VARCHAR(255)) 
RETURNS SMALLINT 
BEGIN
	RETURN TRIM(id_number) REGEXP @chinese_id_15_numbers_regexp;
END // 
DELIMITER ;



/*
 * this function is defined to convert id having 15 numbers to 18numbers and if the 15numbers is not validated then return empty string
 * 
 */
DROP PROCEDURE IF	EXISTS convert_15_to_18_for_id_number;
DELIMITER //
CREATE PROCEDURE convert_15_to_18_for_id_number(IN id_number VARCHAR(255), OUT result VARCHAR(50)) 
BEGIN
	DECLARE tmp_first_17_numbers VARCHAR(30);
	DECLARE verification_code VARCHAR(5);
	
	IF id_number REGEXP @chinese_id_15_numbers_regexp THEN
		/*insert 19 to the 15 id numbers*/
		SET tmp_first_17_numbers = CONCAT(SUBSTRING(id_number, 1, 6), '19', SUBSTRING(id_number, 7));
		CALL calculate_verification_code_for_chinese_id(tmp_first_17_numbers, verification_code);
		
		/*return the final result*/
		SET result = CONCAT(tmp_first_17_numbers, verification_code);
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
CREATE PROCEDURE is_id_18_numbers_validated(IN id_number VARCHAR(255), OUT result SMALLINT(2), OUT corrected_id_number VARCHAR(50)) 
BEGIN
	DECLARE verificatoin_code VARCHAR(5);
	DECLARE validate_number VARCHAR(50);
	/*if the id_number is not a validated id having 18 numbers, then return false*/
	IF id_number REGEXP @chinese_id_18_numbers_regexp THEN
		CALL calculate_verification_code_for_chinese_id(SUBSTRING(id_number, 1, 17), verificatoin_code);
		
		/*compare query result and result of calculation*/
		SET validate_number = SUBSTRING(id_number, 18, 1);
		/*if the verification is not valid ,then we will joint the true veirifcation code into id_number for correcting*/
		IF verificatoin_code <=> IF(validate_number <=> 'x', UPPER(validate_number), validate_number) THEN
			SET result = @id_18_numbers_valid;
		ELSE
			SET result = @verification_code_not_valid;
			SET corrected_id_number = CONCAT(SUBSTRING(id_number, 1, 17), verificatoin_code);
		END IF;
	ELSE 
		SET result = @id_18_numbers_not_valid;
	END IF;
END // 
DELIMITER ;


DROP PROCEDURE IF EXISTS correct_id_processing_function_for_id_18_numbers;
DELIMITER //
CREATE PROCEDURE correct_id_processing_function_for_id_18_numbers(IN unvalid_value_cleared VARCHAR(50), OUT corrected_value VARCHAR(50)) 
BEGIN
	DECLARE the_first_17_numbers VARCHAR(50);
	DECLARE veirification_code VARCHAR(10);
	IF CHAR_LENGTH(unvalid_value_cleared) >= 17 THEN
		SET the_first_17_numbers = LEFT(unvalid_value_cleared, 17);
		CALL calculate_verification_code_for_chinese_id(the_first_17_numbers, veirification_code);
		
		IF !ISNULL(veirification_code) AND CHAR_LENGTH(veirification_code) > 0 THEN
			SET corrected_value = CONCAT(the_first_17_numbers, veirification_code);
		ELSE
			SET corrected_value = CONCAT(SUBSTRING(unvalid_value_cleared, 1, 14), REPEAT(@repeat_character_for_filling, 4));
		END IF;
	ELSE
		/*if the valid value*/
		SET corrected_value = CONCAT(unvalid_value_cleared, REPEAT(@repeat_character_for_filling, 18 - CHAR_LENGTH(unvalid_value_cleared)));
	END IF;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS correct_id_processing_function_for_id_15_numbers;
DELIMITER //
CREATE PROCEDURE correct_id_processing_function_for_id_15_numbers(IN unvalid_value_cleared VARCHAR(50), IN area_info VARCHAR(20), IN birthday VARCHAR(20), OUT corrected_value VARCHAR(50)) 
BEGIN
	DECLARE the_first_17_numbers VARCHAR(50);
	DECLARE veirification_code VARCHAR(10);
	DECLARE tmp_for_judge VARCHAR(5);
	SET tmp_for_judge = SUBSTRING(unvalid_value_cleared, 13, 3);
	IF ISNULL(tmp_for_judge) THEN
		SET corrected_value = CONCAT(area_info, birthday, REPEAT(@repeat_character_for_filling, 4));
	ELSE
		IF tmp_for_judge REGEXP '^[0-9]{3}$' THEN
			SET the_first_17_numbers = CONCAT(area_info, birthday, SUBSTRING(unvalid_value_cleared, 13, 3));
			CALL calculate_verification_code_for_chinese_id(the_first_17_numbers, veirification_code);
			SET corrected_value = CONCAT(the_first_17_numbers, veirification_code);
		ELSE
			SET corrected_value = CONCAT(area_info, birthday, REPEAT(@repeat_character_for_filling, 4));
		END IF;
	END IF;
END //
DELIMITER ;

/*
 *  this procedure is defined to deal with a type of id number, which is not valid by verifying, but its area code and birthday are valid
 */

DROP PROCEDURE IF EXISTS correct_id_with_valid_area_and_birthday_info;
DELIMITER //
CREATE PROCEDURE correct_id_with_valid_area_and_birthday_info(IN unvalid_value VARCHAR(255), IN id INT, IN column_name VARCHAR(255), IN table_name VARCHAR(255), IN database_name VARCHAR(255), IN is_from_other_column SMALLINT, OUT valid_id_number VARCHAR(255), OUT is_area_info_all_digits SMALLINT)
for_leave : BEGIN
	
	/*declare local variables*/
	DECLARE unvalid_value_cleared VARCHAR(255);
	DECLARE birthday VARCHAR(10);
	DECLARE area_info VARCHAR(10);
	DECLARE veirification_code VARCHAR(5) DEFAULT '';
	DECLARE the_first_17_numbers VARCHAR (30);
	DECLARE tmp_for_judge VARCHAR(5);
	DECLARE is_area_info_valid SMALLINT;
	
	/*drop all CHARACTERs which are not digits or letter x*/
	SET unvalid_value_cleared = drop_illegal_character(unvalid_value);
	/*if the area info is not valid then this id in not valid*/
	SET area_info = LEFT(unvalid_value_cleared, 6);
	/*if the area_info is valid but not all digits, then it must be unvalid id number, or it may be a valid area info, like some ids which have old area code*/
	SET is_area_info_valid = is_area_info_validated(area_info);
	IF !is_area_info_valid AND area_info REGEXP '^[0-9]{6}$' AND LEFT(area_info, 1) != '0' THEN
		SET birthday = SUBSTRING(unvalid_value_cleared, 7, 8);
		IF birthday REGEXP @the_yyyy_mm_dd_regexp THEN
			SET is_area_info_all_digits	= TRUE;
			CALL correct_id_processing_function_for_id_18_numbers(unvalid_value_cleared, valid_id_number);
		ELSE
			SET birthday = SUBSTRING(unvalid_value_cleared, 7, 6);
			IF birthday REGEXP @the_yy_mm_dd_regexp THEN
				SET is_area_info_all_digits	= TRUE;
				CALL correct_id_processing_function_for_id_15_numbers(unvalid_value_cleared, area_info, CONCAT('19', birthday), valid_id_number);
			ELSE	
				SET valid_id_number = unvalid_value;
				SET is_area_info_all_digits = is_from_other_column;
			END IF;
		END IF;
		LEAVE for_leave;
	ELSE
		IF !is_area_info_valid THEN
			SET valid_id_number = unvalid_value;
			SET is_area_info_all_digits = FALSE;
			LEAVE for_leave;
		END IF;
	END IF;
	
	/*firstly, let's consider the yyyy-mm-dd, if it's valid then the id number is useful for data analysis*/
	SET birthday = SUBSTRING(unvalid_value_cleared, 7, 8);
	IF birthday REGEXP @the_yyyy_mm_dd_regexp THEN
		CALL correct_id_processing_function_for_id_18_numbers(unvalid_value_cleared, valid_id_number);
	ELSE
		/*if the birthday is not a yyyy-mm-dd, then we will consider the yy-mm-dd*/
		SET birthday = SUBSTRING(unvalid_value, 7, 6); 
		IF birthday REGEXP @the_yy_mm_dd_regexp THEN
			SET birthday = CONCAT('19', birthday);
			/*if the birthday is a valid yy-mm-dd, then we should correct the value according to the remain contents*/
			CALL correct_id_processing_function_for_id_15_numbers(unvalid_value_cleared, area_info, birthday, valid_id_number);
		ELSE
			IF id < 1 THEN
				SET valid_id_number = CONCAT(area_info, REPEAT(@repeat_character_for_filling, 12)); 
				SET is_area_info_all_digits = TRUE;
				LEAVE for_leave;
			END IF;
			/*if the area_info is valid, however the birthday is not valid, the we will try to extact the birthday from cdgus.Birthday to fill*/
			SET @query_result = '';
			SET @query_statement  = CONCAT('SELECT ', column_name, ' INTO @query_result FROM ', database_name, '.', table_name, ' WHERE id = ', id);
			PREPARE query_statement FROM @query_statement;
			EXECUTE query_statement;
			DEALLOCATE PREPARE query_statement;
			/*if th birthday by querying is valid, then let it be part of id_number*/
			IF @query_result REGEXP @the_yyyy_mm_dd_regexp AND STRCMP(@query_result, '19100101') THEN
				SET valid_id_number = CONCAT(area_info, @query_result, REPEAT(@repeat_character_for_filling, 4));
			ELSE
				/*if the birthday is not valid, then */
				SET valid_id_number = CONCAT(area_info, REPEAT(@repeat_character_for_filling, 12));
			END IF;
		END IF;
	END IF;
	SET is_area_info_all_digits = TRUE;
END//
DELIMITER ;


/*
 *  this function is defined to judge whether the area info is valid according to the codes of cities we have.
 */
 DROP FUNCTION IF EXISTS is_area_info_validated;
DELIMITER //
CREATE FUNCTION is_area_info_validated(id_number VARCHAR(50)) 
RETURNS SMALLINT
BEGIN
	DECLARE area_info VARCHAR(10);
	SET area_info = LEFT(id_number, 6);
	IF !ISNULL(area_info) AND CHAR_LENGTH(TRIM(area_info)) > 0 THEN
		IF EXISTS (SELECT * FROM city_codes_chn WHERE `code` = area_info) THEN
			RETURN TRUE;
		ELSE 
			RETURN FALSE;
		END IF;
	ELSE
		RETURN FALSE;
	END IF;
END //
DELIMITER ;

/* test
SET @result = '';
CALL correct_the_unvalid_id_into_valid_id_having_18_numbers('320213196004165162', 0, '', '', '', @result);
SELECT @result;*/

/*
 * added in 2018-12-15, last attempt to correct id for CtfId value
 */
DROP PROCEDURE IF EXISTS last_attempt_to_correct_chinese_id;
DELIMITER //
CREATE PROCEDURE last_attempt_to_correct_chinese_id(IN id VARCHAR(50), OUT corrected_id VARCHAR(300), OUT is_area_info_valid SMALLINT)
for_leave : BEGIN

	DECLARE area_info VARCHAR(10);
	DECLARE birthday VARCHAR(10);
	DECLARE id_tmp VARCHAR(30);
	DECLARE tmp VARCHAR(50);
	DECLARE valid_result SMALLINT;
	DECLARE corrected_id_tmp VARCHAR(30);
	DECLARE indexer INT;
	DECLARE verification_info VARCHAR(30);
	DECLARE length INT;
	DECLARE index_of_verification_info INT;
	
	DECLARE birthday_selector INT DEFAULT 0;
	/*for indicating the situation of birthday*/
	DECLARE birthday_selector_1 INT DEFAULT 1;
	DECLARE birthday_selector_2 INT DEFAULT 2;
	
	IF CHAR_LENGTH(id) < 14 THEN
		LEAVE for_leave;
	END IF;
	
	/*if the area_info is not valid, then we do not need to do any improvement*/
	SET area_info = SUBSTRING(id, 1, 6);
	IF EXISTS (SELECT * FROM city_codes_chn WHERE `code` = area_info) THEN
		SET is_area_info_valid = TRUE;
	ELSE
		IF area_info REGEXP '^[0-9]{6}$' AND LEFT(area_info, 1) != '0' THEN
			SET is_area_info_valid = FALSE;
		ELSE
			SET is_area_info_valid = FALSE;
			SET corrected_id = '';
			LEAVE for_leave;
		END IF;
	END IF;
	
	SET tmp = SUBSTRING(drop_illegal_character(id), 7);
	/*for bithday, we consider only it may lack of the first number 1 or has redundant  number 1 for id having 18 numbers like 41072[]19940527 or like 410721[1]19940527*/
	SET birthday = CONCAT('1', SUBSTRING(tmp, 1, 7));
	IF birthday REGEXP @the_yyyy_mm_dd_regexp AND STRCMP(birthday, '19100101') THEN
		SET birthday_selector = birthday_selector_1;
		SET id_tmp = CONCAT(area_info, birthday, SUBSTRING(tmp, 8, 4));
		CALL is_id_18_numbers_validated(id_tmp, valid_result, corrected_id_tmp);
		IF valid_result <=> @id_18_numbers_valid THEN
			SET corrected_id = id_tmp;
			LEAVE for_leave;
		END IF;
	ELSE
		SET birthday = SUBSTRING(tmp, 2, 8);
		IF birthday REGEXP @the_yyyy_mm_dd_regexp AND STRCMP(birthday, '19100101') THEN
			SET birthday_selector = birthday_selector_2;
			SET id_tmp = CONCAT(area_info, birthday, SUBSTRING(tmp, 10, 4));
			CALL is_id_18_numbers_validated(id_tmp, valid_result, corrected_id_tmp);
			IF valid_result <=> @id_18_numbers_valid THEN
				SET corrected_id = id_tmp;
				LEAVE for_leave;				
			END IF;
		ELSE
			SET birthday = SUBSTRING(tmp, 1, 8);
			IF !(birthday REGEXP @the_yyyy_mm_dd_regexp) THEN
				SET corrected_id = CONCAT(area_info, REPEAT(@repeat_character_for_filling, 12));
				LEAVE for_leave;
			END IF;
		END IF;
	END IF;
	
	/*consider the verification info which may cause that id is not valid*/
	SET indexer = 1;
	SET index_of_verification_info = IF(birthday_selector <=> birthday_selector_1, 
																						8, 
																						IF(birthday_selector <=> birthday_selector_2, 10, 9));
	SET length = CHAR_LENGTH(SUBSTRING(tmp, index_of_verification_info));
	WHILE indexer <= length - 3 DO
		SET id_tmp = CONCAT(area_info, birthday, SUBSTRING(tmp, index_of_verification_info + indexer, 4));
		CALL is_id_18_numbers_validated(id_tmp, valid_result, corrected_id_tmp);
		IF valid_result <=> @id_18_numbers_valid THEN
			SET corrected_id = id_tmp;
			LEAVE for_leave;
		END IF;
		SET indexer = indexer + 1;
	END WHILE;
	
	SET corrected_id = CONCAT(area_info, birthday, REPEAT(@repeat_character_for_filling, 4));
END //
DELIMITER ;
/* test
SET @result = '';
SET @sdsdsd = 0;
CALL last_attempt_to_correct_chinese_id('370205968092055515', @result, @sdsdsd );
SELECT @result, @sdsdsd;


/***************************************split line*********************************************/
/********************************below this is the main procedure part*************************/


/*
 * this prodeure is trying to find the id number from other columns, this procedure is called by procedure 
 * find_id_number_from_other_columns.
 */
DROP PROCEDURE IF	EXISTS find_id_number_from_other_columns_processing_function;
DELIMITER //
CREATE PROCEDURE find_id_number_from_other_columns_processing_function(IN column_value VARCHAR(255), IN id INT, IN is_from_other_column SMALLINT, OUT id_number VARCHAR(255), OUT is_area_info_all_digits SMALLINT) 
for_leave_procedure : BEGIN
	
	DECLARE indexer INT DEFAULT 1;
	DECLARE str_cleared VARCHAR(1000);
	DECLARE length_of_str_cleared INT;
	DECLARE tmp_substr VARCHAR(30);
	DECLARE result SMALLINT;
	/*clear the tmp string, because it may have some chars which are not digits or letter x*/
	DECLARE corrected_18_id_number VARCHAR(50) DEFAULT '';
	DECLARE final_corrected_value VARCHAR(30) DEFAULT '';
	
	SET str_cleared = drop_illegal_character(column_value);
	SET length_of_str_cleared = CHAR_LENGTH(str_cleared);
	
	IF length_of_str_cleared >= 18 THEN
		/*extract the substr with 18 chars and verify it*/
		WHILE	indexer <= length_of_str_cleared - 17 DO
			SET tmp_substr = SUBSTRING(str_cleared, indexer, 18);
			
			/*verify the substring*/
			CALL is_id_18_numbers_validated(
						tmp_substr, 
						result, 
						corrected_18_id_number
						);
			
			/*if the substr is a validated id number then leave the procedure*/
			IF result <=> @id_18_numbers_valid THEN
				SET id_number = tmp_substr;
				SET is_area_info_all_digits = TRUE;
				LEAVE for_leave_procedure;
			ELSE
				IF result <=> @verification_code_not_valid THEN
					SET id_number = corrected_18_id_number;
					SET is_area_info_all_digits = TRUE;
					LEAVE for_leave_procedure;
				END IF;
				/*for each tmp_str with 18 numbers, if the verification failed, we should consider the situation: it has a valid area info and a valid birthday*/
				SET final_corrected_value = '';
				CALL correct_id_with_valid_area_and_birthday_info(
							tmp_substr, 
							id, 
							@birthday_column_name, 
							@table_name, 
							@database_name, 
							is_from_other_column,
							final_corrected_value,
							is_area_info_all_digits
							);
				IF CHAR_LENGTH(final_corrected_value) > 0 AND final_corrected_value != tmp_substr THEN 
					SET id_number = final_corrected_value;
					LEAVE for_leave_procedure;
				END IF;
			END IF;
		
			SET indexer = indexer + 1;
		END WHILE;
		
		/*if we do not find the validated id number having 18 numbers, then we should try to find the id number with 15 numbers and convert them to 18 id number*/
		SET indexer = 1;
		WHILE	indexer <= length_of_str_cleared - 14 DO
			SET tmp_substr = SUBSTRING(str_cleared, indexer, 15);
			IF is_id_15_numbers_validated(tmp_substr) THEN
				CALL convert_15_to_18_for_id_number(tmp_substr, id_number);
				SET is_area_info_all_digits = TRUE;
				LEAVE for_leave_procedure;
			ELSE
				/*for each tmp_str with 15 numbers, if the verification failed, we should consider the situation: it has a valid area info and a valid birthday*/
				SET final_corrected_value = '';
				CALL correct_id_with_valid_area_and_birthday_info(
							tmp_substr, 
							id, 
							@birthday_column_name, 
							@table_name, 
							@database_name,
							is_from_other_column,	
							final_corrected_value,
							is_area_info_all_digits
							);
				IF CHAR_LENGTH(final_corrected_value) > 0 AND final_corrected_value !=  tmp_substr THEN 
					SET id_number = final_corrected_value;
					LEAVE for_leave_procedure;
				END IF;
			END IF;
			
			SET indexer = indexer + 1;
		END WHILE;	
	/*there may exists valid number which has valid area_ifo and valid birthday in 15 or 18 id*/
	ELSE
		IF length_of_str_cleared >= 14 THEN
			SET indexer = 1;
			WHILE indexer <= length_of_str_cleared - 13 DO
				SET tmp_substr = SUBSTRING(str_cleared, indexer, 14);
				IF tmp_substr REGEXP @fisrt_14_numbers_in_18_id_regexp THEN
					SET final_corrected_value = '';
					CALL correct_id_with_valid_area_and_birthday_info(
								tmp_substr, 
								id, 
								@birthday_column_name, 
								@table_name, 
								@database_name,
								is_from_other_column,
								final_corrected_value,
								is_area_info_all_digits
								);
					IF CHAR_LENGTH(final_corrected_value) > 0 AND final_corrected_value !=  tmp_substr THEN 
						SET id_number = final_corrected_value;
						LEAVE for_leave_procedure;
					END IF;
				END IF;
				SET indexer = indexer + 1;
			END WHILE;
		END IF;
		
		IF length_of_str_cleared >= 12 THEN
			SET indexer = 1;
			WHILE indexer <= length_of_str_cleared - 11 DO
				SET tmp_substr = SUBSTRING(str_cleared, indexer, 12);
				IF tmp_substr REGEXP @fisrt_12_numbers_in_15_id_regexp THEN
					SET final_corrected_value = '';
					CALL convert_15_to_18_for_id_number(str_cleared, tmp_substr);
					CALL correct_id_with_valid_area_and_birthday_info(
								tmp_substr, 
								id, 
								@birthday_column_name, 
								@table_name, 
								@database_name,
								is_from_other_column,	
								final_corrected_value,
								is_area_info_all_digits
								);
					IF CHAR_LENGTH(final_corrected_value) > 0 AND final_corrected_value !=  tmp_substr THEN 
						SET id_number = final_corrected_value;
						LEAVE for_leave_procedure;
					END IF;
				END IF;
				SET indexer = indexer + 1;
			END WHILE;
		END IF;
	END IF;
END // 
DELIMITER ;



/*
 * this procedure is defined to query result by id in cdsgus, and put into tmp_view for realizing dynamic cursor
 */
DROP PROCEDURE IF	EXISTS find_id_number_from_other_columns;
DELIMITER //
CREATE PROCEDURE find_id_number_from_other_columns(IN id INT, OUT id_number VARCHAR(255), OUT is_area_info_all_digits SMALLINT) 
for_leave_procedure : BEGIN

	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE tmp VARCHAR(255) DEFAULT '';
	DECLARE id_number_extracted VARCHAR(30) DEFAULT '';
	/*get all columns in @table_name*/
	DECLARE columns_cursor CURSOR FOR SELECT COLUMN_NAME 
																		FROM information_schema.`COLUMNS` 
																		WHERE TABLE_NAME = @table_name AND 	
																		TABLE_SCHEMA = @database_name;
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

			/*for id column, we don't need to concern it*/
			IF tmp != 'id' AND tmp != @base_column_name THEN
				SET id_number_extracted = '';		
				CALL find_id_number_from_other_columns_processing_function(
							@query_result, 
							id, 
							tmp <=> @base_column_name, 
							id_number_extracted, 
							is_area_info_all_digits);
					
				/*if the @id_number_extracted is not null, then mission is completed*/
				IF !ISNULL(id_number_extracted) AND CHAR_LENGTH(id_number_extracted) > 0 THEN
					SET id_number = id_number_extracted;
					LEAVE for_leave_procedure;					
				END IF;
			END IF;
		END IF;
	END WHILE;
	SET id_number = '';
END // 
DELIMITER ; 
/* test
SET @result = '';
CALL find_id_number_from_other_columns(75778, @result);
SELECT @result;*/

/* 
 * *****This procedure is procedure which owns the main processing logic*****
 *
 * this procedure is the main processing part in main procedure. The cause of creation is to 
 * reduce the complexity of main procedure
 */
DROP PROCEDURE IF EXISTS processing_id_numbers_and_do_insertion;
DELIMITER //
CREATE PROCEDURE processing_id_numbers_and_do_insertion(IN id INT, IN str VARCHAR(255))
for_leave : BEGIN

	DECLARE corrected_id_having_18_numbers VARCHAR(50) DEFAULT '';
	DECLARE is_a_validated_id_number_having_18_numbers SMALLINT;
	DECLARE converted_to_18_numbers VARCHAR(30) DEFAULT '';
	DECLARE corrected_value VARCHAR(30) DEFAULT '';
	DECLARE is_area_info_all_digits SMALLINT;
	/*firstly, we will judge whether str is a valid id number having 18 numbers*/
	CALL is_id_18_numbers_validated(
				str,
				is_a_validated_id_number_having_18_numbers,
				corrected_id_having_18_numbers
				);
	/*firstly, we need to judge whether the string is a 18 id number, according to regular expression*/
	IF is_a_validated_id_number_having_18_numbers <=> @id_18_numbers_valid THEN
		/*if the it's validated, then we will add the record into the new table*/
		CALL insert_one_record_to_target_table_using_column_names(
					@origin_column_names, 
					@target_column_names, 
					id, 
					IF(is_area_info_validated(str), 
								@chinese_table, @chinese_table_for_old_area_code),
					@target_database, 
					@table_name, 
					@database_name
					);
	ELSE
		IF is_a_validated_id_number_having_18_numbers <=> @verification_code_not_valid THEN	
			CALL update_single_column_with_id(
						id, 
						corrected_id_having_18_numbers, 
						@base_column_name, 
						@table_name, 
						@database_name
						);
			CALL insert_one_record_to_target_table_using_column_names(
						@origin_column_names, 
						@target_column_names, 
						id, 
						IF(is_area_info_validated(corrected_id_having_18_numbers),
									@chinese_table, 
									@chinese_table_for_old_area_code),
						@target_database, 
						@table_name, 
						@database_name
						);
			LEAVE for_leave;
		END IF;
		/*if the id number is not a 18 id number, and we need to judge whether the id number is a 15 id number*/
		IF is_id_15_numbers_validated(str) THEN
			/*if the id numbr is a 15 id number according to regular expression*/
			CALL convert_15_to_18_for_id_number(str, converted_to_18_numbers);
			CALL update_single_column_with_id(
						id, 
						converted_to_18_numbers, 
						@base_column_name, 
						@table_name, 
						@database_name
						);		
			CALL insert_one_record_to_target_table_using_column_names(
						@origin_column_names, 
						@target_column_names, 
						id, 
						IF(is_area_info_validated(converted_to_18_numbers),
									@chinese_table, @chinese_table_for_old_area_code),
						@target_database, 
						@table_name, 
						@database_name
						);
						
		ELSE
			/*if the value is not a validated id number, so we need to try to find value from other columns*/
			CALL find_id_number_from_other_columns(id, corrected_value, is_area_info_all_digits);
			/*if we find the proper value, then update the origin table, and insert it into the chinese table*/
			IF !ISNULL(corrected_value) AND CHAR_LENGTH(corrected_value) > 0 AND is_area_info_all_digits <=> TRUE THEN
				CALL update_single_column_with_id(
							id, 
							corrected_value, 
							@base_column_name, 
							@table_name, 
							@database_name
							);
				CALL insert_one_record_to_target_table_using_column_names(
							@origin_column_names, 
							@target_column_names, 
							id, 
							IF(is_area_info_validated(corrected_value),
									@chinese_table, @chinese_table_for_old_area_code),
							@target_database, 
							@table_name, 
							@database_name
							);
			ELSE
				/*this is the last attempt to correct CtfId*/
				CALL last_attempt_to_correct_chinese_id(str, corrected_value, is_area_info_all_digits);
				IF CHAR_LENGTH(corrected_value) > 0 THEN
					CALL update_single_column_with_id(
								id, 
								corrected_value, 
								@base_column_name, 
								@table_name, 
								@database_name
								);
					CALL insert_one_record_to_target_table_using_column_names(
							@origin_column_names, 
							@target_column_names, 
							id, 
							IF(is_area_info_validated(corrected_value),
									@chinese_table, @chinese_table_for_old_area_code),
							@target_database, 
							@table_name, 
							@database_name
							);
				ELSE
					
					/*if we do not find the proper value, we will insert it into the non chinese table*/
					CALL insert_one_record_to_target_table_using_column_names(
								@origin_column_names, 
								@target_column_names, 
								id, 
								@non_chinese_table, 
								@target_database, 
								@table_name, 
								@database_name
								);
				END IF;
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
	
	DECLARE indexer INT;
	SET indexer = @upper_bound_of_id;
	/*according to @max_number, do correcting action for each tuple*/
	WHILE indexer >= @lower_bound_of_id DO
		SET @query_result = '';
		SET @get_record_statement = CONCAT('SELECT ', @base_column_name,' INTO @query_result FROM ', @table_name, ' WHERE id = ', indexer);
		PREPARE get_record_statement FROM @get_record_statement;
		EXECUTE get_record_statement;
		DEALLOCATE PREPARE get_record_statement;
		
		/*if the result queried is not null value, then we need to */
		IF !ISNULL(@query_result) AND LENGTH(TRIM(@query_result)) > 0 THEN
			 CALL processing_id_numbers_and_do_insertion(indexer, @query_result);
		END IF;
		
		SET indexer = indexer - 1;
	END WHILE;
END // 
DELIMITER ;


/*
 * the entrance of whole procedure
 */
CALL split_table_to_chinese_and_non_chinese();