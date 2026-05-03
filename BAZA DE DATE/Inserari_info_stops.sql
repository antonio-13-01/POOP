-- Ruta IR Bucuresti Nord - Brasov TUR
-- Bucuresti Nord - Ploiesti Vest - Sinaia - Predeal - Brasov
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(1, 1, 0, 0, 0),    
(1, 97, 59, 37, 39),  
(1, 99, 121, 85, 87), 
(1, 36, 140, 108, 110),
(1, 33, 166, 145, 145);

-- Ruta IR Bucuresti Nord - Brasov RETUR
-- Brasov - Predeal - Sinaia - Ploiesti Vest - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(2, 33, 0, 0, 0),     
(2, 36, 26, 32, 34),  
(2, 97, 107, 105, 107),
(2, 1, 166, 145, 145); 

-- Ruta R Bucuresti Nord - Brasov TUR
-- Bucuresti Nord - Buftea - Ploiesti Vest -Campina - Sinaia - Busteni - Azuga - Predeal - Brasov
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(3, 1, 0, 0, 0),       -- Bucuresti Nord
(3, 81, 17, 15, 16),   -- Buftea
(3, 97, 59, 45, 47),   -- Ploiesti Vest
(3, 98, 92, 70, 72),   -- Campina
(3, 99, 121, 95, 97),  -- Sinaia
(3, 100, 127, 105, 106),-- Busteni
(3, 101, 131, 112, 113),-- Azuga
(3, 36, 140, 125, 127),-- Predeal
(3, 33, 166, 165, 165);-- Brasov

-- Ruta R Bucuresti Nord - Brasov RETUR
-- Brasov - Predeal - Azuga - Busteni - Sinaia - Campina - Ploiesti Vest - Buftea - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(4, 33, 0, 0, 0),       
(4, 36, 26, 35, 37),   
(4, 101, 35, 48, 49),  
(4, 100, 39, 56, 57), 
(4, 99, 45, 65, 67),   
(4, 98, 74, 90, 92),   
(4, 97, 107, 115, 117),
(4, 81, 149, 148, 149),
(4, 1, 166, 165, 165); 

-- Ruta IR Bucuresti Nord - Constanta TUR
-- Bucuresti Nord - Fetesti - Constanta
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(5, 1, 0, 0, 0),       
(5, 76, 146, 85, 87),  
(5, 47, 225, 130, 130);

-- Ruta IR Bucuresti Nord - Constanta RETUR 
-- Constanta - Fetesti - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(6, 47, 0, 0, 0),       
(6, 76, 79, 43, 45),    
(6, 1, 225, 130, 130);  

-- Ruta R Bucuresti Nord - Constanta TUR
-- Bucuresti Nord - Lehliu - Fetesti - Cernavoda Pod - Medgidia - Constanta
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(7, 1, 0, 0, 0),       
(7, 42, 70, 50, 52),   
(7, 76, 146, 105, 107),
(7, 50, 162, 120, 122),
(7, 49, 191, 145, 147),
(7, 47, 225, 175, 175);

-- Ruta R Bucuresti Nord - Constanta RETUR 
-- Constanta - Medgidia - Cernavoda Pod - Fetesti - Lehliu - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(8, 47, 0, 0, 0),      
(8, 49, 34, 30, 32),    
(8, 50, 63, 55, 57),    
(8, 76, 79, 70, 72),    
(8, 42, 155, 123, 125), 
(8, 1, 225, 175, 175);  

-- Ruta IR București Nord - Craiova TUR
-- Bucuresti Nord - Rosiori Nord - Craiova 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(9, 1, 0, 0, 0),        
(9, 113, 100, 75, 77),  
(9, 58, 209, 150, 150); 

-- Ruta IR București Nord - Craiova RETUR
-- Craiova - Rosiori Nord - Bucuresti Nord  
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(10, 58, 0, 0, 0),       
(10, 113, 109, 73, 75),  
(10, 1, 209, 150, 150);  

-- Ruta R București Nord - Craiova TUR
-- Bucuresti Nord - Videle - Rosiori Nord - Caracal - Craiova 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(11, 1, 0, 0, 0),        
(11, 115, 51, 45, 47),   
(11, 113, 100, 90, 92),  
(11, 94, 154, 135, 137), 
(11, 58, 209, 190, 190); 

-- Ruta R București Nord - Craiova RETUR
-- Craiova - Caracal - Rosiori Nord - Videle - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(12, 58, 0, 0, 0),       
(12, 94, 55, 50, 52),    
(12, 113, 109, 95, 97),  
(12, 115, 158, 140, 142),
(12, 1, 209, 190, 190);  

-- IR București Nord - Iasi TUR
-- Bucuresti Nord - Ploiesti Sud - Buzau - Focsani - Bacau - Pascani - Iasi
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(13, 1, 0, 0, 0),        
(13, 96, 59, 45, 47),    
(13, 39, 128, 100, 105), 
(13, 125, 199, 160, 162),
(13, 20, 302, 240, 245), 
(13, 79, 387, 310, 315), 
(13, 78, 463, 370, 370); 

