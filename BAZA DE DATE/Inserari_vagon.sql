DECLARE @train_id INT;
DECLARE @total_wagons INT;
DECLARE @train_type VARCHAR(20);
DECLARE @counter INT;
DECLARE @wagon_type VARCHAR(20);
DECLARE @capacity INT;

-- Selectăm și tipul trenului în cursor
DECLARE train_cursor CURSOR FOR 
SELECT train_id, number_of_wagons, train_type FROM Train;

OPEN train_cursor;
FETCH NEXT FROM train_cursor INTO @train_id, @total_wagons, @train_type;

WHILE @@FETCH_STATUS = 0
BEGIN
    SET @counter = 1;

    WHILE @counter <= @total_wagons
    BEGIN
        -- LOGICĂ PERSONALIZATĂ
        -- Verificăm dacă trenul este InterCity
        IF @train_type = 'InterCity'
        BEGIN
            -- Primul vagon este mereu Cușetă la InterCity
            IF @counter = 1 
                SELECT @wagon_type = 'Cuseta', @capacity = 20;
            -- Al doilea vagon este Clasa I
            ELSE IF @counter = 2 
                SELECT @wagon_type = 'Clasa I', @capacity = 40;
            -- Restul sunt Clasa a II-a
            ELSE 
                SELECT @wagon_type = 'Clasa a II-a', @capacity = 60;
        END
        -- Pentru restul trenurilor (InterRegio/Regio)
        ELSE
        BEGIN
            IF @counter = 1 
                SELECT @wagon_type = 'Clasa I', @capacity = 40;
            ELSE 
                SELECT @wagon_type = 'Clasa a II-a', @capacity = 60;
        END

        -- Inserarea în tabel
        INSERT INTO Wagon (wagon_number, capacity, wagon_type, train_id)
        VALUES (@counter, @capacity, @wagon_type, @train_id);

        SET @counter = @counter + 1;
    END

    FETCH NEXT FROM train_cursor INTO @train_id, @total_wagons, @train_type;
END

CLOSE train_cursor;
DEALLOCATE train_cursor;

SELECT wagon_id, wagon_number,wagon_type,train_id
FROM Wagon