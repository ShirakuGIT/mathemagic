#include <iostream>
#include <unistd.h>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

const int WINDOW_SIZE = 1000;
const int GRID_SIZE = 50;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

int board[50][50];

// Function to draw the grid using SFML
void drawGrid(sf::RenderWindow &window, int board[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            if (board[i][j] == 1)
            {
                cell.setFillColor(sf::Color::White);
            }
            else
            {
                cell.setFillColor(sf::Color::Black);
            }
            window.draw(cell);
        }
    }
}

// Function to draw a single cell using SFML
void drawCell(sf::RenderWindow &window, int i, int j, int state)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
    
    if (state == 1)
    {
        cell.setFillColor(sf::Color::White); // Alive cell
    }
    else
    {
        cell.setFillColor(sf::Color::Black); // Dead cell
    }
    
    window.draw(cell); // Draw the individual cell
}


// Conway's rules
int conway_rules(int cell, int neighbours[8])
{
    int live_cells = 0;
    for (int i = 0; i < 8; i++)
    {
        live_cells += neighbours[i];
    }

    if (live_cells < 2 || live_cells > 3)
    {
        return 0; // Cell dies
    }
    else if (cell == 0 && live_cells == 3)
    {
        return 1; // Cell becomes alive
    }

    return cell; // Cell remains the same
}

// Apply the generation changes to the board
void generate(vector<pair<int, int>>& generation)
{
    for (auto coord : generation)
    {
        int i = coord.first;
        int j = coord.second;
        board[i][j] = !board[i][j]; // Toggle the state of the cell
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Conway's Game of Life");
    sf::Clock clock;
    window.setFramerateLimit(30);  // Set the frame limit to 60 FPS
    // Gosper Glider Gun initial seed
    vector<pair<int, int>> glider_gun = {
        {5, 1}, {5, 2}, {6, 1}, {6, 2},
        {5, 11}, {6, 11}, {7, 11},
        {4, 12}, {8, 12},
        {3, 13}, {9, 13},
        {3, 14}, {9, 14},
        {6, 15},
        {4, 16}, {8, 16},
        {5, 17}, {6, 17}, {7, 17},
        {6, 18},
        {3, 21}, {4, 21}, {5, 21},
        {3, 22}, {4, 22}, {5, 22},
        {2, 23}, {6, 23},
        {1, 25}, {2, 25}, {6, 25}, {7, 25},
        {3, 35}, {4, 35}, 
        {3, 36}, {4, 36}
    };

    // Set the Gosper Glider Gun pattern on the board
    for (auto coord : glider_gun)
    {
        board[coord.first][coord.second] = 1;
    }
    sleep(20);
    // Game loop
    while (window.isOpen())
    {   
        // Framerate limit
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 100) // 100 ms delay
        {
            clock.restart(); // Restart the clock for the next frame
            
            // Game logic
            // Handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            vector<pair<int, int>> generation;

            // Iterate over the grid
            for (int i = 0; i < GRID_SIZE; i++)
            {
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    int cell = board[i][j];
                    
                    // Calculate neighbors
                    int neighbours[8] = 
                    {
                        board[(i-1+GRID_SIZE)%GRID_SIZE][(j-1+GRID_SIZE)%GRID_SIZE], board[(i-1+GRID_SIZE)%GRID_SIZE][(j+GRID_SIZE)%GRID_SIZE], board[(i-1+GRID_SIZE)%GRID_SIZE][(j+1+GRID_SIZE)%GRID_SIZE],
                        board[(i+GRID_SIZE)%GRID_SIZE][(j-1+GRID_SIZE)%GRID_SIZE],                               board[(i+GRID_SIZE)%GRID_SIZE][(j+1+GRID_SIZE)%GRID_SIZE],
                        board[(i+1+GRID_SIZE)%GRID_SIZE][(j-1+GRID_SIZE)%GRID_SIZE], board[(i+1+GRID_SIZE)%GRID_SIZE][(j+GRID_SIZE)%GRID_SIZE], board[(i+1+GRID_SIZE)%GRID_SIZE][(j+1+GRID_SIZE)%GRID_SIZE]
                    };

                    // Apply Conway's rules
                    int cell_gen = conway_rules(cell, neighbours);
                    if (cell_gen != cell)
                    {
                        generation.push_back(make_pair(i, j));
                    }
                }
            }

            // Apply the changes
            generate(generation);

            
            
            // Don't clear the entire window; just update the changed cells.
            for (auto& coord : generation)
            {
                int i = coord.first;
                int j = coord.second;

                // Draw only the cells that have changed state
                drawCell(window, i, j, board[i][j]);
            }
            // Clear the vector after applying the changes for the next generation
            generation.clear();

            // No need to clear the entire screen, just call display to show the updated cells.
            window.display();
        }
    }
    return 0;
}