-- IR București Nord - Iasi RETUR
-- Iasi - Pascani - Bacau - Focsani -Buzau - Ploiesti Sud - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(14, 78, 0, 0, 0),       
(14, 79, 76, 55, 60),    
(14, 20, 161, 125, 130), 
(14, 125, 264, 205, 207),
(14, 39, 335, 260, 265), 
(14, 96, 404, 318, 320),
(14, 1, 463, 370, 370);  

-- R București Nord - Iasi TUR
-- Bucuresti Nord - Ploiesti Sud - Buzau - Ramnicu Sarat - Focsani - Marasesti - Adjud - Bacau - Roman - Pascani - Iasi
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(15, 1, 0, 0, 0),        
(15, 96, 59, 55, 57),    
(15, 39, 128, 120, 125), 
(15, 40, 161, 155, 157), 
(15, 125, 199, 195, 197),
(15, 126, 218, 215, 217),
(15, 7, 244, 240, 242),  
(15, 20, 302, 290, 295), 
(15, 91, 346, 335, 337), 
(15, 79, 387, 375, 380), 
(15, 78, 463, 440, 440); 

-- R București Nord - Iasi RETUR
-- Iasi - Pascani - Roman - Bacau - Adjud - Marasesti - Focsani -Ramnicu Sarat -Buzau - Ploiesti Sud - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(16, 78, 0, 0, 0),       -- Iasi
(16, 79, 76, 60, 65),    -- Pascani
(16, 91, 117, 100, 102), -- Roman
(16, 20, 161, 145, 150), -- Bacau
(16, 7, 219, 195, 197),  -- Adjud
(16, 126, 245, 220, 222),-- Marasesti
(16, 125, 264, 240, 242),-- Focsani
(16, 40, 302, 280, 282), -- Ramnicu Sarat
(16, 39, 335, 315, 320), -- Buzau
(16, 96, 404, 380, 382), -- Ploiesti Sud
(16, 1, 463, 440, 440);  -- Bucuresti Nord

-- IR București Nord - Galati TUR 
-- Bucuresti Nord - Ploiesti Sud - Buzau - Braila - Galati
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(17, 1, 0, 0, 0),        
(17, 96, 59, 45, 47),    
(17, 39, 128, 100, 105), 
(17, 37, 229, 185, 187), 
(17, 62, 260, 220, 220); 

-- IR București Nord - Galati RETUR 
-- Galati - Braila - Buzau - Ploiesti Sud - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(18, 62, 0, 0, 0),       
(18, 37, 31, 33, 35),    
(18, 39, 132, 115, 120), 
(18, 96, 201, 173, 175), 
(18, 1, 260, 220, 220);  

-- R București Nord - Galati TUR 
-- Bucuresti Nord - Ploiesti Sud - Buzau - Faurei - Braila - Barbosi - Galati
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(19, 1, 0, 0, 0),        
(19, 96, 59, 55, 57),    
(19, 39, 128, 120, 125), 
(19, 38, 168, 160, 162), 
(19, 37, 229, 210, 212), 
(19, 63, 248, 235, 237), 
(19, 62, 260, 255, 255); 

-- R București Nord - Galati RETUR 
-- Galati - Barbosi - Braila - Faurei - Buzau - Ploiesti Sud - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(20, 62, 0, 0, 0),       
(20, 63, 12, 15, 17),    
(20, 37, 31, 40, 42),    
(20, 38, 92, 90, 92),    
(20, 39, 132, 130, 135), 
(20, 96, 201, 198, 200), 
(20, 1, 260, 255, 255);  

-- IR București Nord - Timisoara Nord TUR
-- Bucuresti Nord - Videle - Craiova - Drobeta Turnu Severin - Lugoj - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(21, 1, 0, 0, 0),        
(21, 115, 51, 45, 47),   
(21, 58, 209, 155, 160), 
(21, 85, 323, 260, 265), 
(21, 118, 473, 410, 412),
(21, 116, 533, 470, 470);

-- IR București Nord - Timisoara Nord RETUR
-- Timisoara Nord - Lugoj - Drobeta Turnu Severin - Craiova - Videle - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(22, 116, 0, 0, 0),       
(22, 118, 60, 55, 57),    
(22, 85, 210, 205, 210),  
(22, 58, 324, 310, 315),  
(22, 115, 482, 423, 425), 
(22, 1, 533, 470, 470);   

