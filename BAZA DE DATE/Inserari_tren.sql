INSERT INTO Train (train_number, train_type, train_status, number_of_wagons, price_multiplier, route_id) VALUES
-- Ruta 1 (IR): InterCity si InterRegio
('TR-001', 'InterCity', 'Activ', 7, 1.4, 1), ('TR-002', 'InterCity', 'Activ', 8, 1.5, 1), ('TR-003', 'InterCity', 'Activ', 9, 1.5, 1), ('TR-004', 'InterCity', 'Activ', 6, 1.3, 1), ('TR-005', 'InterRegio', 'Activ', 5, 1.2, 1), ('TR-006', 'InterRegio', 'Activ', 6, 1.2, 1), ('TR-007', 'InterRegio', 'Activ', 4, 1.1, 1), ('TR-008', 'InterRegio', 'Activ', 5, 1.1, 1),
-- Ruta 2 (IR): InterCity si InterRegio
('TR-009', 'InterCity', 'Activ', 9, 1.5, 2), ('TR-010', 'InterCity', 'Activ', 7, 1.4, 2), ('TR-011', 'InterCity', 'Activ', 8, 1.4, 2), ('TR-012', 'InterCity', 'Activ', 6, 1.3, 2), ('TR-013', 'InterRegio', 'Activ', 6, 1.2, 2), ('TR-014', 'InterRegio', 'Activ', 5, 1.1, 2), ('TR-015', 'InterRegio', 'Activ', 7, 1.2, 2), ('TR-016', 'InterRegio', 'Activ', 4, 1.1, 2),
-- Rutele 3-4 (R): Regio
('TR-017', 'Regio', 'Activ', 3, 0.9, 3), ('TR-018', 'Regio', 'Activ', 4, 1.0, 3), ('TR-019', 'Regio', 'Activ', 2, 0.8, 3), ('TR-020', 'Regio', 'Activ', 5, 1.0, 3), ('TR-021', 'Regio', 'Activ', 3, 0.9, 3), ('TR-022', 'Regio', 'Activ', 4, 0.9, 3), ('TR-023', 'Regio', 'Activ', 2, 0.8, 3), ('TR-024', 'Regio', 'Activ', 5, 1.0, 3),
('TR-025', 'Regio', 'Activ', 4, 1.0, 4), ('TR-026', 'Regio', 'Activ', 3, 0.9, 4), ('TR-027', 'Regio', 'Activ', 5, 1.0, 4), ('TR-028', 'Regio', 'Activ', 2, 0.8, 4), ('TR-029', 'Regio', 'Activ', 4, 0.9, 4), ('TR-030', 'Regio', 'Activ', 3, 0.9, 4), ('TR-031', 'Regio', 'Activ', 5, 1.0, 4), ('TR-032', 'Regio', 'Activ', 2, 0.8, 4),
-- Rutele 5-6 (IR): InterCity si InterRegio
('TR-033', 'InterCity', 'Activ', 8, 1.4, 5), ('TR-034', 'InterCity', 'Activ', 7, 1.3, 5), ('TR-035', 'InterCity', 'Activ', 9, 1.5, 5), ('TR-036', 'InterCity', 'Activ', 6, 1.3, 5), ('TR-037', 'InterRegio', 'Activ', 5, 1.1, 5), ('TR-038', 'InterRegio', 'Activ', 4, 1.1, 5), ('TR-039', 'InterRegio', 'Activ', 6, 1.2, 5), ('TR-040', 'InterRegio', 'Activ', 5, 1.1, 5),
('TR-041', 'InterCity', 'Activ', 7, 1.3, 6), ('TR-042', 'InterCity', 'Activ', 8, 1.4, 6), ('TR-043', 'InterCity', 'Activ', 9, 1.5, 6), ('TR-044', 'InterCity', 'Activ', 7, 1.3, 6), ('TR-045', 'InterRegio', 'Activ', 5, 1.1, 6), ('TR-046', 'InterRegio', 'Activ', 6, 1.2, 6), ('TR-047', 'InterRegio', 'Activ', 4, 1.1, 6), ('TR-048', 'InterRegio', 'Activ', 5, 1.1, 6),
-- Rutele 7-8 (R): Regio
('TR-049', 'Regio', 'Activ', 2, 0.8, 7), ('TR-050', 'Regio', 'Activ', 4, 1.0, 7), ('TR-051', 'Regio', 'Activ', 3, 0.9, 7), ('TR-052', 'Regio', 'Activ', 5, 1.0, 7), ('TR-053', 'Regio', 'Activ', 2, 0.8, 7), ('TR-054', 'Regio', 'Activ', 4, 0.9, 7), ('TR-055', 'Regio', 'Activ', 3, 0.9, 7), ('TR-056', 'Regio', 'Activ', 5, 1.0, 7),
('TR-057', 'Regio', 'Activ', 3, 0.9, 8), ('TR-058', 'Regio', 'Activ', 2, 0.8, 8), ('TR-059', 'Regio', 'Activ', 4, 1.0, 8), ('TR-060', 'Regio', 'Activ', 3, 0.9, 8), ('TR-061', 'Regio', 'Activ', 5, 1.0, 8), ('TR-062', 'Regio', 'Activ', 2, 0.8, 8), ('TR-063', 'Regio', 'Activ', 4, 0.9, 8), ('TR-064', 'Regio', 'Activ', 3, 0.9, 8),
-- Rutele 9-10 (IR): InterCity si InterRegio
('TR-065', 'InterCity', 'Activ', 9, 1.5, 9), ('TR-066', 'InterCity', 'Activ', 8, 1.4, 9), ('TR-067', 'InterCity', 'Activ', 7, 1.3, 9), ('TR-068', 'InterCity', 'Activ', 6, 1.3, 9), ('TR-069', 'InterRegio', 'Activ', 5, 1.1, 9), ('TR-070', 'InterRegio', 'Activ', 6, 1.2, 9), ('TR-071', 'InterRegio', 'Activ', 4, 1.1, 9), ('TR-072', 'InterRegio', 'Activ', 5, 1.1, 9),
('TR-073', 'InterCity', 'Activ', 7, 1.3, 10), ('TR-074', 'InterCity', 'Activ', 9, 1.5, 10), ('TR-075', 'InterCity', 'Activ', 8, 1.4, 10), ('TR-076', 'InterCity', 'Activ', 7, 1.3, 10), ('TR-077', 'InterRegio', 'Activ', 4, 1.1, 10), ('TR-078', 'InterRegio', 'Activ', 6, 1.2, 10), ('TR-079', 'InterRegio', 'Activ', 5, 1.1, 10), ('TR-080', 'InterRegio', 'Activ', 4, 1.1, 10),
-- Rutele 11-12 (R): Regio
('TR-081', 'Regio', 'Activ', 2, 0.8, 11), ('TR-082', 'Regio', 'Activ', 4, 1.0, 11), ('TR-083', 'Regio', 'Activ', 3, 0.9, 11), ('TR-084', 'Regio', 'Activ', 5, 1.0, 11), ('TR-085', 'Regio', 'Activ', 2, 0.8, 11), ('TR-086', 'Regio', 'Activ', 4, 0.9, 11), ('TR-087', 'Regio', 'Activ', 3, 0.9, 11), ('TR-088', 'Regio', 'Activ', 5, 1.0, 11),
('TR-089', 'Regio', 'Activ', 3, 0.9, 12), ('TR-090', 'Regio', 'Activ', 2, 0.8, 12), ('TR-091', 'Regio', 'Activ', 4, 1.0, 12), ('TR-092', 'Regio', 'Activ', 3, 0.9, 12), ('TR-093', 'Regio', 'Activ', 5, 1.0, 12), ('TR-094', 'Regio', 'Activ', 2, 0.8, 12), ('TR-095', 'Regio', 'Activ', 4, 0.9, 12), ('TR-096', 'Regio', 'Activ', 3, 0.9, 12),
-- Rutele 13-14 (IR): InterCity si InterRegio
('TR-097', 'InterCity', 'Activ', 8, 1.4, 13), ('TR-098', 'InterCity', 'Activ', 7, 1.3, 13), ('TR-099', 'InterCity', 'Activ', 9, 1.5, 13), ('TR-100', 'InterCity', 'Activ', 6, 1.3, 13), ('TR-101', 'InterRegio', 'Activ', 5, 1.1, 13), ('TR-102', 'InterRegio', 'Activ', 4, 1.1, 13), ('TR-103', 'InterRegio', 'Activ', 6, 1.2, 13), ('TR-104', 'InterRegio', 'Activ', 5, 1.1, 13),
('TR-105', 'InterCity', 'Activ', 9, 1.5, 14), ('TR-106', 'InterCity', 'Activ', 8, 1.4, 14), ('TR-107', 'InterCity', 'Activ', 7, 1.3, 14), ('TR-108', 'InterCity', 'Activ', 8, 1.4, 14), ('TR-109', 'InterRegio', 'Activ', 6, 1.2, 14), ('TR-110', 'InterRegio', 'Activ', 5, 1.1, 14), ('TR-111', 'InterRegio', 'Activ', 4, 1.1, 14), ('TR-112', 'InterRegio', 'Activ', 6, 1.2, 14),
-- Rutele 15-16 (R): Regio
('TR-113', 'Regio', 'Activ', 2, 0.8, 15), ('TR-114', 'Regio', 'Activ', 4, 1.0, 15), ('TR-115', 'Regio', 'Activ', 3, 0.9, 15), ('TR-116', 'Regio', 'Activ', 5, 1.0, 15), ('TR-117', 'Regio', 'Activ', 2, 0.8, 15), ('TR-118', 'Regio', 'Activ', 4, 0.9, 15), ('TR-119', 'Regio', 'Activ', 3, 0.9, 15), ('TR-120', 'Regio', 'Activ', 5, 1.0, 15),
('TR-121', 'Regio', 'Activ', 3, 0.9, 16), ('TR-122', 'Regio', 'Activ', 2, 0.8, 16), ('TR-123', 'Regio', 'Activ', 4, 1.0, 16), ('TR-124', 'Regio', 'Activ', 3, 0.9, 16), ('TR-125', 'Regio', 'Activ', 5, 1.0, 16), ('TR-126', 'Regio', 'Activ', 2, 0.8, 16), ('TR-127', 'Regio', 'Activ', 4, 0.9, 16), ('TR-128', 'Regio', 'Activ', 3, 0.9, 16),
-- Rutele 17-18 (IR): InterCity si InterRegio
('TR-129', 'InterCity', 'Activ', 7, 1.3, 17), ('TR-130', 'InterCity', 'Activ', 9, 1.5, 17), ('TR-131', 'InterCity', 'Activ', 8, 1.4, 17), ('TR-132', 'InterCity', 'Activ', 7, 1.3, 17), ('TR-133', 'InterRegio', 'Activ', 4, 1.1, 17), ('TR-134', 'InterRegio', 'Activ', 6, 1.2, 17), ('TR-135', 'InterRegio', 'Activ', 5, 1.1, 17), ('TR-136', 'InterRegio', 'Activ', 4, 1.1, 17),
('TR-137', 'InterCity', 'Activ', 8, 1.4, 18), ('TR-138', 'InterCity', 'Activ', 7, 1.3, 18), ('TR-139', 'InterCity', 'Activ', 9, 1.5, 18), ('TR-140', 'InterCity', 'Activ', 8, 1.4, 18), ('TR-141', 'InterRegio', 'Activ', 5, 1.1, 18), ('TR-142', 'InterRegio', 'Activ', 4, 1.1, 18), ('TR-143', 'InterRegio', 'Activ', 6, 1.2, 18), ('TR-144', 'InterRegio', 'Activ', 5, 1.1, 18),
-- Rutele 19-20 (R): Regio
('TR-145', 'Regio', 'Activ', 3, 0.9, 19), ('TR-146', 'Regio', 'Activ', 2, 0.8, 19), ('TR-147', 'Regio', 'Activ', 4, 1.0, 19), ('TR-148', 'Regio', 'Activ', 3, 0.9, 19), ('TR-149', 'Regio', 'Activ', 5, 1.0, 19), ('TR-150', 'Regio', 'Activ', 2, 0.8, 19), ('TR-151', 'Regio', 'Activ', 4, 0.9, 19), ('TR-152', 'Regio', 'Activ', 3, 0.9, 19),
('TR-153', 'Regio', 'Activ', 2, 0.8, 20), ('TR-154', 'Regio', 'Activ', 4, 1.0, 20), ('TR-155', 'Regio', 'Activ', 3, 0.9, 20), ('TR-156', 'Regio', 'Activ', 5, 1.0, 20), ('TR-157', 'Regio', 'Activ', 2, 0.8, 20), ('TR-158', 'Regio', 'Activ', 4, 0.9, 20), ('TR-159', 'Regio', 'Activ', 3, 0.9, 20), ('TR-160', 'Regio', 'Activ', 5, 1.0, 20),
-- Rutele 21-22 (IR): InterCity si InterRegio
('TR-161', 'InterCity', 'Activ', 9, 1.5, 21), ('TR-162', 'InterCity', 'Activ', 8, 1.4, 21), ('TR-163', 'InterCity', 'Activ', 7, 1.3, 21), ('TR-164', 'InterCity', 'Activ', 6, 1.3, 21), ('TR-165', 'InterRegio', 'Activ', 6, 1.2, 21), ('TR-166', 'InterRegio', 'Activ', 5, 1.1, 21), ('TR-167', 'InterRegio', 'Activ', 4, 1.1, 21), ('TR-168', 'InterRegio', 'Activ', 5, 1.1, 21),
('TR-169', 'InterCity', 'Activ', 7, 1.3, 22), ('TR-170', 'InterCity', 'Activ', 9, 1.5, 22), ('TR-171', 'InterCity', 'Activ', 8, 1.4, 22), ('TR-172', 'InterCity', 'Activ', 7, 1.3, 22), ('TR-173', 'InterRegio', 'Activ', 4, 1.1, 22), ('TR-174', 'InterRegio', 'Activ', 6, 1.2, 22), ('TR-175', 'InterRegio', 'Activ', 5, 1.1, 22), ('TR-176', 'InterRegio', 'Activ', 4, 1.1, 22),
-- Rutele 23-24 (R): Regio
('TR-177', 'Regio', 'Activ', 3, 0.9, 23), ('TR-178', 'Regio', 'Activ', 2, 0.8, 23), ('TR-179', 'Regio', 'Activ', 4, 1.0, 23), ('TR-180', 'Regio', 'Activ', 3, 0.9, 23), ('TR-181', 'Regio', 'Activ', 5, 1.0, 23), ('TR-182', 'Regio', 'Activ', 2, 0.8, 23), ('TR-183', 'Regio', 'Activ', 4, 0.9, 23), ('TR-184', 'Regio', 'Activ', 3, 0.9, 23),
('TR-185', 'Regio', 'Activ', 2, 0.8, 24), ('TR-186', 'Regio', 'Activ', 4, 1.0, 24), ('TR-187', 'Regio', 'Activ', 3, 0.9, 24), ('TR-188', 'Regio', 'Activ', 5, 1.0, 24), ('TR-189', 'Regio', 'Activ', 2, 0.8, 24), ('TR-190', 'Regio', 'Activ', 4, 0.9, 24), ('TR-191', 'Regio', 'Activ', 3, 0.9, 24), ('TR-192', 'Regio', 'Activ', 5, 1.0, 24),
-- Rutele 25-26 (IR): InterCity si InterRegio
('TR-193', 'InterCity', 'Activ', 8, 1.4, 25), ('TR-194', 'InterCity', 'Activ', 7, 1.3, 25), ('TR-195', 'InterCity', 'Activ', 9, 1.5, 25), ('TR-196', 'InterCity', 'Activ', 8, 1.4, 25), ('TR-197', 'InterRegio', 'Activ', 5, 1.1, 25), ('TR-198', 'InterRegio', 'Activ', 4, 1.1, 25), ('TR-199', 'InterRegio', 'Activ', 6, 1.2, 25), ('TR-200', 'InterRegio', 'Activ', 5, 1.1, 25),
('TR-201', 'InterCity', 'Activ', 9, 1.5, 26), ('TR-202', 'InterCity', 'Activ', 8, 1.4, 26), ('TR-203', 'InterCity', 'Activ', 7, 1.3, 26), ('TR-204', 'InterCity', 'Activ', 9, 1.5, 26), ('TR-205', 'InterRegio', 'Activ', 6, 1.2, 26), ('TR-206', 'InterRegio', 'Activ', 5, 1.1, 26), ('TR-207', 'InterRegio', 'Activ', 4, 1.1, 26), ('TR-208', 'InterRegio', 'Activ', 6, 1.2, 26),
-- Rutele 27-28 (R): Regio
('TR-209', 'Regio', 'Activ', 3, 0.9, 27), ('TR-210', 'Regio', 'Activ', 2, 0.8, 27), ('TR-211', 'Regio', 'Activ', 4, 1.0, 27), ('TR-212', 'Regio', 'Activ', 3, 0.9, 27), ('TR-213', 'Regio', 'Activ', 5, 1.0, 27), ('TR-214', 'Regio', 'Activ', 2, 0.8, 27), ('TR-215', 'Regio', 'Activ', 4, 0.9, 27), ('TR-216', 'Regio', 'Activ', 3, 0.9, 27),
('TR-217', 'Regio', 'Activ', 2, 0.8, 28), ('TR-218', 'Regio', 'Activ', 4, 1.0, 28), ('TR-219', 'Regio', 'Activ', 3, 0.9, 28), ('TR-220', 'Regio', 'Activ', 5, 1.0, 28), ('TR-221', 'Regio', 'Activ', 2, 0.8, 28), ('TR-222', 'Regio', 'Activ', 4, 0.9, 28), ('TR-223', 'Regio', 'Activ', 3, 0.9, 28), ('TR-224', 'Regio', 'Activ', 5, 1.0, 28),
-- Rutele 43 44 (R): Regio
('TR-337', 'Regio', 'Activ', 3, 0.9, 43), ('TR-338', 'Regio', 'Activ', 2, 0.8, 43), ('TR-339', 'Regio', 'Activ', 4, 1.0, 43), ('TR-340', 'Regio', 'Activ', 3, 0.9, 43), ('TR-341', 'Regio', 'Activ', 5, 1.0, 43), ('TR-342', 'Regio', 'Activ', 2, 0.8, 43), ('TR-343', 'Regio', 'Activ', 4, 0.9, 43), ('TR-344', 'Regio', 'Activ', 3, 0.9, 43),
('TR-345', 'Regio', 'Activ', 2, 0.8, 44), ('TR-346', 'Regio', 'Activ', 4, 1.0, 44), ('TR-347', 'Regio', 'Activ', 3, 0.9, 44), ('TR-348', 'Regio', 'Activ', 5, 1.0, 44), ('TR-349', 'Regio', 'Activ', 2, 0.8, 44), ('TR-350', 'Regio', 'Activ', 4, 0.9, 44), ('TR-351', 'Regio', 'Activ', 3, 0.9, 44), ('TR-352', 'Regio', 'Activ', 5, 1.0, 44),
-- Rutele 47-50 (IR): InterCity si InterRegio
('TR-369', 'InterCity', 'Activ', 9, 1.5, 47), ('TR-370', 'InterCity', 'Activ', 8, 1.4, 47), ('TR-371', 'InterCity', 'Activ', 7, 1.3, 47), ('TR-372', 'InterCity', 'Activ', 9, 1.5, 47), ('TR-373', 'InterRegio', 'Activ', 6, 1.2, 47), ('TR-374', 'InterRegio', 'Activ', 5, 1.1, 47), ('TR-375', 'InterRegio', 'Activ', 4, 1.1, 47), ('TR-376', 'InterRegio', 'Activ', 6, 1.2, 47),
('TR-377', 'InterCity', 'Activ', 7, 1.3, 48), ('TR-378', 'InterCity', 'Activ', 9, 1.5, 48), ('TR-379', 'InterCity', 'Activ', 8, 1.4, 48), ('TR-380', 'InterCity', 'Activ', 7, 1.3, 48), ('TR-381', 'InterRegio', 'Activ', 4, 1.1, 48), ('TR-382', 'InterRegio', 'Activ', 6, 1.2, 48), ('TR-383', 'InterRegio', 'Activ', 5, 1.1, 48), ('TR-384', 'InterRegio', 'Activ', 4, 1.1, 48),
('TR-385', 'InterCity', 'Activ', 8, 1.4, 49), ('TR-386', 'InterCity', 'Activ', 7, 1.3, 49), ('TR-387', 'InterCity', 'Activ', 9, 1.5, 49), ('TR-388', 'InterCity', 'Activ', 8, 1.4, 49), ('TR-389', 'InterRegio', 'Activ', 5, 1.1, 49), ('TR-390', 'InterRegio', 'Activ', 4, 1.1, 49), ('TR-391', 'InterRegio', 'Activ', 6, 1.2, 49), ('TR-392', 'InterRegio', 'Activ', 5, 1.1, 49),
('TR-393', 'InterCity', 'Activ', 9, 1.5, 50), ('TR-394', 'InterCity', 'Activ', 8, 1.4, 50), ('TR-395', 'InterCity', 'Activ', 7, 1.3, 50), ('TR-396', 'InterCity', 'Activ', 8, 1.4, 50), ('TR-397', 'InterRegio', 'Activ', 6, 1.2, 50), ('TR-398', 'InterRegio', 'Activ', 5, 1.1, 50), ('TR-399', 'InterRegio', 'Activ', 4, 1.1, 50), ('TR-400', 'InterRegio', 'Activ', 6, 1.2, 50),
-- Ruta 119 (IR)
('TR-1268', 'InterCity', 'Activ', 8, 1.4, 119), ('TR-1269', 'InterCity', 'Activ', 7, 1.3, 119), ('TR-1270', 'InterCity', 'Activ', 9, 1.5, 119), ('TR-1271', 'InterCity', 'Activ', 8, 1.4, 119), ('TR-1272', 'InterRegio', 'Activ', 5, 1.1, 119), ('TR-1273', 'InterRegio', 'Activ', 4, 1.1, 119), ('TR-1274', 'InterRegio', 'Activ', 6, 1.2, 119), ('TR-1275', 'InterRegio', 'Activ', 5, 1.1, 119),
-- Ruta 120 (IR)
('TR-1276', 'InterCity', 'Activ', 9, 1.5, 120), ('TR-1277', 'InterCity', 'Activ', 8, 1.4, 120), ('TR-1278', 'InterCity', 'Activ', 7, 1.3, 120), ('TR-1279', 'InterCity', 'Activ', 8, 1.4, 120), ('TR-1280', 'InterRegio', 'Activ', 6, 1.2, 120), ('TR-1281', 'InterRegio', 'Activ', 5, 1.1, 120), ('TR-1282', 'InterRegio', 'Activ', 4, 1.1, 120), ('TR-1283', 'InterRegio', 'Activ', 6, 1.2, 120),
-- Ruta 123 (IR)
('TR-1284', 'InterCity', 'Activ', 7, 1.3, 123), ('TR-1285', 'InterCity', 'Activ', 9, 1.5, 123), ('TR-1286', 'InterCity', 'Activ', 8, 1.4, 123), ('TR-1287', 'InterCity', 'Activ', 7, 1.3, 123), ('TR-1288', 'InterRegio', 'Activ', 4, 1.1, 123), ('TR-1289', 'InterRegio', 'Activ', 6, 1.2, 123), ('TR-1290', 'InterRegio', 'Activ', 5, 1.1, 123), ('TR-1291', 'InterRegio', 'Activ', 4, 1.1, 123),
-- Ruta 124 (IR)
('TR-1292', 'InterCity', 'Activ', 8, 1.4, 124), ('TR-1293', 'InterCity', 'Activ', 7, 1.3, 124), ('TR-1294', 'InterCity', 'Activ', 9, 1.5, 124), ('TR-1295', 'InterCity', 'Activ', 8, 1.4, 124), ('TR-1296', 'InterRegio', 'Activ', 5, 1.1, 124), ('TR-1297', 'InterRegio', 'Activ', 4, 1.1, 124), ('TR-1298', 'InterRegio', 'Activ', 6, 1.2, 124), ('TR-1299', 'InterRegio', 'Activ', 5, 1.1, 124),
-- Ruta 131 (IR)
('TR-1300', 'InterCity', 'Activ', 9, 1.5, 131), ('TR-1301', 'InterCity', 'Activ', 8, 1.4, 131), ('TR-1302', 'InterCity', 'Activ', 7, 1.3, 131), ('TR-1303', 'InterCity', 'Activ', 9, 1.5, 131), ('TR-1304', 'InterRegio', 'Activ', 6, 1.2, 131), ('TR-1305', 'InterRegio', 'Activ', 5, 1.1, 131), ('TR-1306', 'InterRegio', 'Activ', 4, 1.1, 131), ('TR-1307', 'InterRegio', 'Activ', 6, 1.2, 131),
-- Ruta 132 (IR)
('TR-1308', 'InterCity', 'Activ', 7, 1.3, 132), ('TR-1309', 'InterCity', 'Activ', 9, 1.5, 132), ('TR-1310', 'InterCity', 'Activ', 8, 1.4, 132), ('TR-1311', 'InterCity', 'Activ', 7, 1.3, 132), ('TR-1312', 'InterRegio', 'Activ', 4, 1.1, 132), ('TR-1313', 'InterRegio', 'Activ', 6, 1.2, 132), ('TR-1314', 'InterRegio', 'Activ', 5, 1.1, 132), ('TR-1315', 'InterRegio', 'Activ', 4, 1.1, 132),
('TR-1316', 'InterCity', 'Activ', 8, 1.4, 152), ('TR-1317', 'InterCity', 'Activ', 7, 1.3, 152), ('TR-1318', 'InterCity', 'Activ', 9, 1.5, 152), ('TR-1319', 'InterCity', 'Activ', 8, 1.4, 152), ('TR-1320', 'InterRegio', 'Activ', 5, 1.1, 152), ('TR-1321', 'InterRegio', 'Activ', 4, 1.1, 152), ('TR-1322', 'InterRegio', 'Activ', 6, 1.2, 152), ('TR-1323', 'InterRegio', 'Activ', 5, 1.1, 152),
-- Ruta 153 (IR)
('TR-1324', 'InterCity', 'Activ', 9, 1.5, 153), ('TR-1325', 'InterCity', 'Activ', 8, 1.4, 153), ('TR-1326', 'InterCity', 'Activ', 7, 1.3, 153), ('TR-1327', 'InterCity', 'Activ', 9, 1.5, 153), ('TR-1328', 'InterRegio', 'Activ', 6, 1.2, 153), ('TR-1329', 'InterRegio', 'Activ', 5, 1.1, 153), ('TR-1330', 'InterRegio', 'Activ', 4, 1.1, 153), ('TR-1331', 'InterRegio', 'Activ', 6, 1.2, 153);
INSERT INTO Train (train_number, train_type, train_status, number_of_wagons, price_multiplier, route_id) VALUES
-- Rutele 29-30 (IR): 2 InterCity, 2 InterRegio
('TR-321', 'InterCity', 'Activ', 6, 1.20, 29), ('TR-322', 'InterCity', 'Activ', 5, 1.15, 29), ('TR-323', 'InterRegio', 'Activ', 4, 1.05, 29), ('TR-324', 'InterRegio', 'Activ', 5, 1.10, 29),
('TR-325', 'InterCity', 'Activ', 6, 1.25, 30), ('TR-326', 'InterCity', 'Activ', 5, 1.20, 30), ('TR-327', 'InterRegio', 'Activ', 4, 1.05, 30), ('TR-328', 'InterRegio', 'Activ', 5, 1.10, 30),

