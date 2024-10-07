# include <SFML/Graphics.hpp>
# include <complex>
# include <cmath>

const int WIDTH = 1080;
const int HEIGHT = 1080;
const int MAX_ITERATIONS = 100;


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


std::complex<float> screenToComplexPlane(float x, float y)
{
    float x_real = ((float) x / WIDTH) * 2.47f - 2.0f;
    float y_imag = ((float) y / HEIGHT) * 2.24f - 1.12f;  
    return std::complex<float>(x_real, y_imag);
}

int iterations(std::complex<float> C)
{
    std::complex<float> z(0, 0);
    int iteration = 0;
    while (std::abs(z) <= 2.0f && iteration < MAX_ITERATIONS)
    {
        z = z * z + C;
        iteration += 1;
    }

    return iteration;

}
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Set");
    sf::Image image;
    image.create(WIDTH, HEIGHT);
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            std::complex<float> complex_coord = screenToComplexPlane(x, y);
            int iter = iterations(complex_coord); 
            sf::Color color = getColor(iter, MAX_ITERATIONS);
            image.setPixel(x, y, color);
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