from PIL import Image

# Load the GIF
gif_path = "anim2.gif"  # Replace with your GIF path
frame_number = 10  # Replace with the frame you want to extract
output_png = "output_frame.png"  # Name of the output PNG file

frames = [0, 50, 100, 110, 120, 150, 200, 248]

# Open the GIF
gif = Image.open(gif_path)

for frame in frames:
    output_png = "output_frame_" + str(frame) + ".png"
    # Seek to the specific frame
    try:
        gif.seek(frame)  # Frame numbers start at 0
        gif.save(output_png, "PNG")
        print(f"Frame {frame_number} saved as {output_png}")
    except EOFError:
        print("The specified frame number is out of range.")
    




