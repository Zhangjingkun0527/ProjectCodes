/* this procedure is defined to get the count of not null value of any column in any table*/

USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'cdsgus';

DROP PROCEDURE IF EXISTS count_not_null_records_of_each_column;
DELIMITER //
CREATE PROCEDURE count_not_null_records_of_each_column()
  BEGIN
    DECLARE flag INT DEFAULT FALSE;
    DECLARE tmp VARCHAR(255) DEFAULT '';
    /*get all column name of @table_name in database @database_name*/
    DECLARE result_cursor CURSOR FOR SELECT COLUMN_NAME
                                   FROM INFORMATION_SCHEMA.COLUMNS
                                   WHERE TABLE_NAME = @table_name AND TABLE_SCHEMA = @database_name;
    /*declare a continue handler ,use finish while loop*/
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
    OPEN result_cursor;
    SET @count_statement = 'SELECT ';
    WHILE !flag DO
      FETCH result_cursor INTO tmp;
      IF !flag THEN
      /*create and concat count statement*/
        SET @count_statement = CONCAT(@count_statement, 'SUM(CASE WHEN ', tmp, ' IS NOT NULL AND LENGTH(TRIM(', tmp, ')) > 0 THEN 1 ELSE 0 END) AS ', tmp, ',');
      END IF;
    END WHILE;
    /*remove the last comma*/  
		SET @count_statement = LEFT(@count_statement, LENGTH(@count_statement) - 1);
    SET @count_statement = CONCAT(@count_statement, ' FROM ', @table_name);
    /*execute the sql statement*/
    PREPARE count_statement FROM @count_statement;
    EXECUTE count_statement;
  END //
DELIMITER ;

CALL count_not_null_records_of_each_column();