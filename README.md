# Mathemagic
Exploring mathematical patterns with computer viz.

## Chapter 1: Mandelbrot Set
A simple rendering of the mandelbrot set using C++ SFML library. [code](/mandelbrot_sfml/mandelbrot.cpp)  
### High level implementation details:
- unoptimized naive escape time algorithm src: [wiki](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Escape_time_algorithm)
- coloring done through logarithmic gradients
![mandelbrot](/mandelbrot_sfml/mandelbrot_viz.png)
