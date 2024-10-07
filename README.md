# Mathemagic
Exploring mathematical patterns with computer viz.

## Chapter 1: Mandelbrot Set
A simple rendering of the [mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) using C++ SFML library. [code](/mandelbrot_sfml/mandelbrot.cpp)  
### High level implementation details:
- unoptimized naive escape time algorithm src: [wiki](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Escape_time_algorithm)
- coloring done through logarithmic gradients
- execution: `g++ -o mandelbrot mandelbrot.cpp -lsfml-graphics -lsfml-window -lsfml-system`  

### Requirements:
- SFML lib.
- Ubuntu / Debian: `sudo apt-get install libsfml-dev`
![mandelbrot](/mandelbrot_sfml/mandelbrot_viz.png)

## Chapter 2: Julia Set
A simple rendering of the [julia set](https://en.wikipedia.org/wiki/Julia_set) using C++ SFML library. [code](/julia_sfml/julia.cpp)  
### High level implementation details:
- uses a escape radius algorithm
- coloring done through logarithmic gradients
- execution: `g++ -o julia julia.cpp -lsfml-graphics -lsfml-window -lsfml-system`  

### Requirements:
- SFML lib.
- Ubuntu / Debian: `sudo apt-get install libsfml-dev`
![julia](/julia_sfml/julia.png)
