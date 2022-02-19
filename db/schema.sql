--scrapped plural forms in favour of simplicity
DROP TABLE IF EXISTS corporation;
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
