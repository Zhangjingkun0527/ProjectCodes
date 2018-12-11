/*
 * this file is created for utility functions
 */
SET GLOBAL log_bin_trust_function_creators = TRUE;
/*
 *this function is defined for remove elements which are not digit or letter x
 */
DROP FUNCTION IF EXISTS drop_non_digit_or_letter_x;
DELIMITER //
CREATE FUNCTION drop_non_digit_or_letter_x(str VARCHAR(255)) 
RETURNS VARCHAR(255) 
BEGIN
	/*get the string trimmed*/
	SET @tmp_str_trimmed = TRIM(str);
	SET @length_of_tmp = LENGTH(@tmp_str_trimmed);
	SET @indexer = 1;
	SET @result = '';
	
	/*remove the elements which are not digit or letter x */
	WHILE	@indexer <= @length_of_tmp DO
		SET @tmp = SUBSTRING(str, @indexer, 1);
		IF @tmp REGEXP '^[0-9Xx]' THEN
			SET @result = CONCAT(@result, @tmp);
		END IF;
		SET @indexer = @indexer + 1;
	END WHILE;

	RETURN @result;
END // 
DELIMITER ;