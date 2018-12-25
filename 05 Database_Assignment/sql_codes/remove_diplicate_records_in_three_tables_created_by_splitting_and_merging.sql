/*
 *  this query is created for remove duplicate records caused by splitting and merging tables
 */
USE kaifang;
SET @database_name = 'kaifang';
SET @table_name = 'users_not_owning_chinese_identity_card';
SET @column_name = 'id_cdsgus';

SET @column_names_for_creating_index = 'id_cdsgus,id_cdsgus,id_cdsgus';
SET @table_names_for_creating_index = 'users_owning_chinese_identity_card,users_not_owning_chinese_identity_card,users_owning_old_chinese_identity_card';
SET @database_names_for_creating_index = 'kaifang,kaifang,kaifang';

SET @upper_bound_of_id_cdsgus = 1000000;
SET @lower_bound_of_id_cdsgus = 2;

/*
 * firstly, create index for id_cdsgus in tables @table_names_for_creating_index
 */
CALL create_index_for_columns(@column_names_for_creating_index, @table_names_for_creating_index, @database_names_for_creating_index);

/*
 * and then, remove all duplicate records in three tables
 */
DROP PROCEDURE IF EXISTS remove_duplicate_records;
DELIMITER //
CREATE PROCEDURE remove_duplicate_records(IN column_name VARCHAR(255), IN table_name VARCHAR(255))
BEGIN
	DECLARE tmp VARCHAR(255);
	DECLARE flag SMALLINT DEFAULT FALSE;
	DECLARE for_stop INT DEFAULT 0;
	DECLARE condition_expression VARCHAR(1000);
	DECLARE result_cursor CURSOR FOR SELECT * FROM tmp_view;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET flag = TRUE;
	
	SET condition_expression = CONCAT(column_name, ' >= ', @lower_bound_of_id_cdsgus, ' AND ', column_name, ' <= ', @upper_bound_of_id_cdsgus);
	CALL create_tmp_view_with_single_column_for_cursor(column_name, table_name, condition_expression);
	
	OPEN result_cursor;
	WHILE !flag DO
		FETCH result_cursor INTO tmp;
		SET condition_expression = CONCAT(column_name ,' = ', tmp);
		SET @tmp_query_result = 0;
		SET @find_duplicate_sql = CONCAT('SELECT COUNT(', column_name, ') INTO @tmp_query_result FROM ', table_name, ' WHERE ', condition_expression);
		PREPARE find_duplicate_sql FROM @find_duplicate_sql;
		EXECUTE find_duplicate_sql;
		DEALLOCATE PREPARE find_duplicate_sql;
		
		IF @tmp_query_result > 1 THEN
			SET @find_min_id_for_saving = 0;
			SET @find_min_id_sql = CONCAT('SELECT MIN(id) INTO @find_min_id_for_saving FROM ',table_name, ' WHERE ', condition_expression);
			PREPARE find_min_id_sql FROM @find_min_id_sql;
			EXECUTE find_min_id_sql;
			DEALLOCATE PREPARE find_min_id_sql;
			
			SET condition_expression = CONCAT(condition_expression, ' AND id != ', @find_min_id_for_saving );		
			CALL self_defined_delete_query(table_name, condition_expression);
		END IF;
	END WHILE;
END //
DELIMITER ;

CALL remove_duplicate_records(@column_name, @table_name);
CALL remove_duplicate_records(@column_name, 'users_owning_chinese_identity_card');
CALL remove_duplicate_records(@column_name, 'users_owning_old_chinese_identity_card');