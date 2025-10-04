SHOW DATABASES;

-- Use desired database (at this time, my only database)
USE u301268454_AnthonyMeyer;

/*
-- Create Table
CREATE TABLE t2(
	name VARCHAR(30) CHECK (CHAR_LENGTH(name)>2),
    start_date DATE,
    end_date DATE CHECK (start_date IS NULL OR end_date IS NULL OR start_date<end_date)
);
*/

/*
-- Insert Content into t2 Table
 INSERT INTO t2(name, start_date, end_date) VALUES('Ione', '2003-12-15', '2014-11-09');
-- INSERT INTO t2(name, start_date, end_date) VALUES('Io', '2003-12-15', '2014-11-09'); -- Will fail because name len == 2
INSERT INTO t2(name, start_date, end_date) VALUES('Ione', null, '2014-11-09');
INSERT INTO t2(name, start_date, end_date) VALUES('Ione', '2015-12-15', '2014-11-09'); -- Will fail because start_data > end_date


-- Product table using auto increment
CREATE TABLE product (
    product_id INT AUTO_INCREMENT PRIMARY KEY,
    product_name VARCHAR(200),
    price INT 
);

-- Insert Desk Chair product
INSERT INTO product (product_name, price) VALUES ('Desk chair', 50);


-- Create Book table
CREATE TABLE Book(
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    PRIMARY KEY (id)
);

-- Show Tables and see structure of Book table
SHOW TABLES;
DESC Book;

-- Insert books into Book
INSERT INTO Book (id, name) VALUES (1, 'MariaDB Book');
INSERT INTO Book (id, name) VALUES (2, "SQLDB Book');


-- View entries of Book Table
SELECT * from Book;

-- Drop previous Book table (No need remove columns first)
DROP TABLE `Book`;

-- If needing to remove columns:
ALTER TABLE Book DROP `id`, DROP `name`;

-- Create a new Book Table
CREATE TABLE Book(
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    PRIMARY KEY (id)
);

-- Create Price table
CREATE TABLE Price(
    id INT NOT NULL AUTO_INCREMENT,
    price float NOT NULL,
    PRIMARY KEY (id)
);


-- Insert Books
INSERT INTO Book (id, name) VALUES
(1, 'MariaDB Book1'),
(2, 'MariaDB Book2'),
(3, 'MariaDB Book3'),
(4, 'MariaDB Book4'),
(5, 'MariaDB Book5');



INSERT INTO Price (id, price) VALUES
(1, 251),
(2, 252),
(3, 223),
(4, 194),
(5, 305);



-- View Price Table
SELECT * from Price;

-- Per Teachers notes, expecting to have a Price w/id 6, so adding now
-- Additional note: This was on line 131 in the tutorial
INSERT INTO Price (id, price) VALUES (6, 251)


-- Change price for id1 to 250
UPDATE Price SET price = 250 WHERE id =1;

-- Change Book for id1 to MariaDB Book1a
UPDATE Book SET name = 'MariaDB Book1a' WHERE id = 1;



-- Delete last record from the table
DELETE FROM Price WHERE id = 6;


-- Display all prices less than 250
SELECT * FROM Price WHERE price < 250;

-- Show prices less than 250 where the id > 3
SELECT * FROM Price WHERE id > 3 OR price < 250;

-- Show all names that end with 4
SELECT name FROM Book WHERE name LIKE '%4';

-- Show all prices that start with 2, and order from low to high
SELECT * FROM Price WHERE price LIKE '2%' ORDER BY price;



-- Join price column from Price table with name from Book Table
-- into a single table.
SELECT Book.name, Price.price FROM Book INNER JOIN Price ON Book.id = Price.id;
*/
