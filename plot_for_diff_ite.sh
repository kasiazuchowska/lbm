reset

set terminal pngcairo
set output 'rysunek_10_ite.png'
plot 'velocity_10_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

reset

set terminal pngcairo
set output 'rysunek_50_ite.png'
plot 'velocity_50_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

reset

set terminal pngcairo
set output 'rysunek_100_ite.png'
plot 'velocity_100_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

reset

set terminal pngcairo
set output 'rysunek_500_ite.png'
plot 'velocity_500_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

reset

set terminal pngcairo
set output 'rysunek_1000_ite.png'
plot 'velocity_1000_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

reset

set terminal pngcairo
set output 'rysunek_2000_ite.png'
plot 'velocity_2000_ite.dat' u 1:2:($3*1000):($4*1000) with vectors nohead

