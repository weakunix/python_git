CREATE TABLE todos (
	todoID VARCHAR(10) NOT NULL,
    className NVARCHAR(10) NOT NULL,
    dueDate DATE NOT NULL,
    isRepeat BOOL,
    progress INT,
    difficulty INT,
    todoComment NVARCHAR(500),  #what person puts in desc 
    PRIMARY KEY (todoID)
);

CREATE TABLE class (
	classID VARCHAR(10) NOT NULL,
    isStaticTime BOOL,
    timeOfClassStart TIME,
    timeOfClassEnd TIME, 
    classBlock NVARCHAR(5), #block
    classroomNumber NVARCHAR(5), #classroom number
    teacher NVARCHAR(10), #teacher
    className NVARCHAR(10), #name
    classComment NVARCHAR(500),  #what person puts in desc   
    PRIMARY KEY (classID)
);


CREATE TABLE mapping (
	 ID VARCHAR(10) NOT NULL,
     todo VARCHAR(10) NOT NULL,
     class VARCHAR(10) NOT NULL,
     PRIMARY KEY (ID),
     FOREIGN KEY (todo) REFERENCES todo (todoID) ON DELETE CASCADE,
     FOREIGN KEY (class) REFERENCES class (classID) ON DELETE CASCADE
);


CREATE TABLE userinfo (
	username NVARCHAR(20) NOT NULL,
    pass BINARY(64) NOT NULL,
    #UID VARCHAR(10) NOT NULL,
    PRIMARY KEY (username),
    todo VARCHAR(10) NOT NULL,
    class VARCHAR(10) NOT NULL,
    #FOREIGN KEY (UID) REFERENCES mapping (ID) ON DELETE CASCADE
    FOREIGN KEY (todo) REFERENCES todo (todoID) ON DELETE CASCADE,
    FOREIGN KEY (class) REFERENCES class (classID) ON DELETE CASCADE
);

DROP TABLE class;
DROP TABLE todos;
DROP TABLE mapping;
DROP TABLE userinfo;