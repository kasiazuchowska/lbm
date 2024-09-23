#!/bin/bash

cd build

cmake ..

make

echo "running"

./lbm

gnuplot ../plot.sh

mv rysunek.png ../results/rysunek.png



