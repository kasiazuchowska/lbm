reset

set terminal pngcairo
set output '3D_velocity.png'

set xlabel "X-axis"
set ylabel "Y-axis"
set zlabel "Z-axis"
set title "3D Velocity"

# Set view angle for 3D plot
set view 60, 30

# Plot using the first three columns as the coordinates and scaling the velocity components
splot 'velocity_3D.dat' using 1:2:3:($4*1000):($5*1000):($6*1000) with vectors
