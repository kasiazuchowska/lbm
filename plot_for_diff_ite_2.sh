reset

set terminal pngcairo
set output 'rysunek_test.png'
set size ratio -1

splot "velocity_ite.dat" i 50 u 1:2:3 w pm