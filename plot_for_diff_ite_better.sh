reset

# Function to create a plot for each dataset
do for [i in "10 50 100 500 1000 2000"] {
    # Set the terminal and output file
    set terminal pngcairo enhanced font "Arial,10" size 800,600
    set output sprintf('rysunek_%s_ite.png', i)
    
    # Set the title and axis labels
    set title sprintf("Prędkości po %s iteracji", i) font ",14"
    set xlabel "X" font ",12"
    set ylabel "Y" font ",12"
    
    # Set grid for better readability
    set grid
    
    # Plot data with vectors and add a legend
    plot sprintf('velocity_%s_ite.dat', i) u 1:2:($3*1000):($4*1000) with vectors nohead title ""
    
    # Reset settings for the next plot
    unset title
    unset xlabel
    unset ylabel
    unset grid
}
