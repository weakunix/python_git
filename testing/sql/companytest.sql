use hw;

CREATE TABLE kid (
	name VARCHAR(20) PRIMARY KEY,
    birth DATE,
    sex VARCHAR(1),
    blood VARCHAR(2),
    dad VARCHAR(20), 
    mom VARCHAR(20),
    FOREIGN KEY(dad) REFERENCES kid(name) ON DELETE SET NULL,
    FOREIGN KEY(mom) REFERENCES kid(name) ON DELETE SET NULL
);

#make dad
INSERT INTO kid #holy shit does this sound bad "insert into kid"
VALUES(
	"dad", 
	"1990-04-23", 
    "M",
    "O ",
    Null,
    Null
);

#make mom
INSERT INTO kid 
VALUES(
	"mom", 
	"1994-01-23", 
    "F",
    "B+",
    Null,
    Null
);

#make brother
INSERT INTO kid 
VALUES(
	"brother", 
	"2006-01-23", 
    "M",
    "B+",
    "dad",
    "mom"
);

#make sister
INSERT INTO kid 
VALUES(
	"sister", 
	"2007-01-15", 
    "F",
    "A+",
    "dad",
    "mom"
);

SELECT * from kid;

DROP TABLE kid;

#other stuff here
SELECT kid.dad AS parent, kid.mom AS parent from kid WHERE name = "brother" OR name = "sister"; 

#count how many ppl have parents
SELECT COUNT(dad) from kid;

#print the kid that is a girl that is born after 2005
SELECT *
FROM kid
WHERE sex = "F" AND birth > '2005-01-01'

#AVG(), SUM... unused as there is no data of numbers
