--scrapped plural forms in favour of simplicity
DROP TABLE IF EXISTS manufacturer;
DROP TABLE IF EXISTS commodity_type;
DROP TABLE IF EXISTS commodity;

DROP TABLE IF EXISTS frame_type;
DROP TABLE IF EXISTS frame;
DROP TABLE IF EXISTS frame_type;

DROP TABLE IF EXISTS element;
--DROP TABLE IF EXISTS module_type;
DROP TABLE IF EXISTS frame_module;

--planetary system->node
--event->encounter
DROP TABLE IF EXISTS node;
DROP TABLE IF EXISTS lane;

DROP TABLE IF EXISTS encounter;
DROP TABLE IF EXISTS modificator;

DROP TABLE IF EXISTS bots;

CREATE TABLE manufacturer(
    id integer PRIMARY KEY,
    name text
);

CREATE TABLE commodity_type(
    id integer PRIMARY KEY,
    name text
);

CREATE TABLE commodity(
    id integer PRIMARY KEY,
    type_id integer REFERENCES(commodity_type.id),
    manufacturer_id integer REFERENCES(manufacturer.id),
    name text
);