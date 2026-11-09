#pragma once

#include "pacman/Maze.hpp"
#include "pacman/Player.hpp"

#include <vector>

#include <SFML/Graphics.hpp>

class Ghost {
public:
    Ghost(sf::Color color);

    void update(float deltaTime, const Maze& maze, const Player& player);
    void render(sf::RenderWindow& window) const;

    void setStartPosition(
        sf::Vector2i tilePosition,
        sf::Vector2f screenPostion
    );

private:
    sf::CircleShape shape;

    sf::Vector2i tilePosition;
    sf::Vector2i lastDecisionTile;
    sf::Vector2f screenPosition;

    sf::Vector2i currentDirection;
    sf::Vector2i lastDirection;
    float speed;

    sf::Vector2i getTilePosition() const;
    sf::Vector2f getScreenPosition() const;

    void setTilePosition(sf::Vector2i tilePosition);
    void updateDirection(const std::vector<sf::Vector2i>& allowDirections);

    std::vector<sf::Vector2i> directionOrder = {
        { 0, -1 }, // UP
        {-1,  0 }, // LEFT
        { 0,  1 }, // DOWN
        { 1,  0 }  // RIGHT
    };

    bool isAtTileCenter(sf::Vector2f tileCenter) const;

};