-- R București Nord - Timisoara Nord TUR
-- Bucuresti Nord - Videle - Rosiori Nord - Caracal- Craiova  - Filiasi - Drobeta Turnu Severin - Orsova - Lugoj - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(23, 1, 0, 0, 0),        
(23, 115, 51, 55, 57),   
(23, 113, 100, 105, 107),
(23, 94, 154, 150, 152), 
(23, 58, 209, 200, 205), 
(23, 59, 245, 240, 242), 
(23, 85, 323, 315, 320), 
(23, 86, 348, 345, 347), 
(23, 118, 473, 510, 512),
(23, 116, 533, 570, 570);

-- R București Nord - Timișoara Nord RETUR
-- Timisoara Nord - Lugoj - Orsova - Drobeta Turnu Severin - Filiasi - Craiova - Caracal - Rosiori Nord - Videle - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(24, 116, 0, 0, 0),   
(24, 118, 60, 60, 62),   
(24, 86, 185, 220, 222),  
(24, 85, 210, 250, 255),  
(24, 59, 288, 325, 327),  
(24, 58, 324, 365, 370),  
(24, 94, 379, 418, 420),  
(24, 113, 433, 463, 465), 
(24, 115, 482, 513, 515),
(24, 1, 533, 570, 570);  

-- IR București Nord - Cluj-Napoca TUR 
-- Bucuresti Nord - Ploiesti Vest - Brasov - Sighisoara - Teius - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(25, 1, 0, 0, 0),        
(25, 97, 59, 45, 47),    
(25, 33, 166, 160, 170), 
(25, 88, 294, 280, 282), 
(25, 11, 396, 380, 385), 
(25, 43, 497, 490, 490); 

-- IR București Nord - Cluj-Napoca RETUR 
-- Cluj-Napoca - Teius - Sighisoara - Brasov - Ploesti Vest - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(26, 43, 0, 0, 0),       
(26, 11, 101, 105, 110), 
(26, 88, 203, 208, 210), 
(26, 33, 331, 320, 330), 
(26, 97, 438, 443, 445), 
(26, 1, 497, 490, 490);  

-- R București Nord - Cluj-Napoca TUR 
-- Bucuresti Nord - Buftea - Ploiesti Vest -Sinaia - Predeal - Brasov - Sighisoara - Medias - Blaj - Teius - Aiud - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(27, 1, 0, 0, 0),       
(27, 81, 17, 15, 16),    
(27, 97, 59, 55, 57),    
(27, 99, 121, 110, 112), 
(27, 36, 140, 135, 137), 
(27, 33, 166, 170, 180), 
(27, 88, 294, 305, 310), 
(27, 107, 332, 350, 352),
(27, 10, 381, 400, 402), 
(27, 11, 396, 420, 425),
(27, 9, 411, 445, 447), 
(27, 43, 497, 560, 560); 

-- R București Nord - Cluj-Napoca RETUR 
-- Cluj-Napoca - Aiud - Teius - Blaj - Medias  - Sighisoara - Brasov - Predeal -Sinaia - Ploesti Vest - Buftea - Bucuresti Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(28, 43, 0, 0, 0),       
(28, 9, 86, 115, 117),   
(28, 11, 101, 135, 140), 
(28, 10, 116, 158, 160), 
(28, 107, 165, 208, 210),
(28, 88, 203, 250, 255), 
(28, 33, 331, 380, 390), 
(28, 36, 357, 423, 425), 
(28, 99, 376, 448, 450), 
(28, 97, 438, 503, 505), 
(28, 81, 480, 544, 545), 
(28, 1, 497, 560, 560);  

-- IR Bucuresti Nord - Pitesti TUR
-- Bucuresti Nord - Titu - Pitesti
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(29, 1, 0, 0, 0),        
(29, 56, 49, 42, 44),    
(29, 16, 108, 95, 95);   

-- IR Bucuresti Nord - Pitesti RETUR
-- Pitesti - Titu - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(30, 16, 0, 0, 0),       
(30, 56, 59, 51, 53),    
(30, 1, 108, 95, 95);    

-- R Bucuresti Nord - Pitesti TUR
-- Bucuresti Nord - Titu - Gaesti - Costesti - Pitesti
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(31, 1, 0, 0, 0),        
(31, 56, 49, 50, 52),    
(31, 57, 71, 75, 77),    
(31, 19, 93, 100, 102), 
(31, 16, 108, 120, 120); 

-- IR Bucuresti Nord - Pitesti RETUR
-- Pitesti - Costesti - Gaesti - Titu - Bucuresti Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(32, 16, 0, 0, 0),       
(32, 19, 15, 18, 20),    
(32, 57, 37, 43, 45),    
(32, 56, 59, 68, 70),    
(32, 1, 108, 120, 120);  

-- IR Cluj-Napoca - Timisoara Nord TUR
-- Cluj-Napoca - Oradea - Arad - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(33, 43, 0, 0, 0),        
(33, 24, 152, 150, 160), 
(33, 13, 273, 270, 275), 
(33, 116, 330, 330, 330);

