SHOW DATABASES;

-- Use appropriate Databasse
USE u301268454_AnthonyMeyer;

-- Create a table
CREATE TABLE Book(
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    PRIMARY KEY (id)
);

-- Insert First book into Table
INSERT INTO Book (id, name) VALUES
(1, 'MariaDB Book');

-- Insert Second book into Table
INSERT INTO Book (id, name) VALUES
(2, 'SQLDB Book');

-- Display all contents of Book Table
SELECT * from Book;
