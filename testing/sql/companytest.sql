CREATE TABLE kid (
	name VARCHAR(20) PRIMARY KEY,
    birth DATE,
    sex VARCHAR(1),
    blood VARCHAR(1),
    dad VARCHAR(20), 
    mom VARCHAR(20),
    FOREIGN KEY(dad) REFERENCES kid(name) ON DELETE SET NULL,
    FOREIGN KEY(mom) REFERENCES kid(name) ON DELETE SET NULL
);

