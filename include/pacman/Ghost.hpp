#pragma once

#include "pacman/Maze.hpp"
#include "pacman/Player.hpp"
#include "pacman/GhostMode.hpp"

#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

class Ghost
{
public:
    Ghost(char type, sf::Color color);

    void render(sf::RenderWindow &window) const;
    void update(float deltaTime, const Maze &maze, GhostMode mode, sf::Vector2i targetTile, bool reverseGhost);

    void setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPostion);

    char getType() const;
    sf::Vector2i getTilePosition() const;

private:
    char type;
    sf::CircleShape shape;

    sf::Vector2i tilePosition;
    sf::Vector2i lastDecisionTile;
    sf::Vector2f screenPosition;

    sf::Vector2i currentDirection;
    sf::Vector2i lastDirection;
    float speed;

    void updateTargetDirection(const std::vector<sf::Vector2i> &allowDirections, sf::Vector2i targetTile);
    void updateFrightenedDirection(const std::vector<sf::Vector2i> &allowDirections);

    std::mt19937 randomGenerator{std::random_device{}()};

    std::vector<sf::Vector2i> directionOrder = {
        {0, -1}, // UP
        {-1, 0}, // LEFT
        {0, 1},  // DOWN
        {1, 0}   // RIGHT
    };

    bool isAtTileCenter(sf::Vector2f tileCenter) const;
    void alignToTileCenter(sf::Vector2f tileCenter);

    bool shouldReverseDirection = false;
};
