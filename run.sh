#!/usr/bin/env bash
mkdir build/data
cp src/data/conf build/data/
cp src/caja.mem build/
cp src/no-cobrado.mem build/
cd build/
./restorrente
