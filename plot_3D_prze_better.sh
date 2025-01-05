reset

set terminal pngcairo


set xlabel "X"
set ylabel "Y"


set title ""

# Set view angle for 3D plot
#set view 60, 30
set xlabel "X"
set ylabel "Z"
set output '3D_velocity_xz_prze.png'
p "velocity_3D.dat" eve :::30::30 u 1:3:4 pt 7 palette title ""


set xlabel "X"
set ylabel "Y"
set output '3D_velocity_xy_prze.png'
p "velocity_3D.dat" eve ::30::30 u 1:2:4 pt 7 palette title ""

set output '3D_velocity_yz_prze.png'
p "velocity_3D.dat" eve 30::30 u 2:3:4 pt 7 palette title ""
