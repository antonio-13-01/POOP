DECLARE @wagon_id INT;
DECLARE @capacity INT;
DECLARE @wagon_type VARCHAR(20);
DECLARE @seat_counter INT;
DECLARE @seat_fare NUMERIC(8,2);

-- Cursor pentru a parcurge fiecare vagon
DECLARE wagon_cursor CURSOR FOR 
SELECT wagon_id, capacity, wagon_type FROM Wagon;

OPEN wagon_cursor;
FETCH NEXT FROM wagon_cursor INTO @wagon_id, @capacity, @wagon_type;

WHILE @@FETCH_STATUS = 0
BEGIN
    SET @seat_counter = 1;

    -- Stabilim suplimentul de preț (seat_fare) în funcție de tipul vagonului
    SET @seat_fare = 
        CASE @wagon_type
            WHEN 'Clasa I' THEN 25.00
            WHEN 'Cuseta' THEN 50.00
            ELSE 10.00
        END;

    -- Inserăm scaunele pentru vagonul curent
    WHILE @seat_counter <= @capacity
    BEGIN
        INSERT INTO Seat (seat_number, seat_fare, wagon_id)
        VALUES (@seat_counter, @seat_fare, @wagon_id);
        
        SET @seat_counter = @seat_counter + 1;
    END

    FETCH NEXT FROM wagon_cursor INTO @wagon_id, @capacity, @wagon_type;
END

CLOSE wagon_cursor;
DEALLOCATE wagon_cursor;


SELECT seat_id, seat_number, seat_fare, wagon_id
FROM Seat