-- Rutele 31-32 (R): 4 Regio
('TR-329', 'Regio', 'Activ', 3, 0.90, 31), ('TR-330', 'Regio', 'Activ', 2, 0.85, 31), ('TR-331', 'Regio', 'Activ', 4, 0.95, 31), ('TR-332', 'Regio', 'Activ', 3, 0.90, 31),
('TR-333', 'Regio', 'Activ', 3, 0.90, 32), ('TR-334', 'Regio', 'Activ', 2, 0.85, 32), ('TR-335', 'Regio', 'Activ', 4, 0.95, 32), ('TR-336', 'Regio', 'Activ', 3, 0.90, 32),

-- Rutele 33-34 (IR): 2 InterCity, 2 InterRegio
('TR-337', 'InterCity', 'Activ', 6, 1.25, 33), ('TR-338', 'InterCity', 'Activ', 5, 1.20, 33), ('TR-339', 'InterRegio', 'Activ', 4, 1.05, 33), ('TR-340', 'InterRegio', 'Activ', 5, 1.10, 33),
('TR-341', 'InterCity', 'Activ', 5, 1.20, 34), ('TR-342', 'InterCity', 'Activ', 6, 1.25, 34), ('TR-343', 'InterRegio', 'Activ', 4, 1.05, 34), ('TR-344', 'InterRegio', 'Activ', 5, 1.10, 34),

