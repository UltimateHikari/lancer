#!/bin/bash

DB=lancer.db

rm build/src/$DB
rm build/tests/$DB
cp db/$DB build/src/
cp db/$DB build/tests/