-- IR Cluj-Napoca - Timisoara Nord RETUR 
-- Timisoara Nord - Arad - Oradea - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(34, 116, 0, 0, 0),       
(34, 13, 57, 55, 60),     
(34, 24, 178, 170, 180), 
(34, 43, 330, 330, 330);

-- R Cluj-Napoca - Timisoara Nord TUR
-- Cluj-Napoca - Huedin - Alesd - Oradea - Arad - Ardaul Nou - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(35, 43, 0, 0, 0),       
(35, 46, 50, 45, 47),    
(35, 26, 114, 110, 112), 
(35, 24, 152, 160, 170), 
(35, 13, 273, 290, 295), 
(35, 14, 279, 305, 307), 
(35, 116, 330, 380, 380);

-- R Cluj-Napoca - Timisoara Nord RETUR 
-- Timisoara Nord - Aradul Nou - Arad - Oradea - Alesd - Huedin - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(36, 116, 0, 0, 0),       
(36, 14, 51, 73, 75),     
(36, 13, 57, 85, 90),     
(36, 24, 178, 210, 220),  
(36, 26, 216, 268, 270),  
(36, 46, 280, 333, 335),  
(36, 43, 330, 380, 380);  

-- IR Cluj-Napoca - Oradea TUR
-- Cluj-Napoca - Oradea 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(37, 43, 0, 0, 0),        
(37, 24, 152, 150, 150);  

-- IR Cluj-Napoca - Oradea RETUR
--  Oradea - Cluj-Napoca 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(38, 24, 0, 0, 0),        
(38, 43, 152, 150, 150);  

-- R Cluj-Napoca - Ordea TUR
-- Cluj-Napoca - Huedin - Alesd - Oradea Est - Oradea
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(39, 43, 0, 0, 0),        
(39, 46, 50, 50, 52),    
(39, 26, 114, 115, 117),  
(39, 25, 148, 145, 146),  
(39, 24, 152, 160, 160); 

-- R Cluj-Napoca - Oradea RETUR 
-- Oradea - Ordea Est - Alesd - Huedin - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(40, 24, 0, 0, 0),        
(40, 25, 4, 10, 11),      
(40, 26, 38, 45, 47),     
(40, 46, 102, 110, 112),  
(40, 43, 152, 160, 160);  

-- R Cluj-Napoca - Baia Mare TUR
-- Cluj-Napoca - Gherla - Dej Caltori - Jibou - Baia Mare
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(41, 43, 0, 0, 0),        
(41, 45, 45, 45, 47),     
(41, 44, 59, 65, 75),     
(41, 105, 122, 135, 137), 
(41, 83, 193, 210, 210); 

-- R Cluj-Napoca - Baia Mare RETUR
-- Baia Mare - Jicou - Dej Calatori - Gherla - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(42, 83, 0, 0, 0),        
(42, 105, 71, 70, 72),    
(42, 44, 134, 135, 145),  
(42, 45, 148, 163, 165),  
(42, 43, 193, 210, 210);  

-- R Cluj-Napoca - Brasov TUR
-- Cluj-Napoca - Aiud - Teius - Blaj - Medias  - Sighisoara - Brasov 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(43, 43, 0, 0, 0),       
(43, 9, 86, 75, 77),     
(43, 11, 101, 95, 100),    
(43, 10, 116, 115, 117),   
(43, 107, 165, 160, 162),
(43, 88, 203, 195, 200),  
(43, 33, 331, 330, 330);   

-- R Cluj-Napoca - Brasov RETUR
-- Brasov - Sighisoara - Medias - Blaj - Teius - Aiud - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(44, 33, 0, 0, 0),         
(44, 88, 128, 130, 135),   
(44, 107, 166, 168, 170), 
(44, 10, 215, 213, 215),   
(44, 11, 230, 230, 235),   
(44, 9, 245, 253, 255),    
(44, 43, 331, 330, 330);   

-- IR Iasi - Timisoara Nord TUR
-- Iasi - Pascani - Suceava - Cluj-Napoca - Oradea - Arad - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(45, 78, 0, 0, 0),        
(45, 79, 76, 55, 60),    
(45, 109, 138, 110, 115), 
(45, 43, 385, 360, 375), 
(45, 24, 537, 520, 530),
(45, 13, 658, 650, 655), 
(45, 116, 715, 720, 720);

-- IR Iasi - Timisoara Nord RETUR
-- Timisoara Nord - Arad - Oradea - Cluj Napoca Suceava - Pascani - Iasi
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(46, 116, 0, 0, 0),       
(46, 13, 57, 55, 60),     
(46, 24, 178, 180, 190),  
(46, 43, 330, 345, 360),  
(46, 109, 577, 605, 610), 
(46, 79, 639, 660, 665),  
(46, 78, 715, 720, 720);  

