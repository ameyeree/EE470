SHOW DATABASES;

-- Use desired database (at this time, my only database)
USE u301268454_AnthonyMeyer;

-- Create Two Tables sensor_data and sensor_register
-- sensor_register Table
/*
node_name: Up to 10 Characters (KEY)
manufacturer: Up to 10 characters
longitude: a REAL positive/negative number with max of 15 positions
latitude: a real (positive/negative) number wiht max of 15 positions
NOTE: Since this is the sensor register, this is where the PRIMARY KEY is
Additional NOTE: Basing Long and Lat off of site given, assumption is only 6 decimal places max,
Therefore the requirements of 15 "positions" is just wasted space, but will still increment this way.
*/
/*
CREATE TABLE sensor_register (
	node_name VARCHAR(10) NOT NULL,
    manufacturer VARCHAR(10) NOT NULL,
    longitude DECIMAL(15,6) NOT NULL CHECK (longitude BETWEEN -180 AND 180),
    latitude DECIMAL(15,6) NOT NULL CHECK (latitude BETWEEN -90 AND 90),
    PRIMARY KEY (node_name)
);*/
-- sensor_data Table
/*
node_name: Up to 10 Characters (KEY)
time_received: Date and Time
temperature: numeric value between -10 to +100 C maximum of 6 positions
humiditiy: a number value between 0-100 with maximum of 6 positions
-- Assumption: positions is number of digits. 
*/
/*
CREATE TABLE sensor_data (
	node_name VARCHAR(10) NOT NULL,
    time_received DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    temperature DECIMAL(6,3) NOT NULL CHECK (temperature BETWEEN -10 AND 100),
    humidity DECIMAL(6,3) NOT NULL CHECK (humidity BETWEEN 0 AND 100),
    FOREIGN KEY (node_name) REFERENCES sensor_register(node_name)
);
*/

-- Now populate some data
/*
1) Starting data DATATIME: '2022-10-1 11:00:00'
2) Data sent every half hour (4 data sets -> 11:00:00, 11:30:00, 12:00:00, 12:30:00)
3) Register 5 different sensors, with 5 different manufacturer names
4) Each sensor will transmit 4 different data sets (4 different entriers/sensor)
5) Node name format: node_n (node_1, node_2, node_3, node_4, node_5)
6) No data from sensor_data is accepted if the transmitting node is not reigstered (handled with primary key)
7) Create VIEW of both Tables and call it sensor_combined
*/

/*
-- First need to populate the 5 different sensors into sensor_register
INSERT INTO sensor_register (node_name, manufacturer, longitude, latitude) VALUES
('node_1', 'TI', 130.125468, 80.245682),
('node_2', 'Honeywell', -130.125468, -80.245682),
('node_3', 'Adafruit', 65.125468, -32.245682),
('node_4', 'Elegoo', -25.125468, 26.245682),
('node_5', 'DFRobot', 180.000000, 90.000000);
*/
