reset

set terminal pngcairo
set output 'rysunek.png'

plot 'velocity.dat' u 1:2:($3*1000):($4*1000) with vectors nohead