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

    sf::Vector2i getTilePosition() const;
    sf::Vector2f getScreenPosition() const;

private:
    sf::CircleShape shape;

    sf::Vector2i tilePosition;
    sf::Vector2f screenPosition;

    sf::Vector2i currentDirection;
    float speed;
};