-- IR Iasi - Cluj-Napoca TUR
-- Iasi - Pascani - Suceava - Vatra Dornei - Dej Calatori - Cluj-Napoca
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(47, 78, 0, 0, 0),        
(47, 79, 76, 55, 57),     
(47, 109, 138, 110, 115), 
(47, 110, 254, 230, 232), 
(47, 44, 326, 300, 310),  
(47, 43, 385, 360, 360); 

-- IR Iasi - Cluj-Napoca RETUR
-- Cluj-Napoca - Dej Calatori - Vatra Dornei - Suceava - Pascani - Iasi 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(48, 43, 0, 0, 0),        
(48, 44, 59, 50, 60),     
(48, 110, 131, 130, 132), 
(48, 109, 247, 245, 250), 
(48, 79, 309, 303, 305),  
(48, 78, 385, 360, 360);  

-- IR Iasi - Constanta TUR
-- Iasi - Vaslui - Barlad - Tecuci - Buzau - Fetesti - Constanta
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(49, 78, 0, 0, 0),       
(49, 121, 75, 60, 62),   
(49, 122, 125, 105, 107), 
(49, 64, 175, 150, 155),  
(49, 39, 280, 240, 245),  
(49, 76, 360, 310, 312),  
(49, 47, 439, 380, 380);

-- IR Iasi - Constanta RETUR
-- Constanta - Fetesti - Buzau - Tecuci - Barlad - Vaslui - Iasi
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(50, 47, 0, 0, 0),        
(50, 76, 79, 70, 72),     
(50, 39, 159, 140, 145),  
(50, 64, 264, 230, 235),  
(50, 122, 314, 273, 275), 
(50, 121, 364, 318, 320), 
(50, 78, 439, 380, 380);  

-- IR Iasi - Galati TUR
-- Iasi - Vaslui - Barlad - Tecuci - Galati
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(51, 78, 0, 0, 0),        
(51, 121, 75, 70, 72),    
(51, 122, 125, 120, 122), 
(51, 64, 175, 170, 175), 
(51, 62, 255, 240, 240);  

-- IR Iasi - Galati RETUR
-- Galati - Tecuci - Barlad - Vaslui - Iasi
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(52, 62, 0, 0, 0),        
(52, 64, 80, 70, 75),     
(52, 122, 130, 123, 125), 
(52, 121, 180, 168, 170), 
(52, 78, 255, 240, 240);  

-- R Brasov - Sibiu TUR 
-- Brasov - Codlea - Fagaras - Sibiu
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(53, 33, 0, 0, 0),       
(53, 35, 15, 20, 21),   
(53, 34, 66, 75, 77),    
(53, 106, 149, 160, 160);

-- R Brasov - Sibiu RETUR 
-- Sibiu - Fagaras - Codlea - Brasov 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(54, 106, 0, 0, 0),      
(54, 34, 83, 85, 87),    
(54, 35, 134, 140, 141), 
(54, 33, 149, 160, 160); 

-- R Brasov - Sighisoara TUR
-- Brasov - Sighisoara
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(55, 33, 0, 0, 0),       
(55, 88, 128, 110, 110); 

-- R Brasov - Sighisoara RETUR
-- Sighisoara - Brasov
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(56, 88, 0, 0, 0),      
(56, 33, 128, 110, 110);

-- R Brasov - Sf. Gheorghe TUR
-- Brasov - Sf. Gheorghe
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(57, 33, 0, 0, 0),       
(57, 54, 32, 40, 40);    

-- R Brasov - Sf. Gheorghe RETUR
-- Sf. Gheorghe - Brasov 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(58, 54, 0, 0, 0),      
(58, 33, 32, 40, 40);    

-- R Timisoara Nord - Arad TUR
-- Timisoara Nord - Ardul Nou - Arad
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(59, 116, 0, 0, 0),       
(59, 14, 51, 55, 56),     
(59, 13, 57, 65, 65);     

-- R Timisoara Nord - Arad RETUR
-- Arad - Ardul Nou - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(60, 13, 0, 0, 0),       
(60, 14, 6, 10, 11),      
(60, 116, 57, 65, 65);    

--IR Timisoara Nord - Arad TUR
-- Timisoara Nord - Arad
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(61, 116, 0, 0, 0),      
(61, 13, 57, 45, 45);    

-- IR Timisoara Nord - Arad RETUR
-- Arad - Timisoara Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(62, 13, 0, 0, 0),       
(62, 116, 57, 45, 45);    

-- IR Timisoara Nord - Drobeta Turnu Severin TUR
-- Timisoara Nord - Lugoj - Drobeta Turnu Severin
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(63, 116, 0, 0, 0),       
(63, 118, 60, 50, 52),    
(63, 85, 210, 180, 180);  

-- IR Timisoara Nord - Drobeta Turnu Severin RETUR
-- Drobeta Turnu Severin - Lugoj - Timisoara Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(64, 85, 0, 0, 0),       
(64, 118, 150, 130, 132), 
(64, 116, 210, 180, 180); 

