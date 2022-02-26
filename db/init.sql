INSERT INTO corporation(name) VALUES ("Giperion");

INSERT INTO commodity_type(name) VALUES ("essential");
INSERT INTO commodity_type(name) VALUES ("illegal");
INSERT INTO commodity_type(name) VALUES ("industrial");
INSERT INTO commodity_type(name) VALUES ("commodity");
INSERT INTO commodity_type(name) VALUES ("ore");

INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (1, 1, "Medical supplies");
INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (2, 1, "Organs");
INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (4, 1, "Luxury");

INSERT INTO frame_class(name) VALUES ("interceptor");
INSERT INTO frame_class(name) VALUES ("fighter");
INSERT INTO frame_class(name) VALUES ("trader");
INSERT INTO frame_class(name) VALUES ("aviso");
INSERT INTO frame_class(name) VALUES ("corvette");
INSERT INTO frame_class(name) VALUES ("destroyer");

INSERT INTO frame(
    class_id, manufacturer_id, 
    name,
    weap_slots, armr_slots, supp_slots,
    energy, inventory_size,
    structure_points, speed, evasion)
VALUES(
    5,1,
    "Dark Angel",
    4,6,6,
    200,40,
    600,100,10
)