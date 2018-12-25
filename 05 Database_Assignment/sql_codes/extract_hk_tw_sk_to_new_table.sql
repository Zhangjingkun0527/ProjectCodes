/*this file is trying to find all user from Honkong, Tai Wan or South Korea, and put them into the corresponding table*/

USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'users_not_owning_chinese_identity_card';
SET @hongkong_id_table_name = 'users_owning_hongkong_id';
SET @hongkong_reentry_permit_table_name = 'users_owning_hongkong_reentry_permit';

SET @hongkong_id_regexp = '^[A-Z|a-z][0-9]{6}[0-9]$';
SET @taiwan_id_regexp = '^[a-z|A-Z][0-9]{9}$';
SET @hongkong_reentry_permit_regexp = '^[H|h][0-9]{10}$';
SET @macao_reentry_permit_regexp = '^[M|m][0-9]{10}$';
SET @taiwan_reentry_permit_regexp = '^[0-9]{10}[A-Z|a-z]$';

/*
 * this procedure is trying to verify the hongkong id which pass the regular verification
 */
DROP PROCEDURE IF EXISTS is_hongkong_id_valid;
DELIMITER //
CREATE PROCEDURE is_hongkong_id_valid(IN hongkong_id VARCHAR(50), OUT result SMALLINT)
BEGIN
	DECLARE indexer INT DEFAULT 1;
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE factor INT;
	DECLARE param INT;
	DECLARE sum INT DEFAULT 0;
	DECLARE substr VARCHAR(10);
	DECLARE validate_number INT;
	DECLARE result_cursor CURSOR FOR SELECT * FROM validate_params WHERE type = 'hongkong_id_for_verifying';
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	OPEN result_cursor;
	WHILE !flag DO
		FETCH result_cursor INTO factor;
		SET substr = SUBSTRING(hongkong_id, indexer, 1);
		IF indexer <=> 1 THEN
			SET param = ASCII(substr) - ASCII('A') + 1;
			SET sum = sum + param * 8;
		ELSE
			IF indexer <= 7 THEN
				SET param = CAST(substr AS UNSIGNED INT);
				SET sum = sum * (7 + indexer - 2);
			ELSE
				SET param = IF(UPPER(substr) <=> 'A', 1, CAST(param AS UNSIGNED INT));
				SET validate_number = MOD(sum, 11);
				IF param <=> 0 THEN
					SET result = validate_number <=> 0;
				ELSE
					IF param <=> 1 THEN
						SET result = validate_number <=> 1;
					ELSE
						SET result = 11 - validate_number <=> param;
					END IF;
				END IF;
			END IF;
		END IF;
		SET indexer = indexer + 1;
	END WHILE;
END //
DELIMITER ;


DELIMITER //
CREATE PROCEDURE is_taiwan_id_valid(IN taiwan_id VARCHAR(50), OUT result SMALLINT)
BEGIN
	DECLARE indexer INT DEFAULT 1;
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE factor INT;
	DECLARE param INT;
	DECLARE sum INT DEFAULT 0;
	DECLARE substr VARCHAR(10);
	DECLARE validate_number INT;
	DECLARE result_cursor CURSOR FOR SELECT * FROM validate_params WHERE type = 'taiwan_id_8_numbers_for_verifying';
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	/*find the number which correspond to the first letter*/
	SET substr = SUBSTRING(taiwan_id, indexer, 1);
	SET @tmp_param = '';
	SET @query_sql_for_first_letter_of_taiwan_id = CONCAT('SELECT param_', ASCII(substr) - ASCII('A') + 1, ' INTO @tmp_param FROM validate_params WHERE type = taiwan_id_first_letter_for_verifying');
	PREPARE query_sql_for_first_letter_of_taiwan_id FROM @query_sql_for_first_letter_of_taiwan_id;
	EXECUTE query_sql_for_first_letter_of_taiwan_id;
	DEALLOCATE PREPARE query_sql_for_first_letter_of_taiwan_id
	SET sum = CAST(@tmp_param AS UNSIGNED INT);
	
	OPEN result_cursor;
	WHILE !flag DO
		FETCH param1_cursor INTO factor;
		
		IF indexer <=> 1 THEN
			
		END IF;
		SET indexer = indexer + 1;
	END WHILE;

END //
DELIMITER ;


/*
 * this procedure is defined to processing all all identity_numbers, and classfy them, then insert the record into
 * target table
 */
DELIMITER //
CREATE PROCEDURE main_processing_function(IN id VARCHAR(20), IN identity_number VARCHAR(255))
for_leave : BEGIN

	DECLARE id_number_cleared VARCHAR(255);
	DECLARE validation_result SMALLINT;
	
	SET id_number_cleared = remove_brackets(drop_illegal_character(identity_number));
	/*processing hongkong id number*/
	IF id_number_cleared REGEXP @hongkong_id_regexp THEN
		CALL is_hongkong_id_valid(id_number_cleared, validation_result);
		IF validation_result THEN
			SET @insert_sql = CONCAT('INSERT INTO ', @hongkong_id_table_name, ' (SELECT * FROM ', @table_name, ' WHERE id = ', id);
			PREPARE insert_sql FROM @insert_sql;
			EXECUTE insert_sql;
			LEAVE for_leave;
		END IF;
	END IF;
	
	/*processing taiwan id number*/
	IF id_number_cleared REGEXP @taiwan_id_regexp THEN
		
	END IF;
	
	
END //
DELIMITER ;

/*
 * main procedure, the entrance of this program
 */
DROP PROCEDURE IF EXISTS extact_hk_tw_sk_to_new_table;
DELIMITER //
CREATE PROCEDURE extact_hk_tw_sk_to_new_table()
BEGIN
	DECLARE tmp VARCHAR(255);
	DECLARE tmp_id INT(10);
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE result_cursor CURSOR FOR SELECT * FROM tmp_view;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	CALL create_tmp_view_with_multi_columns_for_cursor('id, identity_number', @table_name, '');
	OPEN result_cursor;
	WHILE !flag DO
		FETCH result_cursor INTO tmp_id, tmp;
		IF !is_column_value_null_or_empty_string(tmp) THEN
			CALL main_processing_function(tmp_id, tmp);
		END IF;
	END WHILE;
END //
DELIMITER ;

CALL extact_hk_tw_sk_to_new_table();