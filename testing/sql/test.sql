use hw; #use the same table

CREATE TABLE test ( #make new table
	id INT AUTO_INCREMENT, #makes unique id for each person automatically increments by 1 per new user
    name VARCHAR(15), # name of new user (up to 15 characters long) probs gonna get the info from the python 'register' option
    password VARCHAR(15) DEFAULT 'password', #password of the user, if none provided (probs wont happen), then use 'password'
    favfood VARCHAR(10) DEFAULT 'undecided', #favorite food (just for testing) default is 'undecided'
    PRIMARY KEY(id) #set this to primary key to access by
);

SELECT * FROM test; #displays all of TABLE test

INSERT INTO test #sql inject da deerug
(
    name,
    password
) VALUES(
    "admin", #name
    "password" #password
);

#test test test comment here github should recieve this

DROP TABLE test; #bye bye

UPDATE test
SET name = "NO ADMIN FOR YOU" #sneaky pesty kids trying to steal my administrator privleges
WHERE name = "admin" OR name = "ADMIN"; 

DELETE FROM test
WHERE name = "admin" OR name = "ADMIN"; #delete the entries with name as ADMIN to not conflict with my administrator account

SELECT name, test.favfood FROM test; #get certain things from a table you can use test. to make it clearer

SELECT * FROM test ORDER BY test.favfood, id ASC; #order by ascending order A-Z of favfood first, if two has the same then it orders by their id.

SELECT name, password FROM test; #select items from test

SELECT name, password FROM test LIMIT 2; #select items from test

SELECT * FROM test WHERE password in ("password"); #select items from test