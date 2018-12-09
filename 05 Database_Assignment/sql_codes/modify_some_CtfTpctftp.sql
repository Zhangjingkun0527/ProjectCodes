UPDATE cdsgus SET CtfTp = 'ID' WHERE CtfTp IS NULL OR LENGTH(TRIM(CtfTp)) < 1;
UPDATE cdsgus SET CtfTp = 'ID' WHERE CtfTp IN ('待定', '1', '11', 'TSZ', 'Id', '#ID', 'HKB');
UPDATE cdsgus SET CtfTp = 'GID' WHERE CtfTp = '#GID';
UPDATE cdsgus SET CtfTp = 'JZ' WHERE CtfTp = 'JZ1';
UPDATE cdsgus SET CtfTp = 'TBZ' WHERE CtfTp = 'hvz';