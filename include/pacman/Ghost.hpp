#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Ghost {
public:
    Ghost(sf::Color color);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

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