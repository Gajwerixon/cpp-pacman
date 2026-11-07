#include "pacman/Ghost.hpp"
#include <iostream>

Ghost::Ghost(sf::Color color)
    : shape(12.f),
      currentDirection(0, -1),
      lastDirection(0, 0),
      tilePosition(0, 0),
      screenPosition(0.f, 0.f),
      speed(10.f)
{
    shape.setFillColor(color);
    shape.setOrigin(12.f, 12.f);
}


void Ghost::render(sf::RenderWindow& window) const {
    window.draw(shape);
}


void Ghost::update(float deltaTime, const Maze& maze, const Player& player) {

    screenPosition.x += currentDirection.x * speed * deltaTime;
    screenPosition.y += currentDirection.y * speed * deltaTime;

    shape.setPosition(screenPosition);

    tilePosition = maze.getTilePosition(screenPosition);

    sf::Vector2f tileCenter = maze.getTileCenter(tilePosition);

    if (!isAtTileCenter(tileCenter)) {
        return;
    }

    updateDirection(maze.getAvailableDirections(tilePosition));

}


void Ghost::setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPosition) {

    this->tilePosition = tilePosition;
    this->screenPosition = screenPosition;

    shape.setPosition(screenPosition);

}


sf::Vector2i Ghost::getTilePosition() const {
    return tilePosition;
}


sf::Vector2f Ghost::getScreenPosition() const {
    return screenPosition;
}


void Ghost::setTilePosition(sf::Vector2i tilePosition) {
    this->tilePosition = tilePosition;
}


void Ghost::updateDirection(const std::vector<sf::Vector2i>& allowDirections) {

    // The Ghost cannot turn back => removing backward direction
    std::vector<sf::Vector2i> validDirections;

    for (auto direction : allowDirections) {

        if (direction != -currentDirection) {
            validDirections.push_back(direction);
        }

    }

    for (auto direction : directionOrder) {

        for (auto validDirection : validDirections) {

            if (direction == validDirection) {

                lastDirection = currentDirection;
                currentDirection = direction;
                return;

            }

        }

    }

}


bool Ghost::isAtTileCenter(sf::Vector2f tileCenter) const {

    float tolerance = 2.f;

    float positionX = std::abs(screenPosition.x - tileCenter.x);
    float positionY = std::abs(screenPosition.y - tileCenter.y);

    return positionX < tolerance && positionY < tolerance;

}
