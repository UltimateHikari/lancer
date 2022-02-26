--scrapped plural forms in favour of simplicity
DROP TABLE IF EXISTS corporation;
DROP TABLE IF EXISTS commodity_type;
DROP TABLE IF EXISTS commodity;

DROP TABLE IF EXISTS frame_class;
DROP TABLE IF EXISTS frame;

DROP TABLE IF EXISTS element;
--DROP TABLE IF EXISTS module_type;
DROP TABLE IF EXISTS frame_module;

DROP TABLE IF EXISTS frame_preset;


--planetary system->node
--event->encounter
DROP TABLE IF EXISTS node;
DROP TABLE IF EXISTS lane;

DROP TABLE IF EXISTS encounter;
DROP TABLE IF EXISTS modificator;

DROP TABLE IF EXISTS bots;

CREATE TABLE corporation(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE commodity_type(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE commodity(
    id integer PRIMARY KEY NOT NULL,
    type_id integer REFERENCES commodity_type(id) NOT NULL,
    manufacturer_id integer REFERENCES corporation(id) NOT NULL,
    name text NOT NULL
);

--TODO: speed/energy/slots modifiers for creation
CREATE TABLE frame_class(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
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
