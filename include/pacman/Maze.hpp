#pragma once

#include <vector>
#include <string>
#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Maze {   
public:
    Maze();

    void render(sf::RenderWindow& window);

    sf::Vector2i getPacmanStart() const;
    std::map<char, sf::Vector2i> getGhostStart() const;

    std::vector<sf::Vector2i> getAvailableDirections(sf::Vector2i tilePosition) const;
    sf::Vector2f getScreenPosition(sf::Vector2i tilePosition) const;
    sf::Vector2i getTilePosition(sf::Vector2f screenPosition) const;
    sf::Vector2f getTileCenter(sf::Vector2i tilePosition) const;

    int getWidth(void) const;
    bool isTunnel(sf::Vector2i tilePosition) const;
    bool isSpecialZone(sf::Vector2i tilePosition) const;

private:
    int tileSize = 24;
    int offsetY = 3;

    std::vector<std::string> mazeLayout;

    std::vector<sf::RectangleShape> walls;
    std::vector<sf::CircleShape> dots;
    std::vector<sf::CircleShape> energizers;

    sf::Vector2i pacmanStart;
    std::map<char, sf::Vector2i> ghostStart;

    void createMaze();
    void createWall(std::size_t row, std::size_t col);
    void createDot(std::size_t row, std::size_t col);
    void createEnergizer(std::size_t row, std::size_t col);
    void setPacmanStart(std::size_t row, std::size_t col);
    void setGhostStart(char ghostType, std::size_t row, std::size_t col);

    int tunnelWidth = 6;
    int tunnelRow = 14;
    std::vector<sf::Vector2i> tunnelTiles;
    void initializeTunnelTiles();

    int specialZoneStartX = 11;
    int specialZoneWidth = 6;
    int specialZone1Y = 11;
    int specialZone2Y = 23;
    std::vector<sf::Vector2i> specialZoneTiles;
    void initializeSpecialZones();

};