--scrapped plural forms in favour of simplicity
DROP TABLE IF EXISTS corporation;
DROP TABLE IF EXISTS frame_class;
DROP TABLE IF EXISTS frame;

CREATE TABLE corporation(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE frame_class(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL,
    slots integer NOT NULL
);

CREATE TABLE frame(
    id integer PRIMARY KEY NOT NULL,
    class_id integer REFERENCES frame_class(id) NOT NULL,
    manufacturer_id integer REFERENCES corporation(id) NOT NULL,
    name text NOT NULL,

    weap_slots integer NOT NULL,
    armr_slots integer NOT NULL,
    supp_slots integer NOT NULL,

    energy integer NOT NULL,
    inventory_size integer NOT NULL,

    structure_points integer NOT NULL,
    speed integer NOT NULL,
    evasion integer NOT NULL
);
