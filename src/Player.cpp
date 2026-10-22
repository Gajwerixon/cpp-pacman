#include "pacman/Player.hpp"


Player::Player()
    : shape(12.f),
      currentDirection(1, 0),
      requestedDirection(1, 0),
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


void Player::checkAvalibleDirections(const std::vector<sf::Vector2i> avalibleDirections) {

    if (currentDirection == requestedDirection) {
        if(!canMoveInDirection(currentDirection, avalibleDirections)) {
            currentDirection = sf::Vector2i(0, 0);        }
    }
    
    else {
        if (canMoveInDirection(requestedDirection, avalibleDirections)) {
            currentDirection = requestedDirection;
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

    if (requestedDirection.x != 0) {
        tilePosition.x = tileCenter.x;
    }

    if (requestedDirection.y != 0) {
        tilePosition.y = tileCenter.y;
    }

}


bool Player::changesMovementAxis() const {
    
    bool isStopped =
    currentDirection.x == 0 && currentDirection.y == 0;

    bool changesAxis =
        (currentDirection.x != 0 && requestedDirection.y != 0) ||
        (currentDirection.y != 0 && requestedDirection.x != 0);

    if (isStopped || changesAxis) {
        return true;
    }

    return false;

}