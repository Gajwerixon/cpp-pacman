#pragma once

#include <pacman/Maze.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
public:
    Player(const Maze& maze);

    // Input and update
    void handleEvents(const sf::Event& event);
    void updateMovementDirection(const std::vector<sf::Vector2i>& avalibleDirections);
    void update(float deltaTime);

    // Rendering
    void render(sf::RenderWindow& window);

    // Movement and alignment
    bool isAtTileCenter(sf::Vector2f tileCenter) const;
    bool changesMovementAxis() const;
    bool stopped() const;

    void alignToTileCenter(sf::Vector2f tileCenter);
    void alignToLastDirection(sf::Vector2f tileCenter);

private:
    sf::CircleShape shape;

    sf::Vector2i currentDirection;
    sf::Vector2i requestedDirection;
    sf::Vector2i lastDirection;

    sf::Vector2i tilePosition;
    sf::Vector2f screenPosition;

    float speed;

    bool canMoveInDirection(
        sf::Vector2i direction,
        const std::vector<sf::Vector2i>& availableDirections
    );

    const Maze& maze;

};