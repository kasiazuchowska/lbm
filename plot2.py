import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

# Function to read the velocity data from the file
def read_velocity_data(file_name):
    iterations = []
    with open(file_name, 'r') as file:
        U, V = [], []
        for line in file:
            if "Iteration" in line:  # New iteration
                if U and V:
                    iterations.append((np.array(U), np.array(V)))
                    U, V = [], []
            elif line.strip():  # If it's not a blank line
                _, _, u_val, v_val = line.split()
                U.append(float(u_val))
                V.append(float(v_val))
        if U and V:
            iterations.append((np.array(U).reshape(Lx, Ly), np.array(V).reshape(Lx, Ly)))  # Last iteration
    return iterations

# Grid dimensions (you'll need to know Lx and Ly)
Lx, Ly = 100, 50  # Adjust to match your grid size

# Read velocity data
velocities_data = read_velocity_data('build/velocity_ite.dat')

# Set up the figure and axis
fig, ax = plt.subplots()
x, y = np.meshgrid(np.arange(Lx), np.arange(Ly))

# Scale factor for velocities (adjust to make the arrows smaller)
scale_factor = 1

# Initial quiver plot with scaled arrows
quiver = ax.quiver(x, y, velocities_data[0][0], velocities_data[0][1])
# quiver = ax.quiver(x, y, velocities_data[0][0], velocities_data[0][1], scale=scale_factor, scale_units='xy')


# Function to update the plot for each frame
def update(frame):
    U, V = velocities_data[frame]
    # Replace zero velocities with a small value or mask them
    # U = np.where((U == 0) & (V == 0), np.nan, U)  # Mask points where both U and V are zero
    # V = np.where((U == 0) & (V == 0), np.nan, V)
    quiver.set_UVC(U, V)
    ax.set_title(f"Iteration {frame}")

# Create the animation
anim = FuncAnimation(fig, update, frames=len(velocities_data), interval=200)

# Show the animation
anim.save('velocity_animation.gif', writer='imagemagick', fps=10)


# Optionally, save the animation as a video or GIF
# anim.save('velocity_animation.mp4', writer='ffmpeg', fps=10)
