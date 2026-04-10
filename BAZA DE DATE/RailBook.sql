CREATE DATABASE RailBook;
USE RailBook;

-- ==================STATION===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Station' AND xtype='U')
CREATE TABLE Station (
    station_id      INT     IDENTITY(1,1) NOT NULL,
    station_name    VARCHAR(100) NOT NULL
)
 
ALTER TABLE Station
ADD CONSTRAINT PK_Station PRIMARY KEY (station_id)

ALTER TABLE Station
DROP COLUMN station_name;

ALTER TABLE Station
ADD station_city VARCHAR(100) NOT NULL;

ALTER TABLE Station
ADD station_county VARCHAR(100) NOT NULL;

ALTER TABLE Station
ADD station_name VARCHAR(100) NOT NULL;

-- ==================ROUTE===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Route' AND xtype='U')
CREATE TABLE Route (
    route_id        INT     IDENTITY(1,1) NOT NULL,
    route_name      VARCHAR(200) NOT NULL
)
 
ALTER TABLE Route
ADD CONSTRAINT PK_Route PRIMARY KEY (route_id)

-- ==================STOP_INFO===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='StopInfo' AND xtype='U')
CREATE TABLE StopInfo (
    stop_info_id        INT     IDENTITY(1,1)       NOT NULL,
    route_id            INT     NOT NULL,
    station_id          INT     NOT NULL,
    km_from_origin      INT     NOT NULL,
    arrival_minutes     INT     NOT NULL,
    departure_minutes   INT     NOT NULL
)
 
ALTER TABLE StopInfo
ADD CONSTRAINT PK_StopInfo PRIMARY KEY (stop_info_id)
 
ALTER TABLE StopInfo
ADD CONSTRAINT FK_StopInfoRoute FOREIGN KEY (route_id) REFERENCES Route(route_id)
 
ALTER TABLE StopInfo
ADD CONSTRAINT FK_StopInfoStation FOREIGN KEY (station_id) REFERENCES Station(station_id)

-- ==================TRAIN===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Train' AND xtype='U')
CREATE TABLE Train (
    train_id        INT     IDENTITY(1,1)       NOT NULL,
    train_number    VARCHAR(20)     NOT NULL,
    train_type      VARCHAR(20)     NOT NULL,         -- Regio, InterCity, InterRegio
    train_status    VARCHAR(20)     NOT NULL    DEFAULT 'Activ',  -- Activ, Anulat
    number_of_wagons    INT     NOT NULL    DEFAULT 0,
    fare        NUMERIC(8,2)    NOT NULL    DEFAULT 0,
    route_id        INT         NOT NULL
)
 
ALTER TABLE Train
ADD CONSTRAINT PK_Train PRIMARY KEY (train_id)
 
ALTER TABLE Train
ADD CONSTRAINT FK_TrainRoute FOREIGN KEY (route_id) REFERENCES Route(route_id)

-- ==================WAGON===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Wagon' AND xtype='U')
CREATE TABLE Wagon (
    wagon_id            INT     IDENTITY(1,1)       NOT NULL,
    wagon_number        INT     NOT NULL,
    capacity            INT     NOT NULL,
    wagon_type          VARCHAR(20)         NOT NULL,           -- 'ClasaI, Clasa aII-a, Cuseta cu 4 paturi
    train_id            INT     NOT NULL
)
 
ALTER TABLE Wagon
ADD CONSTRAINT PK_Wagon PRIMARY KEY (wagon_id)
 
ALTER TABLE Wagon
ADD CONSTRAINT FK_WagonTrain FOREIGN KEY (train_id) REFERENCES Train(train_id)

-- ==================SEAT===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Seat' AND xtype='U')
CREATE TABLE Seat (
    seat_id         INT          IDENTITY(1,1)      NOT NULL,
    seat_number     INT          NOT NULL,
    seat_fare       NUMERIC(8,2) NOT NULL           DEFAULT 0,
    wagon_id        INT          NOT NULL
)
 
ALTER TABLE Seat
ADD CONSTRAINT PK_Seat PRIMARY KEY (seat_id)
 
ALTER TABLE Seat
ADD CONSTRAINT FK_SeatWagon FOREIGN KEY (wagon_id) REFERENCES Wagon(wagon_id)

-- ==================DISCOUNT===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Discount' AND xtype='U')
CREATE TABLE Discount (
    discount_id         INT                 IDENTITY(1,1)      NOT NULL,
    discount_type        VARCHAR(20)         NOT NULL           DEFAULT  'Adult Standard', --Elev, Student, Senior
    discount_percent    DECIMAL(10,2)       NOT NULL
)
 
ALTER TABLE Discount
ADD CONSTRAINT PK_Discount PRIMARY KEY (discount_id)
 

-- ==================USER===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Users' AND xtype='U')
CREATE TABLE Users (
    users_id         INT             IDENTITY(1,1) NOT NULL,
    users_last_name    VARCHAR(100)    NOT NULL,
    users_first_name   VARCHAR(100)    NOT NULL,
    users_email        VARCHAR(255)    NOT NULL,
    users_password     VARCHAR(255)    NOT NULL,
    
    -- Rolul în sistem - administrator, operator, client
    users_role         VARCHAR(20)     NOT NULL DEFAULT 'Client',
   
    -- Client
    client_category   VARCHAR(20)     NULL, --adult standard, elev, student, pensionar
    client_credit     DECIMAL(10,2)   DEFAULT 0.00
);

ALTER TABLE Users
ADD CONSTRAINT PK_Users PRIMARY KEY (users_id);

ALTER TABLE Users
ADD CONSTRAINT UQ_UsersEmail UNIQUE (users_email);

ALTER TABLE Users
ADD valability_date   DATE      NOT NULL

ALTER TABLE Users
ALTER COLUMN valability_date DATE NULL;

ALTER TABLE Users
ADD discount_id       INT       NULL

ALTER TABLE Users
ADD CONSTRAINT FK_UsersDiscount FOREIGN KEY (discount_id) REFERENCES Discount(discount_id);

-- ==================TICKET===================

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Ticket' AND xtype='U')
CREATE TABLE Ticket (
    ticket_id               INT          IDENTITY(1,1)      NOT NULL,
    users_id               INT          NOT NULL,
    seat_id                 INT          NOT NULL,
    begin_stop_info_id      INT          NOT NULL,  -- statie imbarcare
    end_stop_info_id        INT          NOT NULL,  -- statie destinatie
    fare                    NUMERIC(8,2) NOT NULL,
    ticket_status           VARCHAR(20)  NOT NULL           DEFAULT 'Activ', -- Activ, Anulat, Finalizat
    journey_date            DATE         NOT NULL,
)
 
ALTER TABLE Ticket
ADD CONSTRAINT PK_Ticket PRIMARY KEY (ticket_id)
 
ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketUser FOREIGN KEY (users_id) REFERENCES Users(users_id)
 
ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketSeat FOREIGN KEY (seat_id) REFERENCES Seat(seat_id)
 
ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketBeginStopInfo FOREIGN KEY (begin_stop_info_id) REFERENCES StopInfo(stop_info_id)
 
ALTER TABLE Ticket
ADD CONSTRAINT FK_TicketEndStopInfo FOREIGN KEY (end_stop_info_id) REFERENCES StopInfo(stop_info_id)

 
