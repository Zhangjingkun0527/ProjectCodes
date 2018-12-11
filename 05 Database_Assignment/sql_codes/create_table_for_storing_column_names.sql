SET @database_name = 'kaifang';

DROP PROCEDURE IF EXISTS create_table_for_storing_column_name;
DELIMITER //
CREATE PROCEDURE create_table_for_storing_column_name() 
BEGIN
	/*create validate table for verifying ids*/
	IF NOT EXISTS (SELECT TABLE_NAME FROM information_schema.`TABLES` WHERE TABLE_NAME = 'column_names_for_insertion' AND TABLE_SCHEMA = @database_name) THEN
		CREATE TABLE column_names_for_insertion (type VARCHAR (100) NOT NULL, CONSTRAINT PRIMARY KEY (type));
		/*we think that it's enough for adding 18 columns to the validate_params*/
		SET @count_of_columns = 32;
		WHILE	@count_of_columns >= 0 DO
			SET @indexer = 33 - @count_of_columns;
			SET @column_name = CONCAT('column_name_', @indexer);
			IF NOT EXISTS (SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_SCHEMA = 'kaifang' AND TABLE_NAME = 'column_names_for_insertion' AND COLUMN_NAME = @column_name) THEN
				SET @add_column_statement = CONCAT( 'ALTER TABLE column_names_for_insertion ADD COLUMN ', @column_name, ' VARCHAR(255)' );
				PREPARE add_column_statement FROM	@add_column_statement;
				EXECUTE add_column_statement;
				
				SET @count_of_columns = @count_of_columns - 1;
			END IF;
		END WHILE;
	END IF;
END // 
DELIMITER ;
CALL create_table_for_storing_column_name();