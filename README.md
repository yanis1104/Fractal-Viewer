# Fractal-Viewer

Yanis GOUGEAT

January 2023

Description:
This software generates many kinds of fractals such as the Julia set and the Mandelbrot set.

Features:
- Zoom on the image: Using the mouse wheel, it is possible to zoom-in and zoom-out on the position of the cursor.
- Switch between Julia set and Mandelbrot set
- Modify the constant values for the Julia set, showing different fractals
- Modify the step value to increase or decrease the constant values with more precision
- Hide the panels by pressing the 'H' key. Press again 'H' to show the panels.

Fractal Viewer GUI
![Fractal GUI](/examples/fractal_gui.png?raw=true "Graphic User Interface")

Examples
![Mandelbrot set](/examples/mandelbrot.png?raw=true "Mandelbrot set")
Z² + c

<br/>
<br/>

![Julia set](/examples/-0.55%2B0.71i.png?raw=true "Julia set")
Z² - 0.55 + 0.71i

<br/>
<br/>

![Julia set](/examples/-1.27%2B0i.png?raw=true "Julia set")
Z² - 1.27 + 0i

<br/>
<br/>

![Julia set](/examples/-1.73%2B0i.png?raw=true "Julia set")
Z² - 1.73 + 0i

<br/>
<br/>

![Julia set](/examples/0.3%2B0.5i.png?raw=true "Julia set")
Z² + 0.3 + 0.51i

<br/>
<br/>

![Julia set](/examples/0.285%2B0.1i.png?raw=true "Julia set")
Z² + 0.285 + 0.1i

<br/>
<br/>

Prerequisites:
- The graphic library used is SFML. You have to install it before running the program.
  https://www.sfml-dev.org/download.php
- You need a NVIDIA graphic card to use it, with the CUDA toolkit intsalled on your computer.
  https://developer.nvidia.com/cuda-downloads


How to run the program:
- On Visual Studio, create a new CUDA project
- Add the SFML library to the project
- Generate the solution
- Execute the program