-- Rutele 35-36 (R): 4 Regio
('TR-345', 'Regio', 'Activ', 3, 0.90, 35), ('TR-346', 'Regio', 'Activ', 2, 0.85, 35), ('TR-347', 'Regio', 'Activ', 4, 0.95, 35), ('TR-348', 'Regio', 'Activ', 3, 0.90, 35),
('TR-349', 'Regio', 'Activ', 3, 0.90, 36), ('TR-350', 'Regio', 'Activ', 2, 0.85, 36), ('TR-351', 'Regio', 'Activ', 4, 0.95, 36), ('TR-352', 'Regio', 'Activ', 3, 0.90, 36),

-- Rutele 37-38 (IR): 2 InterCity, 2 InterRegio
('TR-353', 'InterCity', 'Activ', 5, 1.20, 37), ('TR-354', 'InterCity', 'Activ', 6, 1.25, 37), ('TR-355', 'InterRegio', 'Activ', 4, 1.05, 37), ('TR-356', 'InterRegio', 'Activ', 5, 1.10, 37),
('TR-357', 'InterCity', 'Activ', 4, 1.15, 38), ('TR-358', 'InterCity', 'Activ', 5, 1.20, 38), ('TR-359', 'InterRegio', 'Activ', 4, 1.05, 38), ('TR-360', 'InterRegio', 'Activ', 5, 1.10, 38),

