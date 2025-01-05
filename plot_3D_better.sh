reset

set terminal pngcairo
set output '3D_velocity_x_part.png'

set xlabel "X"
set ylabel "Y"
set zlabel "Z"

set title ""

# Set view angle for 3D plot
#set view 60, 30

# Plot using the first three columns as the coordinates and scaling the velocity components
sp "velocity_3D.dat" eve 4:4 u 1:2:3:4 with points pt 7 ps 0.5 palette title ""


set output '3D_velocity_y_part.png'

sp "velocity_3D.dat" eve 4:4 u 1:2:3:5 with points pt 7 ps 0.5 palette title ""

set output '3D_velocity_z_part.png'

sp "velocity_3D.dat" eve 4:4 u 1:2:3:6 with points pt 7 ps 0.5 palette title ""


set output '3D_velocity.png'

sp "velocity_3D.dat" eve 4:4 u 1:2:3:4:5:6 with vectors palette title ""
