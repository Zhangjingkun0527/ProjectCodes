/*create index for columns exceprt for column named id, the index_name is the same as the column name*/

/*please define your database here, and please change the relative databse and table to yours in the program*/
/***************please note this:the table name is cdsgus, you should substitute the name************************/
USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'cdsgus';

/*  ***main procedure***  */
DROP PROCEDURE IF EXISTS create_index_for_columns_except_column_named_id;
DELIMITER //
CREATE PROCEDURE create_index_for_columns_except_column_named_id()
	BEGIN
		DECLARE flag INT DEFAULT FALSE;
		DECLARE tmp VARCHAR(255) DEFAULT '';
		/*get all column name of @table_name in databse @databse_name*/
		DECLARE result_cursor CURSOR FOR SELECT COLUMN_NAME FROM information_schema.COLUMNS WHERE TABLE_NAME = @table_name AND TABLE_SCHEMA = @database_name;
		/*declare a continue handler ,use finish while loop*/
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
		OPEN result_cursor;
		WHILE !flag DO
			FETCH result_cursor INTO tmp;
			
			IF !flag THEN
				SET @index_name = '';
				/*firstly, we need to judge whether the column has the index*/
				SET @index_judge = CONCAT('SELECT INDEX_NAME INTO @index_name FROM information_schema.STATISTICS WHERE TABLE_NAME = \'', @table_name, '\'', ' AND TABLE_SCHEMA = \'', @database_name, '\'', ' AND COLUMN_NAME = \'', tmp, '\' LIMIT 1');
				PREPARE index_judge_statement FROM @index_judge;
				EXECUTE index_judge_statement;
				DEALLOCATE PREPARE index_judge_statement;
				SET flag = FALSE;
				
				/*finally, if the column has not index, then we will create a index(not UNIQUE, it's name is the same as column name) for it*/
				IF ISNULL(@index_name) || LENGTH(TRIM(@index_name)) < 1 THEN
					SET @index_create = CONCAT('CREATE INDEX ', tmp, ' ON ', @table_name, '(', tmp,')');
					PREPARE index_create_statement FROM @index_create;
					EXECUTE index_create_statement;
					SET flag = FALSE;
				END IF;
			END IF;
		END WHILE;
		CLOSE result_cursor;
	END//
DELIMITER ;

CALL create_index_for_columns_except_column_named_id();