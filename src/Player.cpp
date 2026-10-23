#include "pacman/Player.hpp"

#include <cmath>
#include <algorithm>

Player::Player()
    : shape(12.f),
      currentDirection(1, 0),
      requestedDirection(1, 0),
      lastDirection(0, 0),
      tilePosition(0, 0),
      screenPosition(0.f, 0.f),
      speed(80.f)
{
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(12.f, 12.f);
}


void Player::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            requestedDirection = sf::Vector2i(0, -1);
        } else if (event.key.code == sf::Keyboard::Right) {
            requestedDirection = sf::Vector2i(1, 0);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            requestedDirection = sf::Vector2i(0, 1);
        }
        else if (event.key.code == sf::Keyboard::Left) {
            requestedDirection = sf::Vector2i(-1, 0);
        }
 
    }

}


void Player::render(sf::RenderWindow& window) {
    window.draw(shape);
}


void Player::update(float deltaTime) {

    screenPosition.x += currentDirection.x * speed * deltaTime;
    screenPosition.y += currentDirection.y * speed * deltaTime;

    shape.setPosition(screenPosition);

}


void Player::setStartPosition(sf::Vector2i start, sf::Vector2f startScreenPosition) {

    tilePosition = start;
    screenPosition = startScreenPosition;
    shape.setPosition(screenPosition);

}


sf::Vector2f Player::getScreenPosition() const {
    return screenPosition;
}


void Player::setTilePosition(sf::Vector2i newTilePosition) {
    tilePosition = newTilePosition;
}


sf::Vector2i Player::getTilePosition() const {
    return tilePosition;
}


bool Player::isAtTileCenter(sf::Vector2f tileCenter) const {

    float tolerance = 2.f;

    float positionX = std::abs(screenPosition.x - tileCenter.x);
    float positionY = std::abs(screenPosition.y - tileCenter.y);

    return positionX < tolerance && positionY < tolerance;

}


void Player::updateMovementDirection(const std::vector<sf::Vector2i>& avalibleDirections) {

    if (currentDirection == requestedDirection) {
        if(!canMoveInDirection(currentDirection, avalibleDirections)) {
            lastDirection = currentDirection;
            currentDirection = sf::Vector2i(0, 0);
        }
    }
    
    else {
        if (canMoveInDirection(requestedDirection, avalibleDirections)) {
            lastDirection = currentDirection;
            currentDirection = requestedDirection;
        }
        else if (!canMoveInDirection(currentDirection, avalibleDirections)) {
            lastDirection = currentDirection;
            currentDirection = sf::Vector2i(0, 0);
        }
    }

}


bool Player::canMoveInDirection(
    sf::Vector2i direction, 
    const std::vector<sf::Vector2i>& avalibleDirections
) {

    return std::find(
        avalibleDirections.begin(),
        avalibleDirections.end(),
        direction) != avalibleDirections.end();

}


void Player::alignToTileCenter(sf::Vector2f tileCenter) {

    if (lastDirection.x != 0) {
        screenPosition.x = tileCenter.x;
    }

    if (lastDirection.y != 0) {
        screenPosition.y = tileCenter.y;
    }
    
    shape.setPosition(screenPosition);

}


bool Player::changesMovementAxis() const {
    
    return
        (lastDirection.x != 0 && currentDirection.y != 0) ||
        (lastDirection.y != 0 && currentDirection.x != 0);
}


bool Player::stopped() const {
    return currentDirection == sf::Vector2i(0, 0);
}


void Player::alignToLastDirection(sf::Vector2f tileCenter) {

    if (lastDirection.x != 0) {
        screenPosition.x = tileCenter.x;
    }

    if (lastDirection.y != 0) {
        screenPosition.y = tileCenter.y;
    }
    
    shape.setPosition(screenPosition);
}


sf::Vector2i Player::getCurrentDirection(void) const {
    return currentDirection;
}


void Player::setScreenPosition(sf::Vector2f position) {
    screenPosition = position;
    shape.setPosition(screenPosition);
}