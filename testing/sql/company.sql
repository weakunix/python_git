CREATE TABLE mootbing (
	id INT PRIMARY KEY AUTO_INCREMENT,
	nam VARCHAR(30)
);

INSERT INTO mootbing
(
	nam
)VALUES(
	"bach LLC"
);

INSERT INTO mootbing
(
	nam
)VALUES(
	"bing ling LLC"
);

INSERT INTO mootbing
(
	nam
)VALUES(
	"tmoxic LLC INC"
);

DROP TABLE mootbing;

SELECT * FROM mootbing WHERE mootbing.nam LIKE "%LLC" OR mootbing.nam LIKE "%LLC%";