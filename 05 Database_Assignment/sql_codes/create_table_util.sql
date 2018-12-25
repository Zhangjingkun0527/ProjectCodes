SET @database_name = 'kaifang';
SET @param_num = 30;

DROP PROCEDURE IF EXISTS create_table_for_storing_column_name;
DELIMITER //
CREATE PROCEDURE create_table_for_storing_column_name() 
BEGIN
	DECLARE count_of_columns INT DEFAULT 32;
	/*create validate table for verifying ids*/
	IF NOT EXISTS (SELECT TABLE_NAME FROM information_schema.`TABLES` WHERE TABLE_NAME = 'column_names_for_insertion' AND TABLE_SCHEMA = @database_name) THEN
		CREATE TABLE column_names_for_insertion (type VARCHAR (100) NOT NULL, CONSTRAINT PRIMARY KEY (type));
		/*we think that it's enough for adding 18 columns to the validate_params*/
		WHILE	count_of_columns >= 0 DO
			SET @indexer = 33 - count_of_columns;
			SET @column_name = CONCAT('column_name_', @indexer);
			IF NOT EXISTS (SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_SCHEMA = 'kaifang' AND TABLE_NAME = 'column_names_for_insertion' AND COLUMN_NAME = @column_name) THEN
				SET @add_column_statement = CONCAT( 'ALTER TABLE column_names_for_insertion ADD COLUMN ', @column_name, ' VARCHAR(255)' );
				PREPARE add_column_statement FROM	@add_column_statement;
				EXECUTE add_column_statement;
				
				SET count_of_columns = count_of_columns - 1;
			END IF;
		END WHILE;
	END IF;
END // 
DELIMITER ;
/*
CALL create_table_for_storing_column_name();



/*
 * this procedure is defined to create param table for verifying id
 */
DROP PROCEDURE IF EXISTS create_param_table;
DELIMITER //
CREATE PROCEDURE create_param_table() 
BEGIN
	DECLARE count_of_columns INT DEFAULT (@param_num - 10);
	/*create validate table for verifying ids*/
	IF NOT EXISTS (SELECT TABLE_NAME FROM information_schema.`TABLES` WHERE TABLE_NAME = 'validate_params' AND TABLE_SCHEMA = @database_name ) THEN
		CREATE TABLE validate_params (type VARCHAR (100) NOT NULL, CONSTRAINT PRIMARY KEY (type));
		/*we think that it's enough for adding 18 columns to the validate_params*/
		WHILE	count_of_columns >= 0 DO
			SET @indexer = @param_num - count_of_columns;
			SET @column_name = CONCAT('param_', @indexer);
			IF NOT EXISTS (SELECT COLUMN_NAME FROM information_schema.`COLUMNS` WHERE TABLE_SCHEMA = @database_name AND TABLE_NAME = 'validate_params' AND COLUMN_NAME = @column_name) THEN
				SET @add_column_statement = CONCAT('ALTER TABLE validate_params ADD COLUMN ', @column_name, ' VARCHAR(10)');
				PREPARE add_column_statement FROM	@add_column_statement;
				EXECUTE add_column_statement;
				
				SET count_of_columns = count_of_columns - 1;
			END IF;
		END WHILE;
	END IF;
END // 
DELIMITER ;
CALL create_param_table();