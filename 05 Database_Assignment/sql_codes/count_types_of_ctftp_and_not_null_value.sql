/* this procedure is defined to get all types of certificate using to register and number of nut null values of each type*/

USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'cdsgus';
SET @column_name_of_type = 'CtfTp';
SET @column_name_of_value = 'CtfId';

/*create TEMPORARY table for storing count result*/
DROP TABLE IF EXISTS tmp_table;
CREATE TABLE tmp_table (id_table INT(10) NOT NULL);

DROP PROCEDURE IF EXISTS get_distinct_values;
DELIMITER //
CREATE PROCEDURE get_distinct_values()
  BEGIN
		DROP VIEW IF EXISTS tmp_view;
    /*get all column name of @table_name in database @database_name*/
		SET @dynamic_cursor_sql = CONCAT('CREATE VIEW tmp_view AS SELECT DISTINCT ', @column_name_of_type, ' FROM ', @table_name);
		/*execute sql with cursor*/
		PREPARE dynamic_cursor_sql FROM @dynamic_cursor_sql;
		EXECUTE dynamic_cursor_sql;
		DEALLOCATE PREPARE dynamic_cursor_sql;
		CALL count_not_null_values();
  END //
DELIMITER ;

DROP PROCEDURE IF EXISTS count_not_null_values;
DELIMITER //
CREATE PROCEDURE count_not_null_values()
	BEGIN
		/*create dynamic cursor*/
		DECLARE flag INT DEFAULT FALSE;
    DECLARE tmp VARCHAR(255) DEFAULT '';
		DECLARE dynamic_cursor CURSOR FOR SELECT * FROM tmp_view;	
		/*declare a continue handler ,use finish while loop*/
		DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
		
		SET @count_statement = 'SELECT ';
		SET @alter_statement = 'ALTER TABLE tmp_table ADD COLUMN ';
		SET @result_of_count = 0;
		/*these two variables are defined to deal with dupilcate column name*/
		SET @duplicate_process = 1;
		SET @is_duplicate_showed = FALSE;
		/*open cursor for getting result*/
	  OPEN dynamic_cursor;
    WHILE !flag DO
      FETCH dynamic_cursor INTO tmp;
      IF !flag THEN
      /*according to the distinct type to add column to tem_table*/
				IF ISNULL(tmp) || LENGTH(TRIM(tmp)) < 1 THEN
					/*create count statement fror null type*/
					SET @count_statement = CONCAT(@count_statement, ' SUM(CASE WHEN ', @column_name_of_value,' IS NOT NULL AND 		LENGTH(TRIM(', @column_name_of_value, ')) > 0 THEN 1 ELSE 0 END) INTO @result_of_count FROM ', @table_name, ' WHERE ', @column_name_of_type, ' IS NULL OR LENGTH(TRIM(', @column_name_of_type, ')) < 1');
					
					/*create column for null type into tmp_table, and set default value = 0*/
					SET @alter_statement = CONCAT(@alter_statement, 'null_type INT(10)');
				ELSE
					SET @count_statement = CONCAT(@count_statement, ' SUM(CASE WHEN ', @column_name_of_value,' IS NOT NULL AND 		LENGTH(TRIM(', @column_name_of_value, ')) > 0 THEN 1 ELSE 0 END) INTO @result_of_count FROM ', @table_name, ' WHERE ', @column_name_of_type, ' = ', CONCAT('\'', tmp, '\''));
					/*create column for not null type into tmp_table, and set default value = 0*/
					IF EXISTS (SELECT * FROM information_schema.`COLUMNS` WHERE COLUMN_NAME = tmp AND TABLE_NAME = 'tmp_table') THEN
						/*deal with the duplicate column problem*/
						SET @alter_statement = CONCAT(CONCAT('ALTER TABLE tmp_table ADD COLUMN `', tmp), @duplicate_process,'` INT(10)');
						SET @is_duplicate_showed = TRUE;
					ELSE
						SET @alter_statement = CONCAT(@alter_statement, CONCAT('`', tmp, '`'), ' INT(10)');
					END IF;
				END IF;
				PREPARE count_statement FROM @count_statement;
				EXECUTE count_statement;
				DEALLOCATE PREPARE count_statement;

				/*execute alter statement in tmp_table*/
				PREPARE alter_statement FROM @alter_statement;
				EXECUTE alter_statement;
				
				/*if the tuple already exists, then update according to tmp, or insert a new tuple with id equals 0*/
				IF EXISTS (SELECT * FROM tmp_table WHERE id_table = 1) THEN
					SET @update_statement = CONCAT('UPDATE tmp_table SET ', IF(ISNULL(tmp) || LENGTH(TRIM(tmp)) < 1, 'null_type', CONCAT('`', tmp, IF(@is_duplicate_showed, @duplicate_process, ''), '`')), ' = ', @result_of_count, ' WHERE id_table = 1');
				ELSE
					SET @update_statement = CONCAT('INSERT INTO tmp_table(id_table,', IF(ISNULL(tmp) || LENGTH(TRIM(tmp)) < 1, 'null_type', CONCAT('`', tmp, '`')), ') VALUES (1,', @result_of_count, ')');
				END IF;
				
				PREPARE update_statement FROM @update_statement;
				EXECUTE update_statement;
      END IF;
			SET @count_statement = 'SELECT ';
			SET @alter_statement = 'ALTER TABLE tmp_table ADD COLUMN ';
			IF @is_duplicate_showed THEN
				SET @duplicate_process = @duplicate_process + 1;
				SET @is_duplicate_showed = FALSE;
			END IF;
    END WHILE;
		/*output all count result*/
    SELECT * FROM tmp_table;
		CLOSE dynamic_cursor;
	END //
DELIMITER ;

CALL get_distinct_values();
DROP TABLE IF EXISTS tmp_table;