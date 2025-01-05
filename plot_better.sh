reset

# Set the terminal and output file
set terminal pngcairo enhanced font "Arial,10" size 800,600
set output 'rysunek.png'

# Set the title and axis labels
set title "Prędkości po 1000 iteracji" font ",14"
set xlabel "X" font ",12"
set ylabel "Y" font ",12"

# Set grid for better readability
set grid

# Plot data with vectors and add a legend
plot 'velocity.dat' u 1:2:($3*1000):($4*1000) with vectors nohead title ""