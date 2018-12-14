/*
 * this file is created for utility functions
 */
SET GLOBAL log_bin_trust_function_creators = TRUE;

/*
 *  this function is defined to remove all illegal character defined by mysql in a string
 */
DROP FUNCTION IF EXISTS drop_illegal_character;
DELIMITER //
CREATE FUNCTION drop_illegal_character(str VARCHAR(500))
RETURNS VARCHAR(500)
BEGIN
	DECLARE str_cleared VARCHAR(500);
	SET str_cleared = REPLACE(str, '\'', '');
	SET str_cleared = REPLACE(str_cleared, '"', '');
	SET str_cleared = REPLACE(str_cleared, '\\', '');
	SET str_cleared = REPLACE(str_cleared, ' ', '');
	RETURN str_cleared;
END //
DELIMITER ;