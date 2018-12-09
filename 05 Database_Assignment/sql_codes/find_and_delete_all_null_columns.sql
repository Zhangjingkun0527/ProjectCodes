/*get the number of columns in default table named course, and find the null columns to delete them.*/

/*please define your database here, and please change the relative databse and table to yours in the program*/
/***************please note this:the table name is cdsgus, you should substitute the name************************/
USE test;
SET @database_name = 'test';
SET @table_name = 'course';

/*Before defining a function, firstly we should judge if the function already exists, or there would be something wrong occured.*/
DROP PROCEDURE IF EXISTS find_and_delete_all_column_names;

/*  ***main procedure***  */
DELIMITER //
CREATE PROCEDURE find_and_delete_all_column_names()
	BEGIN
		DECLARE flag INT DEFAULT FALSE;
		DECLARE tmp VARCHAR(100) DEFAULT('');
		/*get all column names of table_name in databse databse_name*/
		DECLARE result_cursor CURSOR FOR SELECT COLUMN_NAME FROM information_schema.COLUMNS WHERE TABLE_NAME = @table_name AND TABLE_SCHEMA = @database_name;
		/*declare a continue handler ,use finish while loop*/
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
		/*open cursor to fetch all column name and delete those which are null*/
		OPEN result_cursor;
		WHILE !flag DO
			/*store a column name to tmp*/
			FETCH result_cursor INTO tmp;
			
			/*define @number fo storing result of count */
			SET @number = 0;
			IF !flag THEN
				/*use EXECUTE statement to execute a self-defined sql statement*/
				SET @sql_find_null_column = CONCAT('SELECT COUNT(`', tmp, '`) INTO @number FROM ', @table_name);
				PREPARE sql_statement FROM @sql_find_null_column; 
				EXECUTE sql_statement;
				DEALLOCATE PREPARE sql_statement;
				SET flag = FALSE;
				
				/*judge whethere the column is a null column, if yes, then delete it*/
				IF @number < 1 THEN
					SET @sql_statement = CONCAT('ALTER TABLE ', @table_name, ' DROP COLUMN ',tmp);
					PREPARE sql_statement FROM @sql_statement; 
					EXECUTE sql_statement;
					SET flag = FALSE;
				END IF;
			END IF;			
		END WHILE;
		CLOSE result_cursor;
		
	END //
DELIMITER ;

CALL find_and_delete_all_column_names();