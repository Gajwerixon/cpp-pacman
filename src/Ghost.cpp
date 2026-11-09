#include "pacman/Ghost.hpp"
#include <iostream>

Ghost::Ghost(sf::Color color)
    : shape(12.f),
      currentDirection(1, 0),
      tilePosition(0, 0),
      screenPosition(0.f, 0.f),
      speed(80.f),
      lastDecisionTile(0, 0),
      lastDirection(0,0)
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

    // Handle tunel
    if (maze.isTunnel(tilePosition)) {

        if (tilePosition.x == 0 && currentDirection != sf::Vector2i(1, 0)) {

            sf::Vector2i targetTile(maze.getWidth() - 1, tilePosition.y);

            tilePosition = targetTile;
            screenPosition = maze.getTileCenter(targetTile);

            return;

        }

        if (tilePosition.x == maze.getWidth() - 1 && currentDirection != sf::Vector2i(-1, 0)) {
            
            sf::Vector2i targetTile(1, tilePosition.y);

            tilePosition = targetTile;
            screenPosition = maze.getTileCenter(targetTile);

            return;

        }

    }

    sf::Vector2f tileCenter = maze.getTileCenter(tilePosition);

    if (!isAtTileCenter(tileCenter)) {
        return;
    }
    
    // Choose a new direction only when entering a different tile
    if (tilePosition != lastDecisionTile) {

        updateDirection(maze.getAvailableDirections(tilePosition));
        lastDecisionTile = tilePosition;

        if (lastDirection != currentDirection) {
            alignToTileCenter(tileCenter);
        }

    }

}


void Ghost::setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPosition) {

    this->tilePosition = tilePosition;
    this->screenPosition = screenPosition;

    shape.setPosition(screenPosition);

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

    float tolerance = 1.f;

    float positionX = std::abs(screenPosition.x - tileCenter.x);
    float positionY = std::abs(screenPosition.y - tileCenter.y);

    return positionX < tolerance && positionY < tolerance;

}


void Ghost::alignToTileCenter(sf::Vector2f tileCenter) {

    if (lastDirection.x != 0) {
        screenPosition.x = tileCenter.x;
    }

    if (lastDirection.y != 0) {
        screenPosition.y = tileCenter.y;
    }
    
    shape.setPosition(screenPosition);

}
