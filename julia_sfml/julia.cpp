# include <cmath>
# include <complex>
# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Color.hpp>
# include <iostream>

const int WIDTH = 1080;
const int HEIGHT = 1080;
const int MAX_ITERATIONS = 500;
const std::complex<float> c (-0.7269, 0.1889);

int escape_radius(std::complex<float> c)
{
    int r = 1;
    while (r*r - r <= std::abs(c))
    {
        r += 1;
    } 
    std::cout << r;
    return r;
}


sf::Color getColor(int iteration, int max_iterations)
{
    if (iteration == max_iterations) 
        return sf::Color::Black;  
    float t = static_cast<float>(iteration) / max_iterations;
    t = sqrt(t); 

    sf::Uint8 r = static_cast<sf::Uint8>(9 * (1 - t) * t * t * t * 255);
    sf::Uint8 g = static_cast<sf::Uint8>(15 * (1 - t) * (1 - t) * t * t * 255);
    sf::Uint8 b = static_cast<sf::Uint8>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return sf::Color(r, g, b);
}

std::complex<float> setToComplex(int x, int y, int escape_radius)
{
    float x_real = ((float) x / WIDTH) * (2*escape_radius) - escape_radius;
    float y_imag = ((float) y / HEIGHT) * (2*escape_radius) - escape_radius;  
    return std::complex<float>(x_real, y_imag);
}

int iterate(std::complex<float> z, int escape_radius)
{
    int iterations = 0;
    while (std::abs(z) <= escape_radius * escape_radius && iterations < MAX_ITERATIONS)
    {
        z = z*z + c;
        iterations++;
    }
    return iterations;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Julia Set");
    sf::Image image;
    image.create(WIDTH, HEIGHT);
    int esc_rad = escape_radius(c);

    for (int i=0; i<WIDTH; i++) 
    {
        for (int j=0; j<HEIGHT; j++)
        {
            std::complex<float> z = setToComplex(i, j, esc_rad);
            
            int iterations = iterate(z, esc_rad);
            sf::Color color = getColor(iterations, MAX_ITERATIONS);
      
            if (iterations == MAX_ITERATIONS)
            {
                image.setPixel(i, j, sf::Color::Black);
            }
            else
            {
                image.setPixel(i, j, color);
            }
        }
    }

    // Load the image into a texture
    sf::Texture texture;
    texture.loadFromImage(image);

    // Create a sprite to display the texture
    sf::Sprite sprite(texture);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window and draw the Mandelbrot set sprite
        window.clear();
        window.draw(sprite);
        window.display();
    }
}