-- R Tmisoara Nord - Drobeta Turnu Severin TUR
-- Timisoara Nord - Lugoj - Orsova - Drobeta Turnu Severin
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(65, 116, 0, 0, 0),       
(65, 118, 60, 60, 62),    
(65, 86, 185, 210, 212),  
(65, 85, 210, 240, 240);  

-- R Timisoara Nord - Drobeta Turnu Severin RETUR
-- Drobeta Turnu Severin - Orsova - Lugoj - Timisoara Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(66, 85, 0, 0, 0),      
(66, 86, 25, 30, 32),   
(66, 118, 150, 180, 182), 
(66, 116, 210, 240, 240); 

-- R Timisoara Nord - Resita Nord TUR
-- Timisoara Nord - Lugoj - Resita Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(67, 116, 0, 0, 0),
(67, 118, 60, 55, 57),
(67, 127, 100, 110, 110);

-- R Timisoara Nord - Resita Nord RETUR
-- Resita Nord- Lugoj - Timisoara Nord 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(68, 127, 0, 0, 0), 
(68, 118, 40, 53, 55), 
(68, 116, 100, 110, 110);

-- R Constanta - Mangalia TUR
--Constanta - Eforie Nord - Eforie Sud - Costinesti - Mangalia
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(69, 47, 0, 0, 0), 
(69, 51, 14, 20, 22), 
(69, 52, 17, 28, 30), 
(69, 53, 28, 45, 47), 
(69, 48, 43, 65, 65);

-- R Constanta - Mangalia RETUR
--Mangalia - Costinesti - Eforie Sud - Eforie Nord -Constanta  
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(70, 48, 0, 0, 0), 
(70, 53, 15, 18, 20), 
(70, 52, 26, 35, 37), 
(70, 51, 29, 43, 45), 
(70, 47, 43, 65, 65);

-- R Constanta - Tulcea Oras TUR
-- Constanta - Medgidia - Tulcea Oras
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(71, 47, 0, 0, 0), 
(71, 49, 34, 35, 45), 
(71, 120, 179, 210, 210);

-- R Constanta - Tulcea Oras RETUR
--Tulcea Oras - Medgidia - Constanta
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(72, 120, 0, 0, 0), 
(72, 49, 145, 165, 175), 
(72, 47, 179, 210, 210);

-- IR Constanta - Buzau TUR 
-- Constanta - Fetesti - Buzau
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(73, 47, 0, 0, 0), 
(73, 76, 79, 55, 57), 
(73, 39, 205, 150, 150);

-- IR Constanta - Buzau RETUR 
-- Buzau- Fetesti -Constanta  
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(74, 39, 0, 0, 0), 
(74, 76, 126, 93, 95), 
(74, 47, 205, 150, 150);

-- R Constanta - Buzau TUR 
-- Constanta - Medgidia - Fetesti - Faurei - Buzau
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(75, 47, 0, 0, 0), 
(75, 49, 34, 30, 32), 
(75, 76, 79, 70, 72), 
(75, 38, 165, 130, 132), 
(75, 39, 205, 170, 170);

-- R Constanta - Buzau RETUR 
-- Buzau- Faurei - Fetesti - Medgidia - Constanta   
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(76, 39, 0, 0, 0), 
(76, 38, 40, 40, 42), 
(76, 76, 126, 100, 102), 
(76, 49, 171, 138, 140),
(76, 47, 205, 170, 170);

-- R Craiova - Calafat TUR
-- Craiova - Bailesti - Calafat
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(77, 58, 0, 0, 0), 
(77, 60, 57, 60, 62),
(77, 61, 107, 110, 110);

-- R Craiova - Calafat RETUR
-- Calafat - Bailesti - Craiova 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(78, 61, 0, 0, 0), 
(78, 60, 50, 48, 50), 
(78, 58, 107, 110, 110);

-- R Craiova - Targu Jiu TUR
-- Craiova - Filiasi - Targu Jiu
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(79, 58, 0, 0, 0), 
(79, 59, 36, 35, 37),
(79, 65, 113, 110, 110);

-- R Craiova - Targu Jiu RETUR
-- Targu Jiu - Filiasi -Craiova  
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(80, 65, 0, 0, 0), 
(80, 59, 77, 73, 75), 
(80, 58, 113, 110, 110);

-- IR Craiova - Drobeta Turnu Severin TUR
-- Craiova - Filiasi - Drobeta Turnu Severin
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(81, 58, 0, 0, 0), 
(81, 59, 36, 25, 27),
(81, 85, 114, 90, 90);

-- IR Craiova - Drobeta Turnu Severin RETUR
-- Drobeta Turnu Severin - Filiasi - Craiova 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(82, 85, 0, 0, 0), 
(82, 59, 78, 63, 65), 
(82, 58, 114, 90, 90);

