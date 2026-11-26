#pragma once

#include "pacman/Maze.hpp"
#include "pacman/GhostMode.hpp"
#include "pacman/GhostStatus.hpp"

#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

class Ghost
{
public:
    // Constructor
    Ghost(char type, sf::Color color, GhostStatus status);

    // Initialization
    void setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPosition);

    // Rendering and update
    void render(sf::RenderWindow &window) const;
    void update(float deltaTime, const Maze &maze, GhostMode mode, sf::Vector2i targetTile, bool reverseGhost);

    // Getters
    char getType() const;
    sf::Vector2i getTilePosition() const;
    GhostStatus getStatus() const;

private:
    // Ghost properties
    char type;
    sf::CircleShape shape;
    GhostStatus status;

    sf::Vector2i tilePosition;
    sf::Vector2i lastDecisionTile;
    sf::Vector2f screenPosition;

    sf::Vector2i currentDirection;
    sf::Vector2i lastDirection;
    float speed;

    // Movement
    void move(float deltaTime, const Maze &maze);
    bool isAtTileCenter(sf::Vector2f tileCenter) const;
    void alignToTileCenter(sf::Vector2f tileCenter);

    // Direction and behavior
    bool shouldReverseDirection = false;
    bool handleReversal(const Maze &maze, bool reverseGhost);

    void updateActive(float deltaTime, const Maze &maze, GhostMode mode, sf::Vector2i targetTile, bool reverseGhost);
    void updateInHouse(float deltaTime, const Maze &maze);
    void updateEaten(float deltaTime, const Maze &maze, sf::Vector2i targetTile);

    void updateTargetDirection(const std::vector<sf::Vector2i> &allowDirections, sf::Vector2i targetTile);
    void updateFrightenedDirection(const std::vector<sf::Vector2i> &allowDirections);

    std::mt19937 randomGenerator{std::random_device{}()};

    std::vector<sf::Vector2i> directionOrder = {
        {0, -1}, // UP
        {-1, 0}, // LEFT
        {0, 1},  // DOWN
        {1, 0}   // RIGHT
    };

    // Maze interactions
    bool handleTunnel(const Maze &maze);
    bool handleSpecialZones(const Maze &maze);
};