/**/
DROP PROCEDURE IF EXISTS delete_all_non_valid_record_in_old_id_table;
DELIMITER //
CREATE PROCEDURE delete_all_non_valid_record_in_old_id_table()
BEGIN
	DECLARE tmp VARCHAR(50);
	DECLARE tmp_id INT;
	DECLARE count INT DEFAULT 0;
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE for_stop INT DEFAULT 0;
	DECLARE result_cursor CURSOR FOR SELECT LEFT(identity_number, 6), id FROM users_owning_old_chinese_identity_card;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	OPEN result_cursor;
	WHILE !flag DO
		FETCH result_cursor INTO tmp, tmp_id;
		IF NOT EXISTS (SELECT * FROM city_codes_chn WHERE `code` = tmp) THEN
			INSERT INTO useless_records_which_come_from_old_chinese_id_table (SELECT * FROM users_owning_old_chinese_identity_card WHERE id = tmp_id);
			DELETE FROM users_owning_old_chinese_identity_card WHERE id = tmp_id;
			SET count = count + 1;
		END IF;
		SET for_stop = for_stop + 1;
	END WHILE;
	SELECT count, for_stop;
END //
DELIMITER ;

CALL delete_all_non_valid_record_in_old_id_table();