-- R Craiova - Drobeta Turnu Severin TUR
-- Craiova - Filiasi - Strehaia - Drobeta Turnu Severin
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(83, 58, 0, 0, 0),        
(83, 59, 36, 40, 42),    
(83, 130, 60, 70, 72),    
(83, 85, 114, 130, 130);  

-- R Craiova - Drobeta Turnu Severin RETUR
-- Drobeta Turnu Severin - Strehaia - Filiasi - Craiova 
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(84, 85, 0, 0, 0),        
(84, 130, 54, 55, 57),    
(84, 59, 78, 88, 90),     
(84, 58, 114, 130, 130);  

-- R Buzău - Galați TUR
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(85, 39, 0, 0, 0), 
(85, 38, 40, 45, 47),
(85, 37, 101, 100, 102), 
(85, 62, 132, 135, 135);

-- R Buzău - Galați RETUR
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(86, 62, 0, 0, 0), 
(86, 37, 31, 33, 35),
(86, 38, 92, 88, 90), 
(86, 39, 132, 135, 135);

-- R Buzău - Mărășești TUR
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(87, 39, 0, 0, 0),
(87, 40, 33, 35, 37),
(87, 126, 90, 95, 95);

-- R Buzău - Mărășești TUR
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(88, 126, 0, 0, 0), 
(88, 40, 57, 58, 60), 
(88, 39, 90, 95, 95);

-- 89-90: R Ploiești Sud - Târgoviște
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(89, 96, 0, 0, 0), (89, 55, 52, 65, 65),
(90, 55, 0, 0, 0), (90, 96, 52, 65, 65);

-- 91-92: R Ploiești Sud - Buzău
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(91, 96, 0, 0, 0), (91, 39, 69, 60, 60),
(92, 39, 0, 0, 0), (92, 96, 69, 60, 60);

-- 93-94: R Suceava - Vatra Dornei
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(93, 109, 0, 0, 0), (93, 112, 47, 55, 57), (93, 110, 116, 140, 140),
(94, 110, 0, 0, 0), (94, 112, 69, 83, 85), (94, 109, 116, 140, 140);

-- 95-96: R Suceava - Rădăuți
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(95, 109, 0, 0, 0), (95, 111, 47, 55, 55),
(96, 111, 0, 0, 0), (96, 109, 47, 55, 55);

-- 97-98: R Satu Mare - Baia Mare
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(97, 102, 0, 0, 0), (97, 83, 60, 75, 75),
(98, 83, 0, 0, 0), (98, 102, 60, 75, 75);

-- 99-100: R Satu Mare - Oradea
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(99, 102, 0, 0, 0), (99, 103, 36, 42, 44), (99, 24, 133, 160, 160),
(100, 24, 0, 0, 0), (100, 103, 97, 116, 118), (100, 102, 133, 160, 160);

-- 101-104: Alba Iulia - Teiuș / Deva
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(101, 8, 0, 0, 0), (101, 11, 14, 20, 20), (102, 11, 0, 0, 0), (102, 8, 14, 20, 20),
(103, 8, 0, 0, 0), (103, 12, 15, 18, 20), (103, 70, 70, 80, 80),
(104, 70, 0, 0, 0), (104, 12, 55, 60, 62), (104, 8, 70, 80, 80);

-- 105-106: R Sibiu - Râmnicu Vâlcea
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(105, 106, 0, 0, 0), (105, 123, 100, 160, 160),
(106, 123, 0, 0, 0), (106, 106, 100, 160, 160);

-- 107-108: R Pitești - Curtea de Argeș
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(107, 16, 0, 0, 0), (107, 18, 38, 55, 55),
(108, 18, 0, 0, 0), (108, 16, 38, 55, 55);

-- 109-110: R Bacău - Piatra Neamț (Include Buhuși)
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(109, 20, 0, 0, 0), (109, 23, 25, 30, 31), (109, 90, 60, 85, 85),
(110, 90, 0, 0, 0), (110, 23, 35, 54, 55), (110, 20, 60, 85, 85);

-- 111-112: R Bacău - Onești
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(111, 20, 0, 0, 0), (111, 21, 53, 75, 75),
(112, 21, 0, 0, 0), (112, 20, 53, 75, 75);

-- 113-114: R Arad - Oradea (Include Salonta)
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(113, 13, 0, 0, 0), (113, 129, 75, 80, 82), (113, 24, 116, 130, 130),
(114, 24, 0, 0, 0), (114, 129, 41, 48, 50), (114, 13, 116, 130, 130);

-- 115-116: R Deva - Simeria
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(115, 70, 0, 0, 0), (115, 71, 7, 12, 12),
(116, 71, 0, 0, 0), (116, 70, 7, 12, 12);

-- 117-118: R Sighișoara - Târgu Mureș
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(117, 88, 0, 0, 0), (117, 89, 40, 45, 47), (117, 87, 55, 65, 65),
(118, 87, 0, 0, 0), (118, 89, 15, 18, 20), (118, 88, 55, 65, 65);

