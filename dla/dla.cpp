#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const int GRID_SIZE = 100;   // Grid size for the simulation
const int WINDOW_SIZE = 1000; // Window size for visualization
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;  // Size of each cell

int lattice[GRID_SIZE][GRID_SIZE] = {0};    // Grid for cluster
int age[GRID_SIZE][GRID_SIZE] = {0};        // Age of the cluster cells

// Function to release a walker on the boundary
pair<int, int> release_walker()
{
    pair<int, int> coord;
    int boundary = rand() % 2;  // 0 for horizontal, 1 for vertical

    if (boundary == 0)
    {
        coord.first = (rand() % 2) * (GRID_SIZE - 1);  
        coord.second = rand() % GRID_SIZE;  
    }
    else  
    {
        coord.first = rand() % GRID_SIZE;  
        coord.second = (rand() % 2) * (GRID_SIZE - 1); 
    }

    return coord;
}

// Function to move the walker randomly
pair<int, int> walk(pair<int, int> walker)
{
    int chance = rand() % 4;

    switch (chance)
    {
        case 0: walker.first = (walker.first - 1 + GRID_SIZE) % GRID_SIZE; break;  // Up
        case 1: walker.first = (walker.first + 1) % GRID_SIZE; break;              // Down
        case 2: walker.second = (walker.second - 1 + GRID_SIZE) % GRID_SIZE; break; // Left
        case 3: walker.second = (walker.second + 1) % GRID_SIZE; break;            // Right
    }

    return walker;
}

// Check if a walker is adjacent to the cluster
int cluster_check(int neighbours[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (neighbours[i] == 1)
            return 1;  
    }
    return 0;
}

// Function to turn walker into part of the cluster if adjacent
pair<int, int> clusterize(pair<int, int> walker)
{
    int i = walker.first;
    int j = walker.second;

    int neighbours[4] = 
    {
        lattice[(i - 1 + GRID_SIZE) % GRID_SIZE][(j + GRID_SIZE) % GRID_SIZE],  // Up
        lattice[(i + 1 + GRID_SIZE) % GRID_SIZE][(j + GRID_SIZE) % GRID_SIZE],  // Down
        lattice[(i + GRID_SIZE) % GRID_SIZE][(j - 1 + GRID_SIZE) % GRID_SIZE],  // Left
        lattice[(i + GRID_SIZE) % GRID_SIZE][(j + 1 + GRID_SIZE) % GRID_SIZE]   // Right
    };

    if (cluster_check(neighbours)) 
    {
        lattice[i][j] = 1; 
        age[i][j]++;       
        return release_walker();  
    }
    return walker;
}

// Function to draw the lattice and walkers
void draw_lattice(sf::RenderWindow &window, int lattice[GRID_SIZE][GRID_SIZE], int age[GRID_SIZE][GRID_SIZE], pair<int, int> walkers[], int num_walkers)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);

            
            if (lattice[i][j] == 1)
            {
                cell.setFillColor(sf::Color(57, 255, 20)); 
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color(255, 0, 0));  
            }
            else
            {
                cell.setFillColor(sf::Color::Black);  
            }
            window.draw(cell);
        }
    }

    // Draw faded walkers
    for (int i = 0; i < num_walkers; i++)
    {
        sf::RectangleShape walker(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
        walker.setPosition(walkers[i].first * CELL_SIZE, walkers[i].second * CELL_SIZE);
        walker.setFillColor(sf::Color(100, 100, 100, 150)); 
        window.draw(walker);
    }
}

int main()
{
    srand(time(0));  
    lattice[GRID_SIZE / 2][GRID_SIZE / 2] = 1;  

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Diffusion-Limited Aggregation with Glow Effect");
    window.setFramerateLimit(60);  

     // Load font for text
    sf::Font font;
    if (!font.loadFromFile("FiraCode-Retina.ttf"))  
    {
        cout << "Failed to load font!" << endl;
        return -1;
    }

    // Create text to display the number of walkers
    sf::Text text;
    text.setFont(font);
    text.setString("Walkers: 2000");
    text.setCharacterSize(24);  
    text.setFillColor(sf::Color::White);  
    text.setPosition(25, 25); 

    vector<pair<int, int>> walkers(2000);  // 2000 walkers
    for (int i = 0; i < 2000; i++) walkers[i] = release_walker();  // Initialize walkers

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < walkers.size(); i++)
        {
            walkers[i] = walk(walkers[i]);
            walkers[i] = clusterize(walkers[i]);
        }

        window.clear(sf::Color::Black);  

        draw_lattice(window, lattice, age, &walkers[0], walkers.size());

        window.draw(text);

        window.display(); 
    }

    return 0;
}