-- Rutele 39-42 (R): 4 Regio
('TR-361', 'Regio', 'Activ', 3, 0.90, 39), ('TR-362', 'Regio', 'Activ', 2, 0.85, 39), ('TR-363', 'Regio', 'Activ', 4, 0.95, 39), ('TR-364', 'Regio', 'Activ', 3, 0.90, 39),
('TR-365', 'Regio', 'Activ', 4, 0.95, 40), ('TR-366', 'Regio', 'Activ', 3, 0.90, 40), ('TR-367', 'Regio', 'Activ', 2, 0.85, 40), ('TR-368', 'Regio', 'Activ', 3, 0.90, 40),
('TR-369', 'Regio', 'Activ', 2, 0.85, 41), ('TR-370', 'Regio', 'Activ', 2, 0.85, 41), ('TR-371', 'Regio', 'Activ', 3, 0.90, 41), ('TR-372', 'Regio', 'Activ', 2, 0.85, 41),
('TR-373', 'Regio', 'Activ', 3, 0.90, 42), ('TR-374', 'Regio', 'Activ', 2, 0.85, 42), ('TR-375', 'Regio', 'Activ', 4, 0.95, 42), ('TR-376', 'Regio', 'Activ', 3, 0.90, 42),

-- Rutele 45-46 (IR): 2 InterCity, 2 InterRegio
('TR-377', 'InterCity', 'Activ', 6, 1.25, 45), ('TR-378', 'InterCity', 'Activ', 5, 1.20, 45), ('TR-379', 'InterRegio', 'Activ', 4, 1.05, 45), ('TR-380', 'InterRegio', 'Activ', 5, 1.10, 45),
('TR-381', 'InterCity', 'Activ', 4, 1.10, 46), ('TR-382', 'InterCity', 'Activ', 5, 1.15, 46), ('TR-383', 'InterRegio', 'Activ', 4, 1.05, 46), ('TR-384', 'InterRegio', 'Activ', 4, 1.00, 46),
-- Rutele 51-80 (Regio)
-- Rutele impare au 3 trenuri, rutele pare au 2 trenuri
('TR-501', 'Regio', 'Activ', 2, 0.80, 51), ('TR-502', 'Regio', 'Activ', 3, 0.85, 51), ('TR-503', 'Regio', 'Activ', 4, 0.90, 51),
('TR-504', 'Regio', 'Activ', 3, 0.85, 52), ('TR-505', 'Regio', 'Activ', 2, 0.80, 52),
('TR-506', 'Regio', 'Activ', 4, 0.90, 53), ('TR-507', 'Regio', 'Activ', 3, 0.85, 53), ('TR-508', 'Regio', 'Activ', 3, 0.85, 53),
('TR-509', 'Regio', 'Activ', 2, 0.85, 54), ('TR-510', 'Regio', 'Activ', 2, 0.80, 54),
('TR-511', 'Regio', 'Activ', 4, 0.90, 55), ('TR-512', 'Regio', 'Activ', 4, 0.90, 55), ('TR-513', 'Regio', 'Activ', 2, 0.80, 55),
('TR-514', 'Regio', 'Activ', 3, 0.85, 56), ('TR-515', 'Regio', 'Activ', 3, 0.85, 56),
('TR-516', 'Regio', 'Activ', 2, 0.80, 57), ('TR-517', 'Regio', 'Activ', 2, 0.80, 57), ('TR-518', 'Regio', 'Activ', 4, 0.90, 57),
('TR-519', 'Regio', 'Activ', 3, 0.85, 58), ('TR-520', 'Regio', 'Activ', 3, 0.85, 58),
('TR-521', 'Regio', 'Activ', 4, 0.90, 59), ('TR-522', 'Regio', 'Activ', 4, 0.90, 59), ('TR-523', 'Regio', 'Activ', 3, 0.85, 59),
('TR-524', 'Regio', 'Activ', 2, 0.80, 60), ('TR-525', 'Regio', 'Activ', 2, 0.80, 60),
('TR-526', 'Regio', 'Activ', 4, 0.90, 61), ('TR-527', 'Regio', 'Activ', 4, 0.90, 61), ('TR-528', 'Regio', 'Activ', 2, 0.80, 61),
('TR-529', 'Regio', 'Activ', 3, 0.85, 62), ('TR-530', 'Regio', 'Activ', 3, 0.85, 62),
('TR-531', 'Regio', 'Activ', 2, 0.80, 63), ('TR-532', 'Regio', 'Activ', 2, 0.80, 63), ('TR-533', 'Regio', 'Activ', 4, 0.90, 63),
('TR-534', 'Regio', 'Activ', 3, 0.85, 64), ('TR-535', 'Regio', 'Activ', 3, 0.85, 64),
('TR-536', 'Regio', 'Activ', 4, 0.90, 65), ('TR-537', 'Regio', 'Activ', 4, 0.90, 65), ('TR-538', 'Regio', 'Activ', 3, 0.85, 65),
('TR-539', 'Regio', 'Activ', 2, 0.80, 66), ('TR-540', 'Regio', 'Activ', 2, 0.80, 66),
('TR-541', 'Regio', 'Activ', 4, 0.90, 67), ('TR-542', 'Regio', 'Activ', 4, 0.90, 67), ('TR-543', 'Regio', 'Activ', 2, 0.80, 67),
('TR-544', 'Regio', 'Activ', 3, 0.85, 68), ('TR-545', 'Regio', 'Activ', 3, 0.85, 68),
('TR-546', 'Regio', 'Activ', 2, 0.80, 69), ('TR-547', 'Regio', 'Activ', 2, 0.80, 69), ('TR-548', 'Regio', 'Activ', 4, 0.90, 69),
('TR-549', 'Regio', 'Activ', 3, 0.85, 70), ('TR-550', 'Regio', 'Activ', 3, 0.85, 70),
('TR-551', 'Regio', 'Activ', 4, 0.90, 71), ('TR-552', 'Regio', 'Activ', 4, 0.90, 71), ('TR-553', 'Regio', 'Activ', 3, 0.85, 71),
('TR-554', 'Regio', 'Activ', 2, 0.80, 72), ('TR-555', 'Regio', 'Activ', 2, 0.80, 72),
('TR-556', 'Regio', 'Activ', 4, 0.90, 73), ('TR-557', 'Regio', 'Activ', 4, 0.90, 73), ('TR-558', 'Regio', 'Activ', 2, 0.80, 73),
('TR-559', 'Regio', 'Activ', 3, 0.85, 74), ('TR-560', 'Regio', 'Activ', 3, 0.85, 74),
('TR-561', 'Regio', 'Activ', 2, 0.80, 75), ('TR-562', 'Regio', 'Activ', 2, 0.80, 75), ('TR-563', 'Regio', 'Activ', 4, 0.90, 75),
('TR-564', 'Regio', 'Activ', 3, 0.85, 76), ('TR-565', 'Regio', 'Activ', 3, 0.85, 76),
('TR-566', 'Regio', 'Activ', 4, 0.90, 77), ('TR-567', 'Regio', 'Activ', 4, 0.90, 77), ('TR-568', 'Regio', 'Activ', 3, 0.85, 77),
('TR-569', 'Regio', 'Activ', 2, 0.80, 78), ('TR-570', 'Regio', 'Activ', 2, 0.80, 78),
('TR-571', 'Regio', 'Activ', 4, 0.90, 79), ('TR-572', 'Regio', 'Activ', 4, 0.90, 79), ('TR-573', 'Regio', 'Activ', 2, 0.80, 79),
('TR-574', 'Regio', 'Activ', 3, 0.85, 80), ('TR-575', 'Regio', 'Activ', 3, 0.85, 80),
-- Rutele 81-158 (Regio)
('TR-671', 'Regio', 'Activ', 2, 0.80, 81), ('TR-672', 'Regio', 'Activ', 3, 0.85, 81),
('TR-673', 'Regio', 'Activ', 4, 0.90, 82), ('TR-674', 'Regio', 'Activ', 2, 0.80, 82), ('TR-675', 'Regio', 'Activ', 3, 0.85, 82),
('TR-676', 'Regio', 'Activ', 2, 0.85, 83), ('TR-677', 'Regio', 'Activ', 4, 0.95, 83),
('TR-678', 'Regio', 'Activ', 2, 0.95, 84), ('TR-679', 'Regio', 'Activ', 3, 0.85, 84), ('TR-680', 'Regio', 'Activ', 2, 0.80, 84),
('TR-681', 'Regio', 'Activ', 4, 0.80, 85), ('TR-682', 'Regio', 'Activ', 3, 0.90, 85),
('TR-683', 'Regio', 'Activ', 3, 0.90, 86), ('TR-684', 'Regio', 'Activ', 2, 0.80, 86), ('TR-685', 'Regio', 'Activ', 4, 0.90, 86),
('TR-686', 'Regio', 'Activ', 2, 0.85, 87), ('TR-687', 'Regio', 'Activ', 3, 0.85, 87),
('TR-688', 'Regio', 'Activ', 4, 0.95, 88), ('TR-689', 'Regio', 'Activ', 2, 0.80, 88), ('TR-690', 'Regio', 'Activ', 3, 0.90, 88),
('TR-691', 'Regio', 'Activ', 3, 0.80, 89), ('TR-692', 'Regio', 'Activ', 2, 0.80, 89),
('TR-693', 'Regio', 'Activ', 2, 0.90, 90), ('TR-694', 'Regio', 'Activ', 3, 0.90, 90), ('TR-695', 'Regio', 'Activ', 4, 0.95, 90),
('TR-696', 'Regio', 'Activ', 4, 0.85, 91), ('TR-697', 'Regio', 'Activ', 2, 0.80, 91),
('TR-698', 'Regio', 'Activ', 3, 0.95, 92), ('TR-699', 'Regio', 'Activ', 4, 0.95, 92), ('TR-700', 'Regio', 'Activ', 2, 0.80, 92),
('TR-701', 'Regio', 'Activ', 2, 0.80, 93), ('TR-702', 'Regio', 'Activ', 3, 0.85, 93),
('TR-703', 'Regio', 'Activ', 4, 0.90, 94), ('TR-704', 'Regio', 'Activ', 2, 0.80, 94), ('TR-705', 'Regio', 'Activ', 3, 0.85, 94),
('TR-706', 'Regio', 'Activ', 3, 0.85, 95), ('TR-707', 'Regio', 'Activ', 2, 0.80, 95),
('TR-708', 'Regio', 'Activ', 2, 0.95, 96), ('TR-709', 'Regio', 'Activ', 3, 0.95, 96), ('TR-710', 'Regio', 'Activ', 4, 0.95, 96),
('TR-711', 'Regio', 'Activ', 4, 0.80, 97), ('TR-712', 'Regio', 'Activ', 2, 0.80, 97),
('TR-713', 'Regio', 'Activ', 3, 0.90, 98), ('TR-714', 'Regio', 'Activ', 4, 0.90, 98), ('TR-715', 'Regio', 'Activ', 2, 0.80, 98),
('TR-716', 'Regio', 'Activ', 2, 0.85, 99), ('TR-717', 'Regio', 'Activ', 3, 0.85, 99),
('TR-718', 'Regio', 'Activ', 4, 0.95, 100), ('TR-719', 'Regio', 'Activ', 2, 0.80, 100), ('TR-720', 'Regio', 'Activ', 3, 0.85, 100),
('TR-721', 'Regio', 'Activ', 3, 0.80, 101), ('TR-722', 'Regio', 'Activ', 2, 0.80, 101),
('TR-723', 'Regio', 'Activ', 2, 0.90, 102), ('TR-724', 'Regio', 'Activ', 3, 0.90, 102), ('TR-725', 'Regio', 'Activ', 4, 0.90, 102),
('TR-726', 'Regio', 'Activ', 4, 0.85, 103), ('TR-727', 'Regio', 'Activ', 2, 0.80, 103),
('TR-728', 'Regio', 'Activ', 3, 0.95, 104), ('TR-729', 'Regio', 'Activ', 4, 0.95, 104), ('TR-730', 'Regio', 'Activ', 2, 0.80, 104),
('TR-731', 'Regio', 'Activ', 2, 0.80, 105), ('TR-732', 'Regio', 'Activ', 3, 0.85, 105),
('TR-733', 'Regio', 'Activ', 4, 0.90, 106), ('TR-734', 'Regio', 'Activ', 2, 0.80, 106), ('TR-735', 'Regio', 'Activ', 3, 0.85, 106),
('TR-736', 'Regio', 'Activ', 3, 0.85, 107), ('TR-737', 'Regio', 'Activ', 2, 0.80, 107),
('TR-738', 'Regio', 'Activ', 2, 0.95, 108), ('TR-739', 'Regio', 'Activ', 3, 0.95, 108), ('TR-740', 'Regio', 'Activ', 4, 0.95, 108),
('TR-741', 'Regio', 'Activ', 4, 0.80, 109), ('TR-742', 'Regio', 'Activ', 2, 0.80, 109),
('TR-743', 'Regio', 'Activ', 3, 0.90, 110), ('TR-744', 'Regio', 'Activ', 4, 0.90, 110), ('TR-745', 'Regio', 'Activ', 2, 0.80, 110),
('TR-746', 'Regio', 'Activ', 2, 0.85, 111), ('TR-747', 'Regio', 'Activ', 3, 0.85, 111),
('TR-748', 'Regio', 'Activ', 4, 0.95, 112), ('TR-749', 'Regio', 'Activ', 2, 0.80, 112), ('TR-750', 'Regio', 'Activ', 3, 0.85, 112),
('TR-751', 'Regio', 'Activ', 3, 0.80, 113), ('TR-752', 'Regio', 'Activ', 2, 0.80, 113),
('TR-753', 'Regio', 'Activ', 2, 0.90, 114), ('TR-754', 'Regio', 'Activ', 3, 0.90, 114), ('TR-755', 'Regio', 'Activ', 4, 0.90, 114),
('TR-756', 'Regio', 'Activ', 4, 0.85, 115), ('TR-757', 'Regio', 'Activ', 2, 0.80, 115),
('TR-758', 'Regio', 'Activ', 3, 0.95, 116), ('TR-759', 'Regio', 'Activ', 4, 0.95, 116), ('TR-760', 'Regio', 'Activ', 2, 0.80, 116),
('TR-761', 'Regio', 'Activ', 2, 0.80, 117), ('TR-762', 'Regio', 'Activ', 3, 0.85, 117),
('TR-763', 'Regio', 'Activ', 4, 0.90, 118), ('TR-764', 'Regio', 'Activ', 2, 0.80, 118), ('TR-765', 'Regio', 'Activ', 3, 0.85, 118),
('TR-766', 'Regio', 'Activ', 3, 0.85, 121), ('TR-767', 'Regio', 'Activ', 2, 0.80, 121),
('TR-768', 'Regio', 'Activ', 2, 0.95, 122), ('TR-769', 'Regio', 'Activ', 3, 0.95, 122), ('TR-770', 'Regio', 'Activ', 4, 0.95, 122),
('TR-771', 'Regio', 'Activ', 4, 0.80, 125), ('TR-772', 'Regio', 'Activ', 2, 0.80, 125),
('TR-773', 'Regio', 'Activ', 3, 0.90, 126), ('TR-774', 'Regio', 'Activ', 4, 0.90, 126), ('TR-775', 'Regio', 'Activ', 2, 0.80, 126),
('TR-776', 'Regio', 'Activ', 2, 0.85, 127), ('TR-777', 'Regio', 'Activ', 3, 0.85, 127),
('TR-778', 'Regio', 'Activ', 4, 0.95, 128), ('TR-779', 'Regio', 'Activ', 2, 0.80, 128), ('TR-780', 'Regio', 'Activ', 3, 0.85, 128),
('TR-781', 'Regio', 'Activ', 3, 0.80, 129), ('TR-782', 'Regio', 'Activ', 2, 0.80, 129),
('TR-783', 'Regio', 'Activ', 2, 0.90, 130), ('TR-784', 'Regio', 'Activ', 3, 0.90, 130), ('TR-785', 'Regio', 'Activ', 4, 0.90, 130),
('TR-786', 'Regio', 'Activ', 4, 0.85, 132), ('TR-787', 'Regio', 'Activ', 2, 0.80, 132),
('TR-788', 'Regio', 'Activ', 3, 0.95, 133), ('TR-789', 'Regio', 'Activ', 4, 0.95, 133), ('TR-790', 'Regio', 'Activ', 2, 0.80, 133),
('TR-791', 'Regio', 'Activ', 2, 0.80, 135), ('TR-792', 'Regio', 'Activ', 3, 0.85, 135),
('TR-793', 'Regio', 'Activ', 4, 0.90, 136), ('TR-794', 'Regio', 'Activ', 2, 0.80, 136), ('TR-795', 'Regio', 'Activ', 3, 0.85, 136),
('TR-796', 'Regio', 'Activ', 3, 0.85, 137), ('TR-797', 'Regio', 'Activ', 2, 0.80, 137),
('TR-798', 'Regio', 'Activ', 2, 0.95, 138), ('TR-799', 'Regio', 'Activ', 3, 0.95, 138), ('TR-800', 'Regio', 'Activ', 4, 0.95, 138),
('TR-801', 'Regio', 'Activ', 4, 0.80, 139), ('TR-802', 'Regio', 'Activ', 2, 0.80, 139),
('TR-803', 'Regio', 'Activ', 3, 0.90, 140), ('TR-804', 'Regio', 'Activ', 4, 0.90, 140), ('TR-805', 'Regio', 'Activ', 2, 0.80, 140),
('TR-806', 'Regio', 'Activ', 2, 0.85, 141), ('TR-807', 'Regio', 'Activ', 3, 0.85, 141),
('TR-808', 'Regio', 'Activ', 4, 0.95, 142), ('TR-809', 'Regio', 'Activ', 2, 0.80, 142), ('TR-810', 'Regio', 'Activ', 3, 0.85, 142),
('TR-811', 'Regio', 'Activ', 3, 0.80, 143), ('TR-812', 'Regio', 'Activ', 2, 0.80, 143),
('TR-813', 'Regio', 'Activ', 2, 0.90, 144), ('TR-814', 'Regio', 'Activ', 3, 0.90, 144), ('TR-815', 'Regio', 'Activ', 4, 0.90, 144),
('TR-816', 'Regio', 'Activ', 4, 0.85, 145), ('TR-817', 'Regio', 'Activ', 2, 0.80, 145),
('TR-818', 'Regio', 'Activ', 3, 0.95, 146), ('TR-819', 'Regio', 'Activ', 4, 0.95, 146), ('TR-820', 'Regio', 'Activ', 2, 0.80, 146),
('TR-821', 'Regio', 'Activ', 2, 0.80, 147), ('TR-822', 'Regio', 'Activ', 3, 0.85, 147),
('TR-823', 'Regio', 'Activ', 4, 0.90, 148), ('TR-824', 'Regio', 'Activ', 2, 0.80, 148), ('TR-825', 'Regio', 'Activ', 3, 0.85, 148),
('TR-826', 'Regio', 'Activ', 3, 0.85, 149), ('TR-827', 'Regio', 'Activ', 2, 0.80, 149),
('TR-828', 'Regio', 'Activ', 2, 0.95, 150), ('TR-829', 'Regio', 'Activ', 3, 0.95, 150), ('TR-830', 'Regio', 'Activ', 4, 0.95, 150),
('TR-831', 'Regio', 'Activ', 4, 0.80, 151), ('TR-832', 'Regio', 'Activ', 2, 0.80, 151),
('TR-833', 'Regio', 'Activ', 3, 0.90, 152), ('TR-834', 'Regio', 'Activ', 4, 0.90, 152), ('TR-835', 'Regio', 'Activ', 2, 0.80, 152),
('TR-836', 'Regio', 'Activ', 4, 0.95, 154), ('TR-837', 'Regio', 'Activ', 2, 0.80, 154),
('TR-838', 'Regio', 'Activ', 3, 0.80, 155), ('TR-839', 'Regio', 'Activ', 4, 0.80, 155), ('TR-840', 'Regio', 'Activ', 2, 0.80, 155),
('TR-841', 'Regio', 'Activ', 2, 0.90, 156), ('TR-842', 'Regio', 'Activ', 3, 0.90, 156),
('TR-843', 'Regio', 'Activ', 4, 0.85, 157), ('TR-844', 'Regio', 'Activ', 2, 0.80, 157),
('TR-845', 'Regio', 'Activ', 3, 0.95, 158), ('TR-846', 'Regio', 'Activ', 2, 0.80, 158);

SELECT train_id,train_number,train_type,train_status,number_of_wagons,price_multiplier,route_id
FROM Train