-- 119-120: IR Suceava - București Nord
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(119, 109, 0, 0, 0), (119, 79, 76, 55, 60), (119, 20, 161, 130, 135), (119, 39, 319, 260, 265), (119, 1, 447, 360, 360),
(120, 1, 0, 0, 0), (120, 39, 128, 95, 100), (120, 20, 286, 225, 230), (120, 79, 371, 300, 305), (120, 109, 447, 360, 360);

-- 121-122: R Suceava - Pașcani
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(121, 109, 0, 0, 0), (121, 79, 76, 80, 80),
(122, 79, 0, 0, 0), (122, 109, 76, 80, 80);

-- 123-124: IR Iași - Brașov
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(123, 78, 0, 0, 0), (123, 79, 76, 60, 65), (123, 20, 161, 130, 135), (123, 33, 463, 420, 420),
(124, 33, 0, 0, 0), (124, 20, 302, 285, 290), (124, 79, 387, 355, 360), (124, 78, 463, 420, 420);

-- 125-130: Segmente Moldova / Adjud / Focșani
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(125, 78, 0, 0, 0), (125, 20, 161, 160, 160), (126, 20, 0, 0, 0), (126, 78, 161, 160, 160),
(127, 20, 0, 0, 0), (127, 7, 58, 65, 65), (128, 7, 0, 0, 0), (128, 20, 58, 65, 65),
(129, 7, 0, 0, 0), (129, 125, 20, 30, 30), (130, 125, 0, 0, 0), (130, 7, 20, 30, 30);

-- 131-134: Botoșani - București / Verești
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(131, 31, 0, 0, 0), (131, 128, 44, 45, 60), (131, 79, 90, 110, 115), (131, 1, 461, 460, 460),
(132, 1, 0, 0, 0), (132, 79, 371, 345, 350), (132, 128, 417, 400, 415), (132, 31, 461, 460, 460),
(133, 31, 0, 0, 0), (133, 128, 44, 55, 55), (134, 128, 0, 0, 0), (134, 31, 44, 55, 55);

-- 135-138: Cluj-Napoca - Satu Mare / Dej
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(135, 43, 0, 0, 0), (135, 44, 59, 50, 60), (135, 102, 192, 185, 185),
(136, 102, 0, 0, 0), (136, 44, 133, 125, 135), (136, 43, 192, 185, 185),
(137, 43, 0, 0, 0), (137, 44, 59, 75, 75), (138, 44, 0, 0, 0), (138, 43, 59, 75, 75);

-- 139-142: Sibiu - București / Mediaș
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(139, 106, 0, 0, 0), (139, 107, 55, 65, 70), (139, 1, 315, 310, 310),
(140, 1, 0, 0, 0), (140, 107, 260, 240, 245), (140, 106, 315, 310, 310),
(141, 106, 0, 0, 0), (141, 107, 55, 80, 80), (142, 107, 0, 0, 0), (142, 106, 55, 80, 80);

-- 143-150: Deva - Arad, Arad - Aradul Nou, Alba - Vințu, Teiuș - Blaj
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(143, 70, 0, 0, 0), (143, 15, 115, 105, 107), (143, 13, 150, 145, 145),
(144, 13, 0, 0, 0), (144, 15, 35, 38, 40), (144, 70, 150, 145, 145),
(145, 13, 0, 0, 0), (145, 14, 6, 12, 12), (146, 14, 0, 0, 0), (146, 13, 6, 12, 12),
(147, 8, 0, 0, 0), (147, 12, 15, 22, 22), (148, 12, 0, 0, 0), (148, 8, 15, 22, 22),
(149, 11, 0, 0, 0), (149, 10, 15, 22, 22), (150, 10, 0, 0, 0), (150, 11, 15, 22, 22);

-- 151-154: IR Craiova - Timișoara / R Filiași
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(151, 58, 0, 0, 0), (151, 85, 114, 95, 100), (151, 116, 324, 310, 310),
(152, 116, 0, 0, 0), (152, 85, 210, 210, 215), (152, 58, 324, 310, 310),
(153, 58, 0, 0, 0), (153, 59, 36, 45, 45), (154, 59, 0, 0, 0), (154, 58, 36, 45, 45);

-- 155-158: R Pitești - Slatina - Piatra Olt (Include Balș)
INSERT INTO StopInfo (route_id, station_id, km_from_origin, arrival_minutes, departure_minutes) VALUES 
(155, 16, 0, 0, 0), (155, 93, 70, 95, 95),
(156, 93, 0, 0, 0), (156, 16, 70, 95, 95),
(157, 93, 0, 0, 0), (157, 132, 25, 30, 32), (157, 95, 43, 55, 55),
(158, 95, 0, 0, 0), (158, 132, 18, 23, 25), (158, 93, 43, 55, 55);

SELECT route_id, COUNT(*) FROM StopInfo GROUP BY route_id;