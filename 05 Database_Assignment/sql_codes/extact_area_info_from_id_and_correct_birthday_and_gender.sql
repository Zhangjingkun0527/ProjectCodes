USE kaifang; 
SET @table_name = 'users_owning_taiwan_id_copy1';
SET @column_names_for_select = 'id, identity_number, gender, birthday';
SET @province_column_name = 'province';
SET @city_column_name = 'city';
SET @district_column_name = 'district';
SET @birthday_column_name = 'birthday';
SET @gender_column_name = 'gender';

DROP PROCEDURE IF EXISTS extact_area_info_from_id_and_correct_birthday_and_gender;
DELIMITER //
CREATE PROCEDURE extact_area_info_from_id_and_correct_birthday_and_gender()
BEGIN
	DECLARE tmp_id INT;
	DECLARE tmp_id_number VARCHAR(50);
	DECLARE tmp_gender VARCHAR(10);
	DECLARE tmp_birthday VARCHAR(20);
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE area_info VARCHAR(20);
	DECLARE birthday VARCHAR(20);
	DECLARE gender VARCHAR(10);
	
	DECLARE result_cursor CURSOR FOR SELECT * FROM tmp_view;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	CALL create_tmp_view_with_column_names_for_cursor(@column_names_for_select, @table_name, '');
	OPEN result_cursor;
	SET @province_tmp = '';
	SET @city_tmp = '';
	SET @district_tmp = '';
	for_continue_or_leave : WHILE !flag DO
	
		FETCH result_cursor INTO tmp_id, tmp_id_number, tmp_gender, tmp_birthday;
		IF is_column_value_null_or_empty_string(tmp_id_number) THEN
			ITERATE for_continue_or_leave;
		END IF;
		
		IF flag THEN
			LEAVE for_continue_or_leave;
		END IF;
		
		IF !flag THEN
			SET area_info = LEFT(tmp_id_number, 6);
			SET @query_province_city_district_sql = CONCAT('SELECT province_name, city_name, district_name INTO @province_tmp, @city_tmp, @district_tmp FROM city_codes_chn WHERE `code` = ', area_info);
			PREPARE query_province_city_district_sql FROM @query_province_city_district_sql;
			EXECUTE query_province_city_district_sql;
			DEALLOCATE PREPARE query_province_city_district_sql;

		/*correct gender*/
			SET gender = SUBSTRING(tmp_id_number, 17, 1);
			IF gender != 'X' THEN
				SET gender = IF(MOD(CAST(gender AS UNSIGNED INT), 2) <=> 0, '\'F\'', '\'M\'');
			ELSE
				SET gender = CONCAT('\'', UPPER(tmp_gender), '\'');
			END IF;
		
		/*correct birthday*/
			IF STRCMP(tmp_birthday,'19100101') <=> 1 THEN
				IF SUBSTRING(tmp_id_number, 7, 4) != 'XXXX' THEN
					SET birthday = CONCAT('\'',SUBSTRING(tmp_id_number, 7, 4), '-', SUBSTRING(tmp_id_number, 11, 2), '-', SUBSTRING(tmp_id_number, 13, 2), '\'');
				ELSE
					SET birthday = CONCAT('\'', tmp_birthday, '\'');
				END IF;
			ELSE 
				IF SUBSTRING(tmp_id_number, 7, 4) != 'XXXX' THEN
					SET birthday = CONCAT('\'',SUBSTRING(tmp_id_number, 7, 4), '-', SUBSTRING(tmp_id_number, 11, 2), '-', SUBSTRING(tmp_id_number, 13, 2), '\'');
				ELSE
					SET birthday = '\'\'';
				END IF;
			END IF;
		
		/*craete update sql*/
			SET @update_area_info_sql = CONCAT('UPDATE ', @table_name, ' SET ', @gender_column_name, ' = ', 
																				gender, ', ', @birthday_column_name, ' = ', birthday);
		/*if the area_info is not null then update*/
			IF !is_column_value_null_or_empty_string(@province_tmp) THEN
				SET @update_area_info_sql = CONCAT(@update_area_info_sql, 
																					', ', 
																					@province_column_name, 
																					' = \'', 
																					@province_tmp, '\'',
																					IF(is_column_value_null_or_empty_string(@city_tmp),
																										'',
																										CONCAT(', ', @city_column_name, ' = \'', @city_tmp, '\'')),
																					IF(is_column_value_null_or_empty_string(@district_tmp),
																										'',
																										CONCAT(', ', @district_column_name, ' = \'', @district_tmp, '\''))
																					);
			END IF;
			SET @update_area_info_sql = CONCAT(@update_area_info_sql, ' WHERE id = ', tmp_id);
			/*execute update sql*/
			PREPARE update_area_info_sql FROM @update_area_info_sql;
			EXECUTE update_area_info_sql;
			SET flag = FALSE;
		END IF;
	END WHILE;
END //
DELIMITER ;

CALL extact_area_info_from_id_and_correct_birthday_and_gender;