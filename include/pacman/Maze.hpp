#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Maze {   
public:
    Maze();

    void render(sf::RenderWindow& window);

    sf::Vector2i getPacmanStart() const;

    std::vector<sf::Vector2i> getAvailableDirections(sf::Vector2i tilePosition);
    sf::Vector2f getScreenPosition(sf::Vector2i tilePosition);
    sf::Vector2i getTilePosition(sf::Vector2f screenPosition);
    sf::Vector2f getTileCenter(sf::Vector2i tilePosition);

private:
    int tileSize = 24;
    int offsetY = 3;

    std::vector<std::string> mazeLayout;

    std::vector<sf::RectangleShape> walls;
    std::vector<sf::CircleShape> dots;
    std::vector<sf::CircleShape> energizers;

    sf::Vector2i pacmanStart;

    void createMaze();
    void createWall(std::size_t row, std::size_t col);
    void createDot(std::size_t row, std::size_t col);
    void createEnergizer(std::size_t row, std::size_t col);
    void setPacmanStart(std::size_t row, std::size_t col);

};