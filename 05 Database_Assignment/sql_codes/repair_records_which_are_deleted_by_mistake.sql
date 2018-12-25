DROP PROCEDURE IF EXISTS repair_records_deleted_by_mistake;
DELIMITER //
CREATE PROCEDURE repair_records_deleted_by_mistake()
BEGIN
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE tmp VARCHAR(255);
	DECLARE count INT DEFAULT 0;
	DECLARE result_cursor CURSOR FOR SELECT id FROM cdsgus WHERE id >= 14000001 AND id <= 14010000;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	OPEN result_cursor;
	WHILE !flag DO
		FETCH result_cursor INTO tmp;
		IF NOT EXISTS (SELECT id_cdsgus FROM users_owning_chinese_identity_card WHERE id_cdsgus = tmp) THEN
			IF NOT EXISTS (SELECT id_cdsgus FROM users_owning_old_chinese_identity_card WHERE id_cdsgus = tmp)  THEN
					INSERT INTO users_not_owning_chinese_identity_card
						(`name`, identity_number, gender, birthday, contact_address, zip, mobile, tel_number, email, 
							nation, register_date, id_cdsgus) 
						(SELECT `Name`, CtfId, Gender, Birthday, Address, Zip, Mobile, Tel, EMail, Nation, Version, id 
						FROM cdsgus 
						WHERE id = tmp);	
						SET count = count + 1;
			END IF;
		END IF;
	END WHILE;
	SELECT count;
END //
DELIMITER ;

CALL repair_records_deleted_by_